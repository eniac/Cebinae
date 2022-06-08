#ifndef CEBINAE_QUEUE_DISC_H
#define CEBINAE_QUEUE_DISC_H

#include <deque>
#include <unordered_map>
#include "ns3/data-rate.h"
#include "ns3/histogram.h"
#include "ns3/ipv4-header.h"
#include "ns3/ipv4-queue-disc-item.h"
#include "ns3/my-source-id-tag.h"
#include "ns3/queue-disc.h"
#include "ns3/simulator.h"

namespace ns3 {

template <class K, class V>
class FlowBottleneckDetector {
public:

  virtual void UpdateCache(Ptr<QueueDiscItem> qdi) = 0;

  virtual std::pair<std::vector<K>, V> GetTopFlows(double delta_f) = 0;

  virtual void FlushCache() = 0; 

  virtual std::unordered_map<K, V> GetMysourceid2bytecount() {
    return m_mysourceid2bytecount;
  }

  virtual void PrintMysourceid2bytecount(std::ostream &os) const {
    os << "[------\n";
    for (auto iter = m_mysourceid2bytecount.begin(); iter != m_mysourceid2bytecount.end(); iter++) {
      os << iter->first << ": " << iter->second << "\n";
    }
    os << "------]\n";
  }

  virtual std::string DumpDigest() = 0;

protected:

  // Flow identifier K (MySourceIDTag value, 1:1 mapping to 5-tuple) to byte count V
  std::unordered_map<K, V> m_mysourceid2bytecount {};
  // Equivalent to hash to 5-tuple registers, but better interpretability
  std::vector<K> m_hash2mysourceid {};
  std::vector<V> m_hash2bytecount {}; 
  std::vector<K> m_hash2mysourceid2 {};
  std::vector<V> m_hash2bytecount2 {};  

  V m_max_bytes {0};

  std::ostringstream m_oss {};

};

class MySourceIDTagFBD: public FlowBottleneckDetector<uint32_t, uint64_t>
{
public:

  void UpdateCache(Ptr<QueueDiscItem> qdi) {
    Ptr<Packet> p = qdi->GetPacket();
    MySourceIDTag tag;
    if (p->FindFirstMatchingByteTag(tag)) {
      auto got = m_mysourceid2bytecount.find(tag.Get());
      if (got != m_mysourceid2bytecount.end()) {
        m_mysourceid2bytecount[tag.Get()] += p->GetSize();
      } else {
        m_mysourceid2bytecount[tag.Get()] = p->GetSize();
      }

      if (m_mysourceid2bytecount[tag.Get()] > m_max_bytes) {
        m_max_bytes = m_mysourceid2bytecount[tag.Get()];
      }
    } else {
      // Non application traffic
    }
  }

  void FlushCache() {
    m_mysourceid2bytecount.clear();
    m_max_bytes = 0;
  }

  std::pair<std::vector<uint32_t>, uint64_t> GetTopFlows(double delta_f) {
    std::vector<uint32_t> ret_vec;
    uint32_t ret_bottleneck_bytes = 0;

    m_num_gettopflows += 1;

    for (auto iter = m_mysourceid2bytecount.begin(); iter != m_mysourceid2bytecount.end(); iter++) {
      if (iter->second > m_max_bytes*(1-delta_f)) {
        // Add the flow signature to set
        ret_vec.push_back(iter->first);
        ret_bottleneck_bytes += iter->second;

        // Update histroy accounting
        auto got = m_sourceidtag2toptimes.find(iter->first);
        if (got != m_sourceidtag2toptimes.end()) {
          m_sourceidtag2toptimes[iter->first] += 1;
        } else {
          m_sourceidtag2toptimes[iter->first] = 1;
        }
      }
    }
    return std::make_pair(ret_vec, ret_bottleneck_bytes);
  }

  std::string DumpDigest() {
    m_oss << "--- FlowBottleneckDetector ---\n"
          << "m_num_gettopflows: " << m_num_gettopflows << "\n"
          << "m_sourceidtag2toptimes:\n";
    for (auto iter = m_sourceidtag2toptimes.begin(); iter != m_sourceidtag2toptimes.end(); iter ++) {
      m_oss << iter->first << ": " << iter->second << "\n";
    }
    m_oss << "------\n";
    return m_oss.str();
  }

private:
  uint32_t m_num_gettopflows {0}; // Counters for GetTopFlows invocations
  std::unordered_map<uint32_t, uint32_t> m_sourceidtag2toptimes {}; // Records of bottlenecked times for each tag for accounting and calculate the ratio
};

class HashPipe1StageFBD: public FlowBottleneckDetector<uint32_t, uint64_t>
{
public:
  HashPipe1StageFBD(int num_slot_pow2) {
    m_num_slot = pow(2, num_slot_pow2);
    m_num_slot_pow2 = num_slot_pow2;
    m_hash2mysourceid.resize(m_num_slot, 2147483648);
    m_hash2bytecount.resize(m_num_slot, 0);
  }

  void UpdateCache(Ptr<QueueDiscItem> qdi) {
    // Get 5-tuple hash: an uncoorperative host my claim more BW by generating multiple flows, one could use alternative flow id (e.g., 2 tuple) to prevent this
    uint32_t h_5tuple = qdi->Hash();
    uint32_t h_slot = (h_5tuple % m_num_slot);

    Ptr<Packet> p = qdi->GetPacket();
    MySourceIDTag tag;
    if (p->FindFirstMatchingByteTag(tag)) {

      // Single stage HashPipe
      if(m_hash2mysourceid[h_slot] == tag.Get()) {
        m_hash2bytecount[h_slot] += p->GetSize();
      } else {
        // Reclaim the slot without recirculation
        m_hash2bytecount[h_slot] = p->GetSize();
      }
      m_hash2mysourceid[h_slot] = tag.Get();
      
      // Keep a ground truth map for debugging
      auto got = m_mysourceid2bytecount.find(tag.Get());
      if (got != m_mysourceid2bytecount.end()) {
        m_mysourceid2bytecount[tag.Get()] += p->GetSize();
      } else {
        m_mysourceid2bytecount[tag.Get()] = p->GetSize();
      }
      if (m_mysourceid2bytecount[tag.Get()] > m_max_bytes) {
        m_max_bytes = m_mysourceid2bytecount[tag.Get()];
      }
    } else {
      // Non-application traffic (ACKs), considered negligible size (i.e., non-top) for better simulation result tracing and interpretability
      Ptr<const Ipv4QueueDiscItem> iqdi = Ptr<const Ipv4QueueDiscItem> (dynamic_cast<const Ipv4QueueDiscItem *> (PeekPointer (qdi)));
      Ipv4Header ipv4_header = iqdi->GetHeader ();
      Ipv4Address ipv4_src = ipv4_header.GetSource ();
      Ipv4Address ipv4_dst = ipv4_header.GetDestination ();      
      NS_LOG_DEBUG("MySourceIDTag not found: " << ipv4_src << "->" << ipv4_dst);
    }
  }

  void FlushCache() {
    m_mysourceid2bytecount.clear();
    m_hash2mysourceid.resize(0);
    m_hash2mysourceid.resize(m_num_slot, 2147483648);
    m_hash2bytecount.resize(0);
    m_hash2bytecount.resize(m_num_slot, 0);
    m_max_bytes = 0;
  }

  std::pair<std::vector<uint32_t>, uint64_t> GetTopFlows(double delta_f) {
    // MA table in HW as top flows are typically of a small subset, o.w., may apply for instance counting BF
    std::vector<uint32_t> ret_vec;
    uint64_t ret_bottleneck_bytes = 0;

    m_num_gettopflows += 1;

    // Get max bytes in cache
    uint64_t max_bytes = 0;
    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes) {
        max_bytes = m_hash2bytecount[i];
      }
    }
    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes*(1-delta_f)) {
        ret_vec.push_back(m_hash2mysourceid[i]);
        ret_bottleneck_bytes += m_hash2bytecount[i];
        // Update histroy accounting
        auto got = m_sourceidtag2toptimes.find(m_hash2mysourceid[i]);
        if (got != m_sourceidtag2toptimes.end()) {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] += 1;
        } else {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] = 1;
        }        
      }
    }
    return std::make_pair(ret_vec, ret_bottleneck_bytes);
  }

  std::string DumpDigest() {
    m_oss << "--- FlowBottleneckDetector ---\n"
          << "m_num_gettopflows: " << m_num_gettopflows << "\n"
          << "m_num_slot_pow2: " << m_num_slot_pow2 << "\n"
          << "m_num_slot: " << m_num_slot << "\n"
          << "m_hash2mysourceid.size(): " << m_hash2mysourceid.size() << "\n"
          << "m_hash2bytecount.size(): " << m_hash2bytecount.size() << "\n"
          << "m_sourceidtag2toptimes:\n";
    for (auto iter = m_sourceidtag2toptimes.begin(); iter != m_sourceidtag2toptimes.end(); iter ++) {
      m_oss << iter->first << ": " << iter->second << "\n";
    }
    m_oss << "------\n";
    return m_oss.str();
  }

private:

  int m_num_slot_pow2 = 11;
  int m_num_slot = 2048;

  uint32_t m_num_gettopflows {0}; // Counters for GetTopFlows invocations
  // Records of bottlenecked times for each tag for accounting and calculate the ratio
  std::unordered_map<uint32_t, uint32_t> m_sourceidtag2toptimes {};
};

class HashPipe1StageFcfsFBD: public FlowBottleneckDetector<uint32_t, uint64_t>
{
  const uint64_t c_unclaimed = 2147483648;
public:
  HashPipe1StageFcfsFBD(int num_slot_pow2) {
    m_num_slot = pow(2, num_slot_pow2);
    m_num_slot_pow2 = num_slot_pow2;
    m_hash2mysourceid.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount.resize(m_num_slot, 0);
  }

  void UpdateCache(Ptr<QueueDiscItem> qdi) {
    // Get 5-tuple hash: an uncoorperative host my claim more BW by generating multiple flows, one could use alternative flow id (e.g., 2 tuple) to prevent this
    uint32_t h_5tuple = qdi->Hash();
    uint32_t h_slot = (h_5tuple % m_num_slot);

    Ptr<Packet> p = qdi->GetPacket();
    MySourceIDTag tag;
    if (p->FindFirstMatchingByteTag(tag)) {
      
      if (m_hash2mysourceid[h_slot] == c_unclaimed) {
        // Claim the slot FCFS
        m_hash2mysourceid[h_slot] = tag.Get();
        m_hash2bytecount[h_slot] = p->GetSize();
      } else if (m_hash2mysourceid[h_slot] == tag.Get()) {
        m_hash2bytecount[h_slot] += p->GetSize();
      } else {
        // Missed flows
        sourceids_wo_slots.insert(tag.Get());
      }

      // Keep a ground truth map for debugging
      auto got = m_mysourceid2bytecount.find(tag.Get());
      if (got != m_mysourceid2bytecount.end()) {
        m_mysourceid2bytecount[tag.Get()] += p->GetSize();
      } else {
        m_mysourceid2bytecount[tag.Get()] = p->GetSize();
      }
      if (m_mysourceid2bytecount[tag.Get()] > m_max_bytes) {
        m_max_bytes = m_mysourceid2bytecount[tag.Get()];
      }
    } else {
      // Non-application traffic (ACKs), considered negligible size (i.e., non-top) for better simulation result tracing and interpretability
      Ptr<const Ipv4QueueDiscItem> iqdi = Ptr<const Ipv4QueueDiscItem> (dynamic_cast<const Ipv4QueueDiscItem *> (PeekPointer (qdi)));
      Ipv4Header ipv4_header = iqdi->GetHeader ();
      Ipv4Address ipv4_src = ipv4_header.GetSource ();
      Ipv4Address ipv4_dst = ipv4_header.GetDestination ();      
      NS_LOG_DEBUG("MySourceIDTag not found: " << ipv4_src << "->" << ipv4_dst);
    }
  }

  void FlushCache() {
    m_mysourceid2bytecount.clear();
    m_hash2mysourceid.resize(0);
    m_hash2mysourceid.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount.resize(0);
    m_hash2bytecount.resize(m_num_slot, 0);
    m_max_bytes = 0;
  }

  std::pair<std::vector<uint32_t>, uint64_t> GetTopFlows(double delta_f) {
    // MA table in HW as top flows are typically of a small subset, o.w., may apply for instance counting BF
    std::vector<uint32_t> ret_vec;
    uint64_t ret_bottleneck_bytes = 0;

    m_num_gettopflows += 1;

    // Get max bytes in cache
    uint64_t max_bytes = 0;
    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes) {
        max_bytes = m_hash2bytecount[i];
      }
    }
    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes*(1-delta_f)) {
        ret_vec.push_back(m_hash2mysourceid[i]);
        ret_bottleneck_bytes += m_hash2bytecount[i];
        // Update histroy accounting
        auto got = m_sourceidtag2toptimes.find(m_hash2mysourceid[i]);
        if (got != m_sourceidtag2toptimes.end()) {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] += 1;
        } else {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] = 1;
        }        
      }
    }
    return std::make_pair(ret_vec, ret_bottleneck_bytes);
  }

  std::string DumpDigest() {
    m_oss << "--- FlowBottleneckDetector ---\n"
          << "m_num_gettopflows: " << m_num_gettopflows << "\n"
          << "m_num_slot_pow2: " << m_num_slot_pow2 << "\n"
          << "m_num_slot: " << m_num_slot << "\n"
          << "m_hash2mysourceid.size(): " << m_hash2mysourceid.size() << "\n"
          << "m_hash2bytecount.size(): " << m_hash2bytecount.size() << "\n"
          << "m_sourceidtag2toptimes:\n";
    for (auto iter = m_sourceidtag2toptimes.begin(); iter != m_sourceidtag2toptimes.end(); iter ++) {
      m_oss << iter->first << ": " << iter->second << "\n";
    }
    m_oss << "sourceids_wo_slots (during some round(s) due to 5-tuple hash collision):\n";
    for (auto iter = sourceids_wo_slots.begin(); iter != sourceids_wo_slots.end(); iter ++) {
      m_oss << (*iter) << "\n";
    }    
    m_oss << "------\n";
    return m_oss.str();
  }

private:

  int m_num_slot_pow2 = 11;
  int m_num_slot = 2048;

  uint32_t m_num_gettopflows {0};
  std::unordered_map<uint32_t, uint32_t> m_sourceidtag2toptimes {};

  std::set<uint32_t> sourceids_wo_slots {};
};

class HashPipe2StageFcfsFBD: public FlowBottleneckDetector<uint32_t, uint64_t>
{
  const uint64_t c_unclaimed = 2147483648;
public:
  HashPipe2StageFcfsFBD(int num_slot_pow2) {
    m_num_slot = pow(2, num_slot_pow2);
    m_num_slot_pow2 = num_slot_pow2;
    m_hash2mysourceid.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount.resize(m_num_slot, 0);
    m_hash2mysourceid2.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount2.resize(m_num_slot, 0);
  }

  void UpdateCache(Ptr<QueueDiscItem> qdi) {
    // Maybe assign independent rand stream rather than automatic assignment for the hash
    uint32_t h_5tuple = qdi->Hash();
    uint32_t h_5tuple2 = qdi->Hash(2022);

    uint32_t h_slot = (h_5tuple % m_num_slot);
    uint32_t h_slot2 = (h_5tuple2 % m_num_slot);

    Ptr<Packet> p = qdi->GetPacket();
    MySourceIDTag tag;
    if (p->FindFirstMatchingByteTag(tag)) {
      // Check slots in stage 1
      if (m_hash2mysourceid[h_slot] == c_unclaimed) {
        m_hash2mysourceid[h_slot] = tag.Get();
        m_hash2bytecount[h_slot] = p->GetSize();
      } else if (m_hash2mysourceid[h_slot] == tag.Get()) {
        m_hash2bytecount[h_slot] += p->GetSize();
      } else {
        // Already occupied, check stage 2
        if (m_hash2mysourceid2[h_slot2] == c_unclaimed) {
          m_hash2mysourceid2[h_slot2] = tag.Get();
          m_hash2bytecount2[h_slot2] = p->GetSize();
        } else if (m_hash2mysourceid2[h_slot2] == tag.Get()) {
          m_hash2bytecount2[h_slot2] += p->GetSize();
        } else {
          sourceids_wo_slots.insert(tag.Get());
        }
      }
      // Keep a ground truth map for debugging
      auto got = m_mysourceid2bytecount.find(tag.Get());
      if (got != m_mysourceid2bytecount.end()) {
        m_mysourceid2bytecount[tag.Get()] += p->GetSize();
      } else {
        m_mysourceid2bytecount[tag.Get()] = p->GetSize();
      }
      if (m_mysourceid2bytecount[tag.Get()] > m_max_bytes) {
        m_max_bytes = m_mysourceid2bytecount[tag.Get()];
      }
    } else {
      // Non-application traffic (ACKs), considered negligible size (i.e., non-top) for better simulation result tracing and interpretability
      Ptr<const Ipv4QueueDiscItem> iqdi = Ptr<const Ipv4QueueDiscItem> (dynamic_cast<const Ipv4QueueDiscItem *> (PeekPointer (qdi)));
      Ipv4Header ipv4_header = iqdi->GetHeader ();
      Ipv4Address ipv4_src = ipv4_header.GetSource ();
      Ipv4Address ipv4_dst = ipv4_header.GetDestination ();      
      NS_LOG_DEBUG("MySourceIDTag not found: " << ipv4_src << "->" << ipv4_dst);
    }
  }

  void FlushCache() {
    m_mysourceid2bytecount.clear();
    m_hash2mysourceid.resize(0);
    m_hash2mysourceid.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount.resize(0);
    m_hash2bytecount.resize(m_num_slot, 0);
    m_hash2mysourceid2.resize(0);
    m_hash2mysourceid2.resize(m_num_slot, c_unclaimed);
    m_hash2bytecount2.resize(0);
    m_hash2bytecount2.resize(m_num_slot, 0);    
    m_max_bytes = 0;
  }

  std::pair<std::vector<uint32_t>, uint64_t> GetTopFlows(double delta_f) {
    // MA table in HW as top flows are typically of a small subset, o.w., may apply for instance counting BF
    std::vector<uint32_t> ret_vec;
    uint64_t ret_bottleneck_bytes = 0;

    m_num_gettopflows += 1;

    // Get max bytes in caches
    uint64_t max_bytes = 0;
    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes) {
        max_bytes = m_hash2bytecount[i];
      }
      if (m_hash2bytecount2[i] > max_bytes) {
        max_bytes = m_hash2bytecount2[i];
      }
    }

    for (int i = 0; i < m_num_slot; i++) {
      if (m_hash2bytecount[i] > max_bytes*(1-delta_f)) {
        ret_vec.push_back(m_hash2mysourceid[i]);
        ret_bottleneck_bytes += m_hash2bytecount[i];
        // Update histroy accounting
        auto got = m_sourceidtag2toptimes.find(m_hash2mysourceid[i]);
        if (got != m_sourceidtag2toptimes.end()) {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] += 1;
        } else {
          m_sourceidtag2toptimes[m_hash2mysourceid[i]] = 1;
        }        
      }
      if (m_hash2bytecount2[i] > max_bytes*(1-delta_f)) {
        ret_vec.push_back(m_hash2mysourceid2[i]);
        ret_bottleneck_bytes += m_hash2bytecount2[i];

        auto got = m_sourceidtag2toptimes.find(m_hash2mysourceid2[i]);
        if (got != m_sourceidtag2toptimes.end()) {
          m_sourceidtag2toptimes[m_hash2mysourceid2[i]] += 1;
        } else {
          m_sourceidtag2toptimes[m_hash2mysourceid2[i]] = 1;
        }        
      }      
    }
    return std::make_pair(ret_vec, ret_bottleneck_bytes);
  }

  std::string DumpDigest() {
    m_oss << "--- FlowBottleneckDetector ---\n"
          << "m_num_gettopflows: " << m_num_gettopflows << "\n"
          << "m_num_slot_pow2: " << m_num_slot_pow2 << "\n"
          << "m_num_slot: " << m_num_slot << "\n"
          << "m_hash2mysourceid.size(): " << m_hash2mysourceid.size() << "\n"
          << "m_hash2bytecount.size(): " << m_hash2bytecount.size() << "\n"
          << "m_sourceidtag2toptimes:\n";
    for (auto iter = m_sourceidtag2toptimes.begin(); iter != m_sourceidtag2toptimes.end(); iter ++) {
      m_oss << iter->first << ": " << iter->second << "\n";
    }
    m_oss << "sourceids_wo_slots (during some round(s) due to 5-tuple hash collision):\n";
    for (auto iter = sourceids_wo_slots.begin(); iter != sourceids_wo_slots.end(); iter ++) {
      m_oss << (*iter) << "\n";
    }    
    m_oss << "------\n";
    return m_oss.str();
  }

private:

  int m_num_slot_pow2 = 11;
  int m_num_slot = 2048;

  uint32_t m_num_gettopflows {0};
  std::unordered_map<uint32_t, uint32_t> m_sourceidtag2toptimes {};

  std::set<uint32_t> sourceids_wo_slots {};
};

/**
 * \ingroup traffic-control
 *
 * Queue disc implementing Cebinae transactions.
 * - Traffic Control Layer to position Cebinae logic in NS-3 ecosystem.
 * - Current CebinaeQueueDisc doesn't consider co-existence with AQM mechanisms, e.g., RED, CoDel.
 * - It builds Cebinae on a simple 2-drop-tail-queue system, each queue with the periodically reconfigured priority.
 */
class CebinaeQueueDisc : public QueueDisc {
public:

  enum CebinaeState
  {
    INIT,
    ROTATE,
    RECONFIG
  };

  const std::vector<std::string> CebinaeStateString {
    "INIT",
    "ROTATE",
    "RECONFIG"
  };

  class CebinaeDebugger {
  public:
    enum EnqueueType
    {
      HEADQ_ENQUEUE,
      HEADQ_DROP,
      NEGHEADQ_ENQUEUE,
      NEGHEADQ_DROP,
      LBF_DROP      
    };  
    class DebugStats {
      public:
        uint64_t num_headq_enqueue {0};
        uint64_t num_headq_drop {0};
        uint64_t num_negheadq_enqueue {0};
        uint64_t num_negheadq_drop {0};
        uint64_t num_lbf_drop {0};
        uint32_t max_total_qlen_pkts {0};
        // Skipped Histogram or qtime quantiles due to overly verbose printing
    };

    void UpdateDebugStats(Ptr<Packet> p, EnqueueType type, uint32_t qlen) {
      MySourceIDTag tag;
      if (p->FindFirstMatchingByteTag(tag)) {
        auto got = m_sourceidtag2debugstats.find(tag.Get());
        if (got != m_sourceidtag2debugstats.end()) {
          if (type==HEADQ_ENQUEUE) {
            m_sourceidtag2debugstats[tag.Get()].num_headq_enqueue += 1;
          } else if (type==HEADQ_DROP) {
            m_sourceidtag2debugstats[tag.Get()].num_headq_drop += 1;          
          } else if (type==NEGHEADQ_ENQUEUE) {
            m_sourceidtag2debugstats[tag.Get()].num_negheadq_enqueue += 1;          
          } else if (type==NEGHEADQ_DROP) {
            m_sourceidtag2debugstats[tag.Get()].num_negheadq_drop += 1;           
          } else if (type==LBF_DROP) {
            m_sourceidtag2debugstats[tag.Get()].num_lbf_drop += 1;          
          }
          if (qlen > m_sourceidtag2debugstats[tag.Get()].max_total_qlen_pkts) {
            m_sourceidtag2debugstats[tag.Get()].max_total_qlen_pkts = qlen;
          }          
        } else {
          DebugStats debug_stats;
          if (type==HEADQ_ENQUEUE) {
            debug_stats.num_headq_enqueue = 1;
          } else if (type==HEADQ_DROP) {
            debug_stats.num_headq_drop = 1;
          } else if (type==NEGHEADQ_ENQUEUE) {
            debug_stats.num_negheadq_enqueue = 1;
          } else if (type==NEGHEADQ_DROP) {
            debug_stats.num_negheadq_drop = 1;
          } else if (type==LBF_DROP) {
            debug_stats.num_lbf_drop = 1;
          }
          debug_stats.max_total_qlen_pkts = qlen;
          m_sourceidtag2debugstats[tag.Get()] = debug_stats;
        }
      }
    }
    void FlushDebugStats() {
      m_sourceidtag2debugstats.clear();
    }
    std::string GetDebugStats() {
      std::ostringstream oss;
      for (auto iter = m_sourceidtag2debugstats.begin(); iter != m_sourceidtag2debugstats.end(); iter ++) {
        oss << iter->first << ":["
            << iter->second.num_headq_enqueue << ","
            << iter->second.num_headq_drop << ","
            << iter->second.num_negheadq_enqueue << ","
            << iter->second.num_negheadq_drop << ","
            << iter->second.num_lbf_drop << ","
            << iter->second.max_total_qlen_pkts << ","
            << "],";
      }
      return oss.str();
    }

  private:
    std::unordered_map<uint32_t, DebugStats> m_sourceidtag2debugstats {};
  };

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * \brief CebinaeQueueDisc constructor
   *
   * Creates a queue with a depth of 1000 packets by default
   */
  CebinaeQueueDisc();

  virtual ~CebinaeQueueDisc();

  // Reasons for dropping packets
  static constexpr const char* LIMIT_EXCEEDED_DROP = "Queue disc limit exceeded";  //!< Packet dropped due to queue disc limit exceeded

  std::string DumpDigest();

  std::string DumpDebugEvents();

private:
  virtual bool DoEnqueue (Ptr<QueueDiscItem> item);
  virtual Ptr<QueueDiscItem> DoDequeue (void);
  virtual Ptr<const QueueDiscItem> DoPeek (void);
  virtual bool CheckConfig (void);
  virtual void InitializeParams (void);

  // State machine loops that locally verifies max-min fairness and push towards the 'fair' direction
  void ReactionFSM();

  // --- Cabinae params ---
  // Port saturation/bottleneck threshold
  double m_delta_p {0.05};
  // Top-k flows threshold
  double m_delta_f {0.05};  
  // Cebinae tax rate
  double m_tau {0.05};
  // Number of dT periods before recomputing utilization and rate limits
  // Note that P can be either odd or even as we set every dT (but recomputes every P*dT)
  uint32_t m_p {1};  
  // Control plane execution deadline, can be effectively close to 0
  Time m_l {NanoSeconds (1024)};
  Time m_dt {NanoSeconds (1048576)};  // Default 2^20
  Time m_vdt {NanoSeconds (1024)};  

  // Data rate of the attached NetDevice
  DataRate m_bps;

  // Number of virtual buckets per phy queue
  uint32_t m_vb {1024};

  // Recomputation counter
  uint32_t m_recomputation_ctr {0};
  // For CebinaeQueueDisc state machine
  CebinaeState m_state {INIT};
  // Base round time
  Time m_base_round_time {NanoSeconds (0)};
  // Round time
  Time m_round_time {NanoSeconds (0)};
  // Binary value referring to which internal queue is headq and neg_headq (headq + neg_headq == 1)
  uint32_t m_headq {0};
  uint32_t m_neg_headq {1};
  uint32_t m_high_prio_queue {0};
  // Every port/NetDevice/CebinaeQueueDisc maintains 2 bytes counters for top and bot flows
  uint32_t m_bytes_top {0};
  uint32_t m_bytes_bot {0};
  // Computed rates for top and bot
  uint64_t m_computed_bps_top {0};
  uint64_t m_computed_bps_bot {0};
  // The configured LBF rate (bps) for LBFs
  std::vector<uint64_t> m_lbf_bps_top;
  std::vector<uint64_t> m_lbf_bps_bot;
  uint64_t m_last_rate_top {0};
  uint64_t m_last_rate_bot {0};
  // Whether port is saturated (one flag per port/NetDevice/CebinaeQueueDisc)
  // bool m_port_saturated {false};

  // Having a class for port saturation detector is an overkill.
  // The egress pipeline maintains a port to byte count register.
  // In simulation, we can freeze and sync the time, hence, 
  // each CebinaeQueueDisc (attached to a single egress port/NetDevice) only needs to record its own local byte count.  
  uint64_t m_port_bytecounts {0};

  // Use a top flow detection subroutine
  // MySourceIDTagFBD m_fbd {};
  // HashPipe1StageFBD m_fbd{11};
  // HashPipe1StageFcfsFBD m_fbd{11};
  HashPipe2StageFcfsFBD m_fbd{11};

  // Set of bottlenecked flows, typically a small set as in reality, only a small portion of elephant flows
  // TODO: use unordered_set
  std::vector<uint32_t> m_bottlenecked_flows_set {};

  // History of top flows

  // --- Debugging stats ---
  std::ostringstream m_oss_summary {};
  bool m_debug;
  std::deque<std::string> m_debug_events {};
  CebinaeDebugger m_debugger {};

  // --- Digest stats ---
  // Counter for all arrival packets
  uint64_t m_arrived_pkts {0};
  // Counter of LBF past head
  uint64_t m_lbf_past_head_pkts {0};
  // Counter of LBF past tail
  uint64_t m_lbf_past_tail_pkts {0};
  // Counter of LBF dropped packets
  uint64_t m_lbf_drop_pkts {0};
  // Counter for number of packets dropped during enqueue due to buffer full
  std::vector<uint64_t> m_enqueue_drop_pkts {};
  // Counter for number of packets dequeued
  uint64_t m_cebinae_dequeued_succeeded {0};
  // Counter for number of recomputation triggers
  uint64_t m_num_p {0};
  // Counter for number of bottlenecked times
  uint64_t m_num_bottleneck_p {0};
  // Counter for number of non-bottlenecked times
  uint64_t m_num_non_bottleneck_p {0};
  // Counter for experienced ROTATE state
  uint64_t m_num_rotated {0};

};

} // namespace ns3

#endif
