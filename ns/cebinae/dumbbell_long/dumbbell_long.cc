#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/my-source-id-tag.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/traffic-control-module.h"

#include "../utils/my-sink.h"
#include "../utils/my-source.h"

using namespace ns3;

// Long-lived flows, single-bottleneck
NS_LOG_COMPONENT_DEFINE ("DumbbellLong");

#define MAX_CCA 9

// static void
// CwndChange (uint32_t oldCwnd, uint32_t newCwnd)
// {
//   NS_LOG_DEBUG (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
// }

// static void
// RxDrop (Ptr<const Packet> p)
// {
//   NS_LOG_DEBUG ("RxDrop at " << Simulator::Now ().GetNanoSeconds());
// }

// void CheckQueueSize (Ptr<QueueDisc> qd)
// {
//   uint32_t qsize = qd->GetCurrentSize ().GetValue ();
//   Simulator::Schedule (Seconds (0.2), &CheckQueueSize, qd);
//   std::ofstream q (dir + "/queueSize.dat", std::ios::out | std::ios::app);
//   q << Simulator::Now ().GetSeconds () << " " << qsize << std::endl;
//   q.close ();
// }
//   tch.Uninstall (routers.Get (0)->GetDevice (1));
//   QueueDiscContainer qd;
//   qd = tch.Install (routers.Get (0)->GetDevice (1));
//   Simulator::ScheduleNow (&CheckQueueSize, qd.Get (0));

std::vector<double> avg_tpt_bottleneck;  // Avg over whole sim period
std::vector<double> avg_tpt_app;  // This is actually goodput
// double avg_jfi_bottleneck = 0.0;
// double avg_jfi_app = 0.0;
std::vector<std::vector<int64_t>> source2rtttrace;

int num_tracing_periods = 0;
double sim_seconds = 1;
double app_seconds_start = 0.1;
double app_seconds_end = 10;

// Triggered when a packet has been completely transmitted over the channel
std::unordered_map<std::uint32_t, std::uint64_t> mysourceidtag2pktcount;
std::unordered_map<std::uint32_t, std::uint64_t> mysourceidtag2cummbytecount;
std::vector<std::uint64_t> mysourceidtag2bytecount;
static void
PhyTxEndCb (Ptr<const Packet> p)
{
  MySourceIDTag tag;
  // p->PeekPacketTag(tag);
  // p->PrintPacketTags(std::cout);
  // p->PrintByteTags(std::cout);
  if (p->FindFirstMatchingByteTag(tag)) {
    std::unordered_map<std::uint32_t, std::uint64_t>::const_iterator got = mysourceidtag2pktcount.find(tag.Get());
    if (got != mysourceidtag2pktcount.end()) {
      mysourceidtag2pktcount[tag.Get()] += 1;
    } else {
      mysourceidtag2pktcount[tag.Get()] = 1;
    }    
    if (got != mysourceidtag2cummbytecount.end()) {
      mysourceidtag2cummbytecount[tag.Get()] += p->GetSize();
    } else {
      mysourceidtag2cummbytecount[tag.Get()] = p->GetSize();
    }
    mysourceidtag2bytecount[tag.Get()] += p->GetSize();
    // Destination IP print
    // NS_LOG_DEBUG ("[" << Simulator::Now ().GetNanoSeconds() << "] Bottleneck link: " << tag.Get() << ", size: " << p->GetSize());
  }
}

std::vector<std::uint64_t> mysink_mysourceidtag2bytecount;
static void
RxWithAddressesMySink (Ptr<const Packet> p, const Address& from, const Address& local) {
  MySourceIDTag tag;
  if (p->FindFirstMatchingByteTag(tag)) {
    NS_LOG_DEBUG ("[" << Simulator::Now ().GetNanoSeconds() << "] SourceIDTag: " << tag.Get() << ", size: " << p->GetSize()
                 << ", from: " << InetSocketAddress::ConvertFrom(from).GetIpv4()
                 << ", local: " << InetSocketAddress::ConvertFrom(local).GetIpv4());
  }
  mysink_mysourceidtag2bytecount[tag.Get()] += p->GetSize();
}

// MakeBoundCallBack arg should come first
static void
TraceRtt (int source_index, Time old_rtt, Time new_rtt) {
  source2rtttrace[source_index].push_back(new_rtt.GetNanoSeconds());
  NS_LOG_DEBUG("[" << Simulator::Now ().GetNanoSeconds() << ", " << source_index << "] old_rtt: " << old_rtt << ", new_rtt: " << new_rtt);
}

Time prevTime = Seconds (0);
std::string result_dir;
uint32_t tracing_period_us = 0;
static void
TraceThroughputJFI(std::string bottleneck_fn, std::string app_fn, std::string jfi_fn)
{
  Time curTime = Now ();

  std::ofstream bottleneck_ofs(result_dir + "/" + bottleneck_fn, std::ios::out | std::ios::app);
  double total = 0.0;
  for (uint32_t i = 0; i < mysourceidtag2bytecount.size(); i++) {
    // bps
    bottleneck_ofs << std::fixed << std::setprecision (3) << 8.0*mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ()) << " ";
    // If apps start async, app_seconds_start[sourceid], but here symmetric
    avg_tpt_bottleneck[i] += (8.0*mysourceidtag2bytecount[i]/(sim_seconds-app_seconds_start));
    total += 8.0*mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ());
  }
  bottleneck_ofs << std::fixed << std::setprecision (3) << total << std::endl;

  std::ofstream app_ofs (result_dir + "/" + app_fn, std::ios::out | std::ios::app);
  total = 0.0;
  for (uint32_t i = 0; i < mysink_mysourceidtag2bytecount.size(); i++) {
    // bps
    app_ofs << std::fixed << std::setprecision (3) << 8.0*mysink_mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ()) << " ";
    avg_tpt_app[i] += (8.0*mysink_mysourceidtag2bytecount[i]/(sim_seconds-app_seconds_start));
    total += 8.0*mysink_mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ());
  }
  app_ofs << std::fixed << std::setprecision (3) << total << std::endl;

  // https://en.wikipedia.org/wiki/Fairness_measure
  std::ofstream jfi_ofs (result_dir + "/" + jfi_fn, std::ios::out | std::ios::app);
  uint64_t sum_squares_app = 0;
  uint64_t sum_app = 0;
  uint64_t sum_bottleneck = 0;  
  uint64_t sum_squares_bottleneck = 0; 
  for (uint32_t i = 0; i < mysourceidtag2bytecount.size(); i++) {
    sum_bottleneck += mysourceidtag2bytecount[i];
    // Note: use uint64_t rather than uint32_t for mysourceidtag2bytecount to prevent overflow
    sum_squares_bottleneck += (mysourceidtag2bytecount[i] * mysourceidtag2bytecount[i]);
    // Reset each period
    mysourceidtag2bytecount[i] = 0;
  }
  for (uint32_t i = 0; i < mysink_mysourceidtag2bytecount.size(); i++) {
    sum_app += mysink_mysourceidtag2bytecount[i];
    sum_squares_app += (mysink_mysourceidtag2bytecount[i] * mysink_mysourceidtag2bytecount[i]);
    // Reset each period
    mysink_mysourceidtag2bytecount[i] = 0;
  }
  double jfi_bottleneck = static_cast<double> (sum_bottleneck * sum_bottleneck) / sum_squares_bottleneck / mysourceidtag2bytecount.size();
  double jfi_app = static_cast<double> (sum_app * sum_app) / sum_squares_app / mysink_mysourceidtag2bytecount.size();

  // // Avoid NaN during first period (no traffic)
  // if (sum_squares_app != 0) {
  //   avg_jfi_bottleneck += (jfi_bottleneck/num_tracing_periods);
  //   avg_jfi_app += (jfi_app/num_tracing_periods);
  // }

  jfi_ofs << std::fixed << std::setprecision (3) << jfi_bottleneck << " "
          << std::fixed << std::setprecision (3) << jfi_app 
          << std::endl;

  prevTime = curTime;
  Simulator::Schedule(MicroSeconds(tracing_period_us), &TraceThroughputJFI, bottleneck_fn, app_fn, jfi_fn);
}

void
PrintProgress (Time interval)
{
  std::cout << "Progress: " << std::fixed << std::setprecision (1) << Simulator::Now ().GetSeconds () << "[s] simulation time" << std::endl;
  Simulator::Schedule (interval, &PrintProgress, interval);
}

int 
main (int argc, char *argv[])
{
  CommandLine cmd (__FILE__);

  // Non-configurable or derived params
  uint32_t num_leaf = 2;
  bool sack = true;  
  std::string recovery = "ns3::TcpClassicRecovery";
  uint32_t app_packet_size = 1440;
  uint32_t num_sender_pkt = 1000000000;  // Infinite demand
  // Naming the output directory using local system time
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  // https://zetcode.com/articles/cdatetime/
  strftime (buffer, sizeof (buffer), "%Y-%m-%d-%H-%M-%S-%Z", timeinfo);
  std::string current_time (buffer);
  result_dir = "tmp_index/" + current_time + "/";
  std::string create_dir_cmd = "mkdir -p " + result_dir;
  if (system (create_dir_cmd.c_str ()) == -1) exit (1);

  // CMD configurable params
  std::string config_path = "";  
  tracing_period_us = 1000000;
  uint32_t progress_interval_ms = 1000;
  bool enable_debug = 0;  
  bool logrtt = 0;
  uint32_t seed = 1;  // Fixed
  uint32_t run = 1;  // Varry across replications
  sim_seconds = 10;
  // Configure 0 will give 1000
  int switch_total_bufsize_pkts = 100;
  std::string queuedisc_type = "FifoQueueDisc";
  std::string bottleneck_bw = "5Mbps";
  std::string bottleneck_delay = "2ms";
  std::string leaf_bw = "10Mbps";
  std::string app_bw = "5Mbps";  
  uint32_t num_cca = 0;
  std::string transport_prot0 = "TcpCubic";
  std::string transport_prot1 = "TcpCubic";
  std::string transport_prot2 = "TcpCubic";
  std::string transport_prot3 = "TcpCubic";
  std::string transport_prot4 = "TcpCubic";
  std::string transport_prot5 = "TcpCubic";
  std::string transport_prot6 = "TcpCubic";
  std::string transport_prot7 = "TcpCubic";
  std::string transport_prot8 = "TcpCubic";
  std::string leaf_delay0 = "1ms";
  std::string leaf_delay1 = "1ms";
  std::string leaf_delay2 = "1ms";
  std::string leaf_delay3 = "1ms";
  std::string leaf_delay4 = "1ms";
  std::string leaf_delay5 = "1ms";
  std::string leaf_delay6 = "1ms";
  std::string leaf_delay7 = "1ms";
  std::string leaf_delay8 = "1ms";              
  uint32_t num_cca0 = 0;
  uint32_t num_cca1 = 0;
  uint32_t num_cca2 = 0;
  uint32_t num_cca3 = 0;
  uint32_t num_cca4 = 0;
  uint32_t num_cca5 = 0;
  uint32_t num_cca6 = 0;
  uint32_t num_cca7 = 0;
  uint32_t num_cca8 = 0;
  Time dt {NanoSeconds (1048576)};
  Time vdt {NanoSeconds (1024)};
  Time l {NanoSeconds (65536)};
  uint32_t p {1};
  double tau {0.05};
  double delta_port {0.05};
  double delta_flow {0.05};

  cmd.AddValue("config_path", "Path to the json configuration file", config_path);
  cmd.AddValue("seed", "Seed", seed);
  cmd.AddValue("run", "Run", run);
  cmd.AddValue ("enable_debug", "Enable logging", enable_debug);
  cmd.AddValue ("logrtt", "Enable logging of RTT (large file size)", logrtt);  
  cmd.AddValue ("sim_seconds", "Simulation time [s]", sim_seconds);
  cmd.AddValue ("app_seconds_start", "Application start time [s]", app_seconds_start);  
  cmd.AddValue ("app_seconds_end", "Application stop time [s]", app_seconds_end);
  cmd.AddValue ("tracing_period_us", "Tracing period [us]", tracing_period_us);
  cmd.AddValue ("progress_interval_ms", "Prograss interval [ms]", progress_interval_ms);    
  cmd.AddValue("num_cca", "Number of CCA groups", num_cca);
  cmd.AddValue ("transport_prot0", "Transport protocol to use: TcpNewReno, TcpLinuxReno, "
                "TcpHybla, TcpHighSpeed, TcpHtcp, TcpVegas, TcpScalable, TcpVeno, "
                "TcpBic, TcpYeah, TcpIllinois, TcpWestwood, TcpWestwoodPlus, TcpLedbat, "
		"TcpLp, TcpDctcp, TcpCubic, TcpBbr", transport_prot0);
  cmd.AddValue ("transport_prot1", "", transport_prot1);
  cmd.AddValue ("transport_prot2", "", transport_prot2);
  cmd.AddValue ("transport_prot3", "", transport_prot3);
  cmd.AddValue ("transport_prot4", "", transport_prot4);
  cmd.AddValue ("transport_prot5", "", transport_prot5);
  cmd.AddValue ("transport_prot6", "", transport_prot6);
  cmd.AddValue ("transport_prot7", "", transport_prot7);
  cmd.AddValue ("transport_prot8", "", transport_prot8);          
  cmd.AddValue ("bottleneck_bw", "BW of the bottleneck link", bottleneck_bw);
  cmd.AddValue ("bottleneck_delay", "Delay of the bottleneck link", bottleneck_delay);
  cmd.AddValue ("leaf_bw", "BW of the leaf link", leaf_bw);
  cmd.AddValue ("leaf_delay0", "Delay of the leaf links for grp0", leaf_delay0);
  cmd.AddValue ("leaf_delay1", "", leaf_delay1);  
  cmd.AddValue ("leaf_delay2", "", leaf_delay2);  
  cmd.AddValue ("leaf_delay3", "", leaf_delay3);  
  cmd.AddValue ("leaf_delay4", "", leaf_delay4);  
  cmd.AddValue ("leaf_delay5", "", leaf_delay5);  
  cmd.AddValue ("leaf_delay6", "", leaf_delay6);  
  cmd.AddValue ("leaf_delay7", "", leaf_delay7);              
  cmd.AddValue ("leaf_delay8", "", leaf_delay8);    
  cmd.AddValue ("app_bw", "BW of each application", app_bw);
  cmd.AddValue ("switch_total_bufsize_pkts", "Switch buffer size in pkts", switch_total_bufsize_pkts);
  cmd.AddValue ("queuedisc_type", "Queue Disc type", queuedisc_type);
  cmd.AddValue ("num_cca0", "Number of flows/mysource for cca0", num_cca0);
  cmd.AddValue ("num_cca1", "Number of flows/mysource for cca1", num_cca1);
  cmd.AddValue ("num_cca2", "Number of flows/mysource for cca2", num_cca2);
  cmd.AddValue ("num_cca3", "Number of flows/mysource for cca3", num_cca3);
  cmd.AddValue ("num_cca4", "Number of flows/mysource for cca4", num_cca4);
  cmd.AddValue ("num_cca5", "Number of flows/mysource for cca5", num_cca5);
  cmd.AddValue ("num_cca6", "Number of flows/mysource for cca6", num_cca6);
  cmd.AddValue ("num_cca7", "Number of flows/mysource for cca7", num_cca7);
  cmd.AddValue ("num_cca8", "Number of flows/mysource for cca8", num_cca8);
  cmd.AddValue ("dt", "CebinaeQueueDisc", dt);
  cmd.AddValue ("vdt", "CebinaeQueueDisc", vdt);
  cmd.AddValue ("l", "CebinaeQueueDisc", l);
  cmd.AddValue ("p", "CebinaeQueueDisc", p);
  cmd.AddValue ("tau", "CebinaeQueueDisc", tau);
  cmd.AddValue ("delta_port", "CebinaeQueueDisc", delta_port);
  cmd.AddValue ("delta_flow", "CebinaeQueueDisc", delta_flow);

  cmd.Parse (argc, argv);

  if (enable_debug) {
    LogComponentEnable ("CebinaeQueueDisc", LOG_LEVEL_DEBUG);
    LogComponentEnable ("DumbbellLong", LOG_LEVEL_DEBUG);
  }

  std::ifstream in_file {config_path};
  std::ofstream out_file {result_dir+"/config.json"};
  std::string line;
  if(in_file && out_file){
    while(getline(in_file, line)) { out_file << line << "\n"; }
  } else {
    printf("ERR mirroring config file");
    return 1;
  }
  in_file.close();
  out_file.close();

  transport_prot0 = std::string("ns3::") + transport_prot0;
  transport_prot1 = std::string("ns3::") + transport_prot1;
  transport_prot2 = std::string("ns3::") + transport_prot2;
  transport_prot3 = std::string("ns3::") + transport_prot3;
  transport_prot4 = std::string("ns3::") + transport_prot4;
  transport_prot5 = std::string("ns3::") + transport_prot5;
  transport_prot6 = std::string("ns3::") + transport_prot6;
  transport_prot7 = std::string("ns3::") + transport_prot7;            
  transport_prot8 = std::string("ns3::") + transport_prot8;

  if (num_cca > MAX_CCA) {
    std::cout << "ERR: " << num_cca << " > " << MAX_CCA << std::endl;
    return 1;
  }

  num_leaf = 0;
  switch(num_cca) {
    case 1:
      num_leaf = num_cca0;
      break;
    case 2:
      num_leaf = num_cca0+num_cca1;
      break;
    case 3:
      num_leaf = num_cca0+num_cca1+num_cca2;  
      break;
    case 4:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3;  
      break;
    case 5:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3+num_cca4;  
      break;      
    case 6:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5;
      break;       
    case 7:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6;
      break;         
    case 8:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7;
      break;         
    case 9:
      num_leaf = num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7+num_cca8;
      break;      
  }

  std::ostringstream oss;
  oss       << "=== Non-CMD varas ===\n"
            << "config_path: " << config_path << "\n"
            << "sack: " << sack << "\n"
            << "recovery: " << recovery << "\n"
            << "app_packet_size: " << app_packet_size << "\n"
            << "num_sender_pkt: " << num_sender_pkt << "\n"
            << "=== CMD vars ===\n"
            << "seed: " << seed << "\n"
            << "run: " << run << "\n"
            << "tracing_period_us: " << tracing_period_us << "\n"   
            << "progress_interval_ms: " << progress_interval_ms << "\n"         
            << "sim_seconds: " << sim_seconds << "\n"
            << "app_seconds_start: " << app_seconds_start << "\n"
            << "app_seconds_end: " << app_seconds_end << "\n"
            << "transport_prot0: " << transport_prot0 << "\n"
            << "transport_prot1: " << transport_prot1 << "\n"
            << "transport_prot2: " << transport_prot2 << "\n"
            << "transport_prot3: " << transport_prot3 << "\n"
            << "transport_prot4: " << transport_prot4 << "\n"
            << "transport_prot5: " << transport_prot5 << "\n"
            << "transport_prot6: " << transport_prot6 << "\n"
            << "transport_prot7: " << transport_prot7 << "\n"
            << "transport_prot8: " << transport_prot8 << "\n"
            << "bottleneck_bw: " << bottleneck_bw << "\n"
            << "bottleneck_delay: " << bottleneck_delay << "\n"
            << "leaf_bw: " << leaf_bw << "\n"
            << "leaf_delay0: " << leaf_delay0 << "\n"
            << "leaf_delay1: " << leaf_delay1 << "\n"
            << "leaf_delay2: " << leaf_delay2 << "\n"
            << "leaf_delay3: " << leaf_delay3 << "\n"
            << "leaf_delay4: " << leaf_delay4 << "\n"
            << "leaf_delay5: " << leaf_delay5 << "\n"
            << "leaf_delay6: " << leaf_delay6 << "\n"
            << "leaf_delay7: " << leaf_delay7 << "\n"
            << "leaf_delay8: " << leaf_delay8 << "\n"
            << "app_bw: " << app_bw << "\n"
            << "switch_total_bufsize_pkts: " << switch_total_bufsize_pkts << "\n"
            << "queuedisc_type: " << queuedisc_type << "\n"
            << "num_cca0: " << num_cca0 << "\n"
            << "num_cca1: " << num_cca1 << "\n"
            << "num_cca2: " << num_cca2 << "\n"
            << "num_cca3: " << num_cca3 << "\n"
            << "num_cca4: " << num_cca4 << "\n"
            << "num_cca5: " << num_cca5 << "\n"
            << "num_cca6: " << num_cca6 << "\n"
            << "num_cca7: " << num_cca7 << "\n"
            << "num_cca8: " << num_cca8 << "\n"
            << "num_leaf: " << num_leaf << "\n"
            << "======\n";

  RngSeedManager::SetSeed (seed);
  RngSeedManager::SetRun (run);

  NS_LOG_DEBUG("================== Topology: dumbell (leaf=2) ==================");

  NodeContainer router;
  NodeContainer leftleaf;
  NodeContainer rightleaf;
  router.Create (2);
  leftleaf.Create (num_leaf);
  rightleaf.Create (num_leaf);

  PointToPointHelper p2p_bottleneck;
  p2p_bottleneck.SetDeviceAttribute ("DataRate", StringValue (bottleneck_bw));
  p2p_bottleneck.SetChannelAttribute ("Delay", StringValue (bottleneck_delay));
  PointToPointHelper p2p_leaf0;
  p2p_leaf0.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf0.SetChannelAttribute ("Delay", StringValue (leaf_delay0));
  PointToPointHelper p2p_leaf1;
  p2p_leaf1.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf1.SetChannelAttribute ("Delay", StringValue (leaf_delay1));  
  PointToPointHelper p2p_leaf2;
  p2p_leaf2.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf2.SetChannelAttribute ("Delay", StringValue (leaf_delay2));  
  PointToPointHelper p2p_leaf3;
  p2p_leaf3.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf3.SetChannelAttribute ("Delay", StringValue (leaf_delay3));  
  PointToPointHelper p2p_leaf4;
  p2p_leaf4.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf4.SetChannelAttribute ("Delay", StringValue (leaf_delay4));  
  PointToPointHelper p2p_leaf5;
  p2p_leaf5.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf5.SetChannelAttribute ("Delay", StringValue (leaf_delay5));  
  PointToPointHelper p2p_leaf6;
  p2p_leaf6.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf6.SetChannelAttribute ("Delay", StringValue (leaf_delay6)); 
  PointToPointHelper p2p_leaf7;
  p2p_leaf7.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf7.SetChannelAttribute ("Delay", StringValue (leaf_delay7)); 
  PointToPointHelper p2p_leaf8;
  p2p_leaf8.SetDeviceAttribute ("DataRate", StringValue (leaf_bw));
  p2p_leaf8.SetChannelAttribute ("Delay", StringValue (leaf_delay8));        

  // Unclear of the right configuration, use default as it seems to match real world models more than using 1p
  // PointToPointHelper default: m_queueFactory.SetTypeId ("ns3::DropTailQueue<Packet>"); ns3::DropTailQueue default MaxSize is 100p
  // p2p_bottleneck.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue ("1p"));
  // p2p_leaf.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue ("1p"));

  NetDeviceContainer leftleaf_devices;
  NetDeviceContainer rightleaf_devices;
  NetDeviceContainer router_devices;
  NetDeviceContainer leftrouter_devices;
  NetDeviceContainer rightrouter_devices;

  router_devices = p2p_bottleneck.Install(router);

  for (uint32_t i = 0; i < num_leaf; ++i) {
    NetDeviceContainer cl;
    NetDeviceContainer cr;    
    if (i < num_cca0) {
      cl = p2p_leaf0.Install(router.Get (0),
                            leftleaf.Get (i));
      cr = p2p_leaf0.Install(router.Get (1),
                            rightleaf.Get (i));                            
    } else if (i < (num_cca0+num_cca1)) {
      cl= p2p_leaf1.Install(router.Get (0),
                      leftleaf.Get (i));
      cr = p2p_leaf1.Install(router.Get (1),
                            rightleaf.Get (i));                        
    } else if (i < (num_cca0+num_cca1+num_cca2)) {
      cl = p2p_leaf2.Install(router.Get (0),
                      leftleaf.Get (i));  
      cr = p2p_leaf2.Install(router.Get (1),
                            rightleaf.Get (i));                            
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3)) {
      cl = p2p_leaf3.Install(router.Get (0),
                      leftleaf.Get (i));    
      cr = p2p_leaf3.Install(router.Get (1),
                            rightleaf.Get (i));                          
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4)) {
      cl = p2p_leaf4.Install(router.Get (0),
                      leftleaf.Get (i)); 
      cr = p2p_leaf4.Install(router.Get (1),
                            rightleaf.Get (i));                             
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5)) {
      cl = p2p_leaf5.Install(router.Get (0),
                      leftleaf.Get (i));
      cr = p2p_leaf5.Install(router.Get (1),
                            rightleaf.Get (i));                          
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6)) {
      cl = p2p_leaf6.Install(router.Get (0),
                      leftleaf.Get (i)); 
      cr = p2p_leaf6.Install(router.Get (1),
                            rightleaf.Get (i));                         
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7)) {
      cl = p2p_leaf7.Install(router.Get (0),
                      leftleaf.Get (i));  
      cr = p2p_leaf7.Install(router.Get (1),
                            rightleaf.Get (i));                        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7+num_cca8)) {
      cl = p2p_leaf8.Install(router.Get (0),
                      leftleaf.Get (i)); 
      cr = p2p_leaf8.Install(router.Get (1),
                            rightleaf.Get (i));                         
    }                                    
    leftrouter_devices.Add (cl.Get (0));
    leftleaf_devices.Add (cl.Get (1));
    rightrouter_devices.Add (cr.Get (0));
    rightleaf_devices.Add (cr.Get (1));    
  }

  NS_LOG_DEBUG("================== InternetStackHelper ==================");

  InternetStackHelper stack;
  for (uint32_t i = 0; i < num_leaf; ++i) {
    stack.Install (leftleaf.Get(i));
  }
  for (uint32_t i = 0; i < num_leaf; ++i) {
    stack.Install (rightleaf.Get(i));
  }
  stack.Install(router.Get(0));
  stack.Install(router.Get(1));

  NS_LOG_DEBUG("================== Install TCP transport ==================");
  // 2 MB of TCP buffer
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (1 << 21));
  Config::SetDefault ("ns3::TcpSocket::SndBufSize", UintegerValue (1 << 21));
  // By default, MSS = ~500
  // IP MTU = IP header (>=20B) + TCP header (20B) + TCP MSS
  // Ethernet frame = Ethernet header (14B) + IP MTU + FCS (4B)
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (app_packet_size));
  Config::SetDefault ("ns3::TcpSocketBase::Sack", BooleanValue (sack));
  // Config::SetDefault ("ns3::TcpSocket::InitialCwnd", UintegerValue (10));
  // Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (delAckCount));
  // Config::SetDefault ("ns3::TcpSocketBase::MinRto", TimeValue (Seconds (minRto)));
  Config::SetDefault ("ns3::TcpL4Protocol::RecoveryType",
                      TypeIdValue (TypeId::LookupByName (recovery)));

  TypeId tcpTid;
  bool ok = TypeId::LookupByNameFailSafe (transport_prot0, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot0 << " not found" << std::endl;
    exit(1);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot1, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot1 << " not found" << std::endl;
    exit(1);
  }   
  ok = TypeId::LookupByNameFailSafe (transport_prot2, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot2 << " not found" << std::endl;
    exit(1);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot3, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot3 << " not found" << std::endl;
    exit(3);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot4, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot4 << " not found" << std::endl;
    exit(1);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot5, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot5 << " not found" << std::endl;
    exit(1);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot6, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot6 << " not found" << std::endl;
    exit(1);
  }  
  ok = TypeId::LookupByNameFailSafe (transport_prot7, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot7 << " not found" << std::endl;
    exit(1);
  }          
  ok = TypeId::LookupByNameFailSafe (transport_prot8, &tcpTid);
  if (!ok) {
    std::cout << "TypeId " << transport_prot8 << " not found" << std::endl;
    exit(1);
  }          
  Ptr<TcpL4Protocol> protol;
  Ptr<TcpL4Protocol> protor;  
  for (uint32_t i = 0; i < num_leaf; ++i) {
    protol = leftleaf.Get(i)->GetObject<TcpL4Protocol> ();    
    protor = rightleaf.Get(i)->GetObject<TcpL4Protocol> ();
    if (i < num_cca0) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot0)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot0)));      
    } else if (i < (num_cca0+num_cca1)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot1)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot1)));        
    } else if (i < (num_cca0+num_cca1+num_cca2)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot2)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot2)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot3)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot3)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot4)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot4)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot5)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot5)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot6)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot6)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot7)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot7)));        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7+num_cca8)) {
      protol->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot8)));
      protor->SetAttribute ("SocketType", TypeIdValue (TypeId::LookupByName(transport_prot8)));        
    }                                    
  }
  // if (transport_prot.compare ("ns3::TcpWestwoodPlus") == 0)
  //   { 
  //     // TcpWestwoodPlus is not an actual TypeId name; we need TcpWestwood here
  //     Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TcpWestwood::GetTypeId ()));
  //     // the default protocol type in ns3::TcpWestwood is WESTWOOD
  //     Config::SetDefault ("ns3::TcpWestwood::ProtocolType", EnumValue (TcpWestwood::WESTWOODPLUS));
  //   }
  // Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (transport_prot)));    

  // Ptr<RateErrorModel> em = CreateObject<RateErrorModel> ();
  // em->SetAttribute ("ErrorRate", DoubleValue (0.00001));
  // devices.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));

  NS_LOG_DEBUG("================== Configure TrafficControlLayer ==================");
  // Manual: To install a queue disc other than the default one, it is necessary to install such queue disc before an IP address is
  // assigned to the device, but after InternetStackHelper::Install(). Alternatively, the default queue disc can be removed from the device after assigning an IP
  // address, by using the Uninstall method of the TrafficControlHelper C++ class, and then installing a different queue
  // disc on the device. By uninstalling without adding a new queue disc, it is also possible to have no queue disc installed
  // on a device.

  // We keep the tch default ns3::FqCoDelQueueDisc (for point-to-point) untouched for sources and sinks.
  // Such DRR fair queueing (https://www.nsnam.org/docs/models/html/fq-codel.html) is useful upon multiple apps on a single sender node.

  // NetDevice switch0 [only tch to change] ---> switch1
  TrafficControlHelper tch_switch;
  QueueDiscContainer qdiscs;
  if (queuedisc_type.compare("FifoQueueDisc") == 0) {
    tch_switch.SetRootQueueDisc ("ns3::FifoQueueDisc", "MaxSize", StringValue (std::to_string(switch_total_bufsize_pkts)+"p"));
    qdiscs = tch_switch.Install(router_devices.Get(0));
    Ptr<QueueDisc> q = qdiscs.Get (0);
    oss << "Configured FifoQueueDisc\n";
  } else if (queuedisc_type.compare("CebinaeQueueDisc") == 0) {
    Config::SetDefault ("ns3::CebinaeQueueDisc::dT", TimeValue (dt));
    Config::SetDefault ("ns3::CebinaeQueueDisc::vdT", TimeValue (vdt));
    Config::SetDefault ("ns3::CebinaeQueueDisc::L", TimeValue (l));
    Config::SetDefault ("ns3::CebinaeQueueDisc::P", UintegerValue (p));
    Config::SetDefault ("ns3::CebinaeQueueDisc::tau", DoubleValue (tau));
    Config::SetDefault ("ns3::CebinaeQueueDisc::delta_port", DoubleValue (delta_port));
    Config::SetDefault ("ns3::CebinaeQueueDisc::delta_flow", DoubleValue (delta_flow));
    Config::SetDefault ("ns3::CebinaeQueueDisc::DataRate", StringValue (bottleneck_bw));

    tch_switch.SetRootQueueDisc ("ns3::CebinaeQueueDisc", "MaxSize", StringValue (std::to_string(switch_total_bufsize_pkts)+"p"));

    qdiscs = tch_switch.Install(router_devices.Get(0));
    Ptr<QueueDisc> q = qdiscs.Get (0);
    oss << "--- Configured CebinaeQueueDisc ---\n"
        << "dt: " << dt << "\n"
        << "vdt: " << vdt << "\n"
        << "l: " << l << "\n"
        << "p: " << p << "\n"
        << "tau: " << tau << "\n"
        << "delta_port: " << delta_port << "\n"
        << "delta_flow: " << delta_flow << "\n"
        << "------\n";
    // DynamicCast<Ptr<CebinaeQueueDisc>>(q)->Configure(Time dt, Time vdt, uint32_t p, double tau, double delta);
  } else if (queuedisc_type.compare("FqCoDelQueueDisc") == 0) {
    tch_switch.SetRootQueueDisc ("ns3::FqCoDelQueueDisc", "MaxSize", StringValue (std::to_string(switch_total_bufsize_pkts)+"p"),
                                                          "Flows", UintegerValue (4294967295));
    qdiscs = tch_switch.Install(router_devices.Get(0));    
    oss << "Configured FqCoDelQueueDisc\n";
  } else {
    oss << "Configured NULL QueueDisc (which is the default FqCoDelQueueDisc and buffer size)\n";
  }
  // q->TraceConnectWithoutContext ("PacketsInQueue", MakeCallback (&TcPacketsInQueueTrace));  
  // SojournTime
  // Ptr<NetDevice> nd = devices.Get (1);
  // Ptr<PointToPointNetDevice> ptpnd = DynamicCast<PointToPointNetDevice> (nd);
  // Ptr<Queue<Packet> > queue = ptpnd->GetQueue ();
  // queue->TraceConnectWithoutContext ("PacketsInQueue", MakeCallback (&DevicePacketsInQueueTrace));

  NS_LOG_DEBUG("================== Configure Ipv4AddressHelper ==================");

  Ipv4AddressHelper ipv4_left;
  ipv4_left.SetBase ("10.1.1.0", "255.255.255.0");  
  Ipv4AddressHelper ipv4_right("10.2.1.0", "255.255.255.0");
  Ipv4AddressHelper ipv4_router("10.3.1.0", "255.255.255.0");

  Ipv4InterfaceContainer leftleaf_ifc;
  Ipv4InterfaceContainer leftrouter_ifc;
  Ipv4InterfaceContainer rightleaf_ifc;
  Ipv4InterfaceContainer rightrouter_ifc;
  Ipv4InterfaceContainer router_ifc;

  router_ifc = ipv4_router.Assign (router_devices);
  for (uint32_t i = 0; i < num_leaf; ++i) {
    NetDeviceContainer ndc;
    ndc.Add (leftleaf_devices.Get (i));
    ndc.Add (leftrouter_devices.Get (i));
    Ipv4InterfaceContainer ifc = ipv4_left.Assign (ndc);
    leftleaf_ifc.Add (ifc.Get (0));
    leftrouter_ifc.Add (ifc.Get (1));
    ipv4_left.NewNetwork ();
  } 
  for (uint32_t i = 0; i < num_leaf; ++i) {
    NetDeviceContainer ndc;
    ndc.Add (rightleaf_devices.Get (i));
    ndc.Add (rightrouter_devices.Get (i));
    Ipv4InterfaceContainer ifc = ipv4_right.Assign (ndc);
    rightleaf_ifc.Add (ifc.Get (0));
    rightrouter_ifc.Add (ifc.Get (1));
    ipv4_right.NewNetwork ();
  }  

  NS_LOG_DEBUG("================== Generate application ==================");

  // We want to look at changes in the ns-3 TCP congestion window:
  // 1. Create a socket
  // 2. Hook the CongestionWindow attribute and do the trace connect
  // 3. Pass the socket into the constructor of our simple application which we then install in the source node
  Ptr<MySource>* sources;
  sources = new Ptr<MySource>[num_leaf];
  for (uint32_t i = 0; i < num_leaf; ++i) {
    uint16_t sinkPort = 8080;
    Address sinkAddress (InetSocketAddress (rightleaf_ifc.GetAddress(i), sinkPort));
    // PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort)); 
    // ApplicationContainer sinkApps = packetSinkHelper.Install (rightleaf.Get(i));
    Ptr<MySink> sink = CreateObject<MySink> ();
    sink->SetAttribute ("Protocol", StringValue ("ns3::TcpSocketFactory"));
    sink->SetAttribute ("Local", AddressValue (InetSocketAddress (Ipv4Address::GetAny (), sinkPort)));
    rightleaf.Get(i)->AddApplication(sink);
    sink->SetStartTime (Seconds (0.));
    sink->SetStopTime (Seconds (app_seconds_end));  

    sink->TraceConnectWithoutContext("RxWithAddresses", MakeCallback(&RxWithAddressesMySink));

    Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (leftleaf.Get (i), TcpSocketFactory::GetTypeId ());
    if (logrtt) {
      // ns3TcpSocket->TraceConnectWithoutContext("RTT", MakeBoundCallback (&TraceRtt, i));
      Config::ConnectWithoutContext ("/NodeList/"+std::to_string(2+i)+"/$ns3::TcpL4Protocol/SocketList/0/RTT", MakeBoundCallback (&TraceRtt, i));
    }

    // Monitor CongestionWindow
    // if (i == 0) {
    //   ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeCallback (&CwndChange));
    // }
    Ptr<MySource> app = CreateObject<MySource> ();
    app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, num_sender_pkt, DataRate (app_bw), i, false);
    leftleaf.Get (i)->AddApplication (app);
    app->SetStartTime (Seconds (app_seconds_start));
    app->SetStopTime (Seconds (app_seconds_end));
    // if (i == 0) {
    //   rightleaf_devices.Get(i)->TraceConnectWithoutContext ("PhyRxDrop", MakeCallback (&RxDrop));
    // }
    sources[i] = app;
  }

  NS_LOG_DEBUG("================== Tracing ==================");
  // Tracing PointToPointNetDevice
  router_devices.Get(0)->TraceConnectWithoutContext("PhyTxEnd", MakeCallback (&PhyTxEndCb));
  // The other NetDevice only transmits ACK packets
  // router_devices.Get(1)->TraceConnectWithoutContext("PhyTxEnd", MakeCallback (&PhyTxEndCb));
  mysourceidtag2bytecount.resize(num_leaf, 0);
  mysink_mysourceidtag2bytecount.resize(num_leaf, 0);
  avg_tpt_bottleneck.resize(num_leaf, 0);
  avg_tpt_app.resize(num_leaf, 0);
  for (uint32_t sourceid = 0; sourceid < num_leaf; sourceid ++) {
    source2rtttrace.push_back(std::vector<int64_t>());
  }
  num_tracing_periods = sim_seconds/(tracing_period_us/pow(10, 6));
  oss << "num_tracing_periods: " << num_tracing_periods << "\n";

  Simulator::Schedule(MicroSeconds(0+tracing_period_us), &TraceThroughputJFI, 
                      "bottleneck_tpt_"+std::to_string(tracing_period_us)+".dat",
                      "app_tpt_"+std::to_string(tracing_period_us)+".dat",
                      "jfi_"+std::to_string(tracing_period_us)+".dat");

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Schedule (MilliSeconds(progress_interval_ms), &PrintProgress, MilliSeconds(progress_interval_ms));

  NS_LOG_DEBUG("================== Run ==================");

  Simulator::Stop (Seconds (sim_seconds));
  auto start = std::chrono::high_resolution_clock::now();
  Simulator::Run ();
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = stop - start;

  std::cout << elapsed_seconds.count() << "s" << std::endl;
  oss << "=== elapsed_seconds: " << elapsed_seconds.count() << "===\n";

  // Calculate overall JFI
  long double sum = 0.0;
  long double sum_squares = 0.0;  
  oss << "=== avg_tpt_bottleneck[*] ===\n";
  for (uint32_t i = 0; i < avg_tpt_bottleneck.size(); i++) {
    sum += avg_tpt_bottleneck[i];
    sum_squares += (avg_tpt_bottleneck[i] * avg_tpt_bottleneck[i]);
    oss << std::fixed << std::setprecision (3) << i << " " << avg_tpt_bottleneck[i] << "\n";
  }
  oss << std::fixed << std::setprecision (3) << "avg_tpt_bottleneck_total: " << sum << "\n";
  oss << std::fixed << std::setprecision (3) << "avg_jfi_bottleneck [computed]: " << (sum*sum)/avg_tpt_bottleneck.size()/sum_squares << "\n";

  sum = 0.0;
  sum_squares = 0.0;
  oss << "=== avg_tpt_app[*] ===\n";
  for (uint32_t i = 0; i < avg_tpt_app.size(); i++) {
    sum += avg_tpt_app[i];
    sum_squares += (avg_tpt_app[i] * avg_tpt_app[i]);
    oss << std::fixed << std::setprecision (3) << i << " " << avg_tpt_app[i] << "\n";
  }
  oss << std::fixed << std::setprecision (3) << "avg_tpt_app_total: " << sum << "\n";
  oss << std::fixed << std::setprecision (3) << "avg_jfi_app [computed]: " << (sum*sum)/avg_tpt_app.size()/sum_squares << "\n";
  
  // oss << std::fixed << std::setprecision (3) << "avg_jfi_bottleneck: " << avg_jfi_bottleneck << "\n"
  //     << std::fixed << std::setprecision (3) << "avg_jfi_app: " << avg_jfi_app << "\n";

  // Calculate avg. RTT and write RTT traces
  if (logrtt) {
    for (uint16_t sourceid = 0; sourceid < num_leaf; sourceid++) {
      std::ofstream rtt_ofs (result_dir + "/rtt_"+std::to_string(sourceid)+".dat", std::ios::out | std::ios::app);
      int num_rtt_samples = source2rtttrace[sourceid].size();
      double avg_rtt_ns = 0.0;
      for (int i = 0; i < num_rtt_samples; i++) {
        rtt_ofs << source2rtttrace[sourceid][i] << "\n";
        avg_rtt_ns += static_cast<double>(source2rtttrace[sourceid][i])/num_rtt_samples;
      }
      oss << "# of RTT samples for source " << sourceid << ": " << num_rtt_samples << "\n";
      oss << "Avg. RTT for source " << sourceid << ": " << avg_rtt_ns << "ns\n";
    }
  }

  oss << "====== Number of packets sent ======\n";
  for (uint32_t sourceid = 0; sourceid < num_leaf; sourceid++) {
    oss << "MySource " << sourceid << ":" << sources[sourceid]->GetPacketsSent() << "\n";
  }

  oss << "====== Number of packets at bottleneck link ======\n";
  for (auto iter=mysourceidtag2pktcount.begin(); iter!=mysourceidtag2pktcount.end(); iter++) {
    oss << "Source " << iter->first << ": " << iter->second << "\n";
  }
  
  oss << "====== CebinaeQueueDisc debugging stats ======\n";
  if (queuedisc_type.compare("CebinaeQueueDisc") == 0) {
    Ptr<QueueDisc> q = qdiscs.Get(0);
    oss << DynamicCast<CebinaeQueueDisc>(q)->DumpDebuggingStats();    
  }

  std::ofstream summary_ofs (result_dir + "/digest", std::ios::out | std::ios::app);  
  summary_ofs << oss.str();

  std::cout << oss.str() << std::endl;
  std::cout << "Folder timestamp/name for experiment index: " << current_time << std::endl;

  Simulator::Destroy ();

  return 0;
}

