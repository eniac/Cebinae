#ifndef CEBINAE_QUEUE_DISC_H
#define CEBINAE_QUEUE_DISC_H

#include "ns3/data-rate.h"
#include "ns3/my-source-id-tag.h"
#include "ns3/queue-disc.h"
#include "ns3/simulator.h"

namespace ns3 {

template <class K, class V>
class FlowBottleneckDetector {
public:

  virtual void UpdateCache(Ptr<Packet> p) = 0;

  virtual std::pair<std::vector<K>, V> GetTopFlows(double delta_f) = 0;

  virtual void FlushCache() {
    m_flow_cache.clear();
    m_max_bytes = 0;
  }

  virtual std::unordered_map<K, V> GetCache() {
    return m_flow_cache;
  }

  virtual void PrintCache(std::ostream &os) const {
    os << "[------\n";
    for (auto iter = m_flow_cache.begin(); iter != m_flow_cache.end(); iter++) {
      os << iter->first << ": " << iter->second << "\n";
    }
    os << "------]\n";
  }

  virtual std::string DumpDigest() = 0;

protected:

  // Flow identifier K (e.g., source tag, 5-tuple hash) to byte count V
  std::unordered_map<K, V> m_flow_cache {};

  V m_max_bytes {0};

  std::ostringstream m_oss {};

};

class MySourceIDTagFBD: public FlowBottleneckDetector<uint32_t, uint64_t>
{
public:

  void UpdateCache(Ptr<Packet> p) {
    MySourceIDTag tag;
    if (p->FindFirstMatchingByteTag(tag)) {
      auto got = m_flow_cache.find(tag.Get());
      if (got != m_flow_cache.end()) {
        m_flow_cache[tag.Get()] += p->GetSize();
      } else {
        m_flow_cache[tag.Get()] = p->GetSize();
      }

      if (m_flow_cache[tag.Get()] > m_max_bytes) {
        m_max_bytes = m_flow_cache[tag.Get()];
      }
    } else {
      // Doesn't matter
    }
  }

  std::pair<std::vector<uint32_t>, uint64_t> GetTopFlows(double delta_f) {
    std::vector<uint32_t> ret_vec;
    uint32_t ret_bottleneck_bytes = 0;

    m_num_gettopflows += 1;

    for (auto iter = m_flow_cache.begin(); iter != m_flow_cache.end(); iter++) {
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

  // Records of bottlenecked times for each tag for accounting and calculate the ratio
  std::unordered_map<uint32_t, uint32_t> m_sourceidtag2toptimes {};
};

// Add another implementation for real 5-tuple and apply HashPipe data struct with n slots

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
  // Control plane execution deadline
  Time m_l {NanoSeconds (65536)};
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
  bool m_port_saturated {false};

  // Having a class for port saturation detector is an overkill.
  // The egress pipeline maintains a port to byte count register.
  // In simulation, we can freeze and sync the time, hence, 
  // each CebinaeQueueDisc (attached to a single egress port/NetDevice) only needs to record its own local byte count.  
  uint64_t m_port_bytecounts {0};

  MySourceIDTagFBD m_fbd {};

  // Set of bottlenecked flows, typically a small set as in reality, only a small portion of elephant flows
  // TODO: use unordered_set
  std::vector<uint32_t> m_bottlenecked_flows_set {};

  // History of top flows

  // --- Debugging stats to dump ---
  std::ostringstream m_oss_summary {};
  bool m_debug;
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
