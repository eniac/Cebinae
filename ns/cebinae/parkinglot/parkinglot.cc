#include <chrono>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/my-source-id-tag.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/traffic-control-module.h"

#include "../dumbbell_long/my-source.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("Parkinglot");

#define MAX_CCA 9

std::vector<double> avg_tpt_app;  // This is actually goodput
// double avg_jfi_bottleneck = 0.0;
// double avg_jfi_app = 0.0;

int num_tracing_periods = 0;
double sim_seconds = 1;
double app_seconds_start = 0.1;
double app_seconds_end = 10;

std::vector<std::uint64_t> packetsink_mysourceidtag2bytecount;
static void
RxWithAddressesPacketSink (Ptr<const Packet> p, const Address& from, const Address& local) {
  MySourceIDTag tag;
  if (p->FindFirstMatchingByteTag(tag)) {
    // NS_LOG_DEBUG ("[" << Simulator::Now ().GetNanoSeconds() << "] SourceIDTag: " << tag.Get() << ", size: " << p->GetSize()
    //              << ", from: " << InetSocketAddress::ConvertFrom(from).GetIpv4()
    //              << ", local: " << InetSocketAddress::ConvertFrom(local).GetIpv4());
  }
  packetsink_mysourceidtag2bytecount[tag.Get()] += p->GetSize();
}

Time prevTime = Seconds (0);
std::string result_dir;
uint32_t tracing_period_us = 0;
static void
TraceThroughputJFI(std::string bottleneck_fn, std::string app_fn, std::string jfi_fn)
{
  Time curTime = Now ();

  std::ofstream app_ofs (result_dir + "/" + app_fn, std::ios::out | std::ios::app);
  double total = 0.0;
  for (uint32_t i = 0; i < packetsink_mysourceidtag2bytecount.size(); i++) {
    // bps
    app_ofs << std::fixed << std::setprecision (3) << 8.0*packetsink_mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ()) << " ";
    avg_tpt_app[i] += (8.0*packetsink_mysourceidtag2bytecount[i]/(sim_seconds-app_seconds_start));
    total += 8.0*packetsink_mysourceidtag2bytecount[i]/(curTime.GetSeconds () - prevTime.GetSeconds ());
  }
  app_ofs << std::fixed << std::setprecision (3) << total << std::endl;

  // std::ofstream jfi_ofs (result_dir + "/" + jfi_fn, std::ios::out | std::ios::app);
  // uint64_t sum_squares_app = 0;
  // uint64_t sum_app = 0;
  for (uint32_t i = 0; i < packetsink_mysourceidtag2bytecount.size(); i++) {
    // sum_app += packetsink_mysourceidtag2bytecount[i];
    // sum_squares_app += (packetsink_mysourceidtag2bytecount[i] * packetsink_mysourceidtag2bytecount[i]);
    // Reset each period
    packetsink_mysourceidtag2bytecount[i] = 0;
  }
  // double jfi_app = static_cast<double> (sum_app * sum_app) / sum_squares_app / packetsink_mysourceidtag2bytecount.size();

  // // Avoid NaN during first period (no traffic)
  // if (sum_squares_app != 0) {
  //   avg_jfi_bottleneck += (jfi_bottleneck/num_tracing_periods);
  //   avg_jfi_app += (jfi_app/num_tracing_periods);
  // }

  // jfi_ofs << std::fixed << std::setprecision (3) << jfi_app 
  //         << std::endl;

  prevTime = curTime;
  Simulator::Schedule(MicroSeconds(tracing_period_us), &TraceThroughputJFI, bottleneck_fn, app_fn, jfi_fn);
}

bool printprogress = true;
void
PrintProgress (Time interval)
{
  std::cout << "[PID:" << getpid() << "] Progress: " << std::fixed << std::setprecision (1) << Simulator::Now ().GetSeconds () << "[s]" << std::endl;
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

  // CMD configurable params
  std::string config_path = "";  
  tracing_period_us = 1000000;
  uint32_t progress_interval_ms = 1000;
  bool enable_debug = 0;  
  bool skip_run = 0;    
  bool logtcp = 0;
  bool enable_stdout = 1; 
  uint32_t seed = 1;  // Fixed
  uint32_t run = 1;  // Varry across replications
  sim_seconds = 10;
  uint32_t delackcount = 1;
  std::string switch_netdev_size = "100p";
  std::string server_netdev_size = "100p";  
  uint32_t app_packet_size = 1440;  
  // Configure 0 will give 1000
  std::string switch_total_bufsize = "100p";
  std::string queuedisc_type = "FifoQueueDisc";
  std::string bottleneck_bw = "5Mbps";
  std::string bottleneck_delay = "2ms";
  std::string leaf_bw0 = "0Mbps";
  std::string leaf_bw1 = "0Mbps";
  std::string leaf_bw2 = "0Mbps";
  std::string leaf_bw3 = "0Mbps";
  std::string leaf_bw4 = "0Mbps";
  std::string leaf_bw5 = "0Mbps";
  std::string leaf_bw6 = "0Mbps";
  std::string leaf_bw7 = "0Mbps";
  std::string leaf_bw8 = "0Mbps";
  std::string app_bw0 = "0Mbps";  
  std::string app_bw1 = "0Mbps"; 
  std::string app_bw2 = "0Mbps"; 
  std::string app_bw3 = "0Mbps"; 
  std::string app_bw4 = "0Mbps"; 
  std::string app_bw5 = "0Mbps"; 
  std::string app_bw6 = "0Mbps"; 
  std::string app_bw7 = "0Mbps"; 
  std::string app_bw8 = "0Mbps";                 
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
  bool pool = 0;

  cmd.AddValue("config_path", "Path to the json configuration file", config_path);
  cmd.AddValue("result_dir", "Optional path to the output dir", result_dir);  
  cmd.AddValue("seed", "Seed", seed);
  cmd.AddValue("run", "Run", run);
  cmd.AddValue ("enable_debug", "Enable logging", enable_debug);
  cmd.AddValue ("pool", "Enable pool", pool);  
  cmd.AddValue ("logtcp", "Enable logging of TCP traces, such as RTT, RTO, cwnd (large file size)", logtcp);  
  cmd.AddValue ("enable_stdout", "Enable verbose rmterminal print", enable_stdout);  
  cmd.AddValue ("printprogress", "Enable verbose rmterminal print", printprogress);
  cmd.AddValue ("skip_run", "Skip running if result_dir/digest exists", skip_run);      
  cmd.AddValue ("sim_seconds", "Simulation time [s]", sim_seconds);
  cmd.AddValue ("app_seconds_start", "Application start time [s]", app_seconds_start);  
  cmd.AddValue ("app_seconds_end", "Application stop time [s]", app_seconds_end);
  cmd.AddValue ("tracing_period_us", "Tracing period [us]", tracing_period_us);
  cmd.AddValue ("progress_interval_ms", "Prograss interval [ms]", progress_interval_ms);    
  cmd.AddValue ("delackcount", "TcpSocket::DelAckCount", delackcount);  
  cmd.AddValue ("app_packet_size", "App payload size", app_packet_size);    
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
  cmd.AddValue ("leaf_bw0", "BW of the leaf link grp 0", leaf_bw0);
  cmd.AddValue ("leaf_bw1", "", leaf_bw1);
  cmd.AddValue ("leaf_bw2", "", leaf_bw2);
  cmd.AddValue ("leaf_bw3", "", leaf_bw3);
  cmd.AddValue ("leaf_bw4", "", leaf_bw4);
  cmd.AddValue ("leaf_bw5", "", leaf_bw5);
  cmd.AddValue ("leaf_bw6", "", leaf_bw6);
  cmd.AddValue ("leaf_bw7", "", leaf_bw7);
  cmd.AddValue ("leaf_bw8", "", leaf_bw8);                
  cmd.AddValue ("leaf_delay0", "Delay of the leaf links for grp0", leaf_delay0);
  cmd.AddValue ("leaf_delay1", "", leaf_delay1);  
  cmd.AddValue ("leaf_delay2", "", leaf_delay2);  
  cmd.AddValue ("leaf_delay3", "", leaf_delay3);  
  cmd.AddValue ("leaf_delay4", "", leaf_delay4);  
  cmd.AddValue ("leaf_delay5", "", leaf_delay5);  
  cmd.AddValue ("leaf_delay6", "", leaf_delay6);  
  cmd.AddValue ("leaf_delay7", "", leaf_delay7);              
  cmd.AddValue ("leaf_delay8", "", leaf_delay8);    
  cmd.AddValue ("app_bw0", "BW of each application", app_bw0);
  cmd.AddValue ("app_bw1", "", app_bw1);  
  cmd.AddValue ("app_bw2", "", app_bw2);  
  cmd.AddValue ("app_bw3", "", app_bw3);  
  cmd.AddValue ("app_bw4", "", app_bw4);  
  cmd.AddValue ("app_bw5", "", app_bw5);  
  cmd.AddValue ("app_bw6", "", app_bw6);  
  cmd.AddValue ("app_bw7", "", app_bw7);  
  cmd.AddValue ("app_bw8", "", app_bw8);                
  cmd.AddValue ("switch_netdev_size", "Netdevice queue size (switch)", switch_netdev_size);  
  cmd.AddValue ("server_netdev_size", "Netdevice queue size (server)", server_netdev_size);    
  cmd.AddValue ("switch_total_bufsize", "Switch buffer size", switch_total_bufsize);
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
    LogComponentEnable ("Parkinglot", LOG_LEVEL_DEBUG);
  }

  if (skip_run) {
    std::ifstream digest_file;
    digest_file.open(result_dir+"/digest");
    if (digest_file) {
      std::cout << "Skip run per existence of " << result_dir << "/digest" << std::endl;
      return 0;
    }
  }

  std::string rm_dir_cmd = "rm -rf " + result_dir;
  if (system (rm_dir_cmd.c_str ()) == -1) {
    std::cout << "ERR: " << rm_dir_cmd << " failed, proceed anyway." << std::endl;
  };
  std::string create_dir_cmd = "mkdir -p " + result_dir;
  if (system (create_dir_cmd.c_str ()) == -1) {
    std::cout << "ERR: " << create_dir_cmd << " failed, proceed anyway." << std::endl;
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
  oss       << "=== CMD varas ===\n"
            << "enable_debug: " << std::boolalpha << enable_debug << "\n" 
            << "enable_stdout: " << std::boolalpha << enable_stdout << "\n"      
            << "printprogress: " << std::boolalpha << printprogress << "\n"
            << "skip_run: " << std::boolalpha << skip_run << "\n"            
            << "config_path: " << config_path << "\n"
            << "result_dir: " << result_dir << "\n"
            << "sack: " << sack << "\n"
            << "recovery: " << recovery << "\n"
            << "app_packet_size: " << app_packet_size << "\n"            
            << "delackcount: " << delackcount << "\n"
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
            << "leaf_bw0: " << leaf_bw0 << "\n"
            << "leaf_bw1: " << leaf_bw1 << "\n"
            << "leaf_bw2: " << leaf_bw2 << "\n"
            << "leaf_bw3: " << leaf_bw3 << "\n"
            << "leaf_bw4: " << leaf_bw4 << "\n"
            << "leaf_bw5: " << leaf_bw5 << "\n"
            << "leaf_bw6: " << leaf_bw6 << "\n"
            << "leaf_bw7: " << leaf_bw7 << "\n"
            << "leaf_bw8: " << leaf_bw8 << "\n"                                                                                                
            << "leaf_delay0: " << leaf_delay0 << "\n"
            << "leaf_delay1: " << leaf_delay1 << "\n"
            << "leaf_delay2: " << leaf_delay2 << "\n"
            << "leaf_delay3: " << leaf_delay3 << "\n"
            << "leaf_delay4: " << leaf_delay4 << "\n"
            << "leaf_delay5: " << leaf_delay5 << "\n"
            << "leaf_delay6: " << leaf_delay6 << "\n"
            << "leaf_delay7: " << leaf_delay7 << "\n"
            << "leaf_delay8: " << leaf_delay8 << "\n"
            << "app_bw0: " << app_bw0 << "\n"
            << "app_bw1: " << app_bw1 << "\n"
            << "app_bw2: " << app_bw2 << "\n"
            << "app_bw3: " << app_bw3 << "\n"
            << "app_bw4: " << app_bw4 << "\n"
            << "app_bw5: " << app_bw5 << "\n"
            << "app_bw6: " << app_bw6 << "\n"
            << "app_bw7: " << app_bw7 << "\n"                                                                                    
            << "app_bw8: " << app_bw8 << "\n"            
            << "switch_total_bufsize: " << switch_total_bufsize << "\n"
            << "switch_netdev_size: " << switch_netdev_size << "\n"
            << "server_netdev_size: " << server_netdev_size << "\n"            
            << "queuedisc_type: " << queuedisc_type << "\n"
            << "num_cca: " << num_cca << "\n"
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

  if (enable_debug) std::cout << oss.str() << std::endl;

  RngSeedManager::SetSeed (seed);
  RngSeedManager::SetRun (run);

  if (enable_debug) std::cout << "================== Topology: dumbell ==================" << std::endl;

  NodeContainer router;
  NodeContainer leftleaf;
  NodeContainer rightleaf;
  router.Create (num_cca);
  leftleaf.Create (num_leaf);
  rightleaf.Create (num_leaf);

  // Presume all switch-switch links are of the same configuration
  PointToPointHelper p2p_bottleneck;
  p2p_bottleneck.SetDeviceAttribute ("DataRate", StringValue (bottleneck_bw));
  p2p_bottleneck.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_bottleneck.SetChannelAttribute ("Delay", StringValue (bottleneck_delay));
  PointToPointHelper p2p_leaf0;
  p2p_leaf0.SetDeviceAttribute ("DataRate", StringValue (leaf_bw0));
  p2p_leaf0.SetDeviceAttribute ("Mtu", UintegerValue(1500));  
  p2p_leaf0.SetChannelAttribute ("Delay", StringValue (leaf_delay0));
  PointToPointHelper p2p_leaf1;
  p2p_leaf1.SetDeviceAttribute ("DataRate", StringValue (leaf_bw1));
  p2p_leaf1.SetDeviceAttribute ("Mtu", UintegerValue(1500));    
  p2p_leaf1.SetChannelAttribute ("Delay", StringValue (leaf_delay1));  
  PointToPointHelper p2p_leaf2;
  p2p_leaf2.SetDeviceAttribute ("DataRate", StringValue (leaf_bw2));
  p2p_leaf2.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf2.SetChannelAttribute ("Delay", StringValue (leaf_delay2));  
  PointToPointHelper p2p_leaf3;
  p2p_leaf3.SetDeviceAttribute ("DataRate", StringValue (leaf_bw3));
  p2p_leaf3.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf3.SetChannelAttribute ("Delay", StringValue (leaf_delay3));  
  PointToPointHelper p2p_leaf4;
  p2p_leaf4.SetDeviceAttribute ("DataRate", StringValue (leaf_bw4));
  p2p_leaf4.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf4.SetChannelAttribute ("Delay", StringValue (leaf_delay4));  
  PointToPointHelper p2p_leaf5;
  p2p_leaf5.SetDeviceAttribute ("DataRate", StringValue (leaf_bw5));
  p2p_leaf5.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf5.SetChannelAttribute ("Delay", StringValue (leaf_delay5));  
  PointToPointHelper p2p_leaf6;
  p2p_leaf6.SetDeviceAttribute ("DataRate", StringValue (leaf_bw6));
  p2p_leaf6.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf6.SetChannelAttribute ("Delay", StringValue (leaf_delay6)); 
  PointToPointHelper p2p_leaf7;
  p2p_leaf7.SetDeviceAttribute ("DataRate", StringValue (leaf_bw7));
  p2p_leaf7.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf7.SetChannelAttribute ("Delay", StringValue (leaf_delay7)); 
  PointToPointHelper p2p_leaf8;
  p2p_leaf8.SetDeviceAttribute ("DataRate", StringValue (leaf_bw8));
  p2p_leaf8.SetDeviceAttribute ("Mtu", UintegerValue(1500));   
  p2p_leaf8.SetChannelAttribute ("Delay", StringValue (leaf_delay8));        

  // Default NS-3 DropTailQueue size for the NetDevice/NIC is 100p, make them configurable anyway (e.g., 1p where FQ has more predictable perf)
  p2p_bottleneck.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (switch_netdev_size));
  p2p_leaf0.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf1.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf2.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf3.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf4.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf5.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf6.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf7.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));
  p2p_leaf8.SetQueue ("ns3::DropTailQueue", "MaxSize", StringValue (server_netdev_size));                

  NetDeviceContainer leftleaf_devices;
  NetDeviceContainer rightleaf_devices;
  NetDeviceContainer router_devices_right;
  NetDeviceContainer router_devices_left;
  NetDeviceContainer leftrouter_devices;
  NetDeviceContainer rightrouter_devices;


  if (enable_debug) std::cout << "================== Linking num_cca-1 pairs of switch-switch links ==================" << std::endl;

  for (uint32_t i = 0; i < num_cca-1; i++) {
    NetDeviceContainer c;
    c = p2p_bottleneck.Install(router.Get(i), router.Get(i+1));
    router_devices_right.Add(c.Get(0));
    router_devices_left.Add(c.Get(1));
  }

  if (enable_debug) std::cout << "================== Linking server-switch ==================" << std::endl;

  for (uint32_t i = 0; i < num_leaf; ++i) {
    NetDeviceContainer cl;
    NetDeviceContainer cr;    
    if (i < num_cca0) {
      cl = p2p_leaf0.Install(router.Get (0),
                            leftleaf.Get (i));
      switch(num_cca) {
        case 1:
          cr = p2p_leaf0.Install(router.Get (0), rightleaf.Get (i));
          break;
        case 2:
          cr = p2p_leaf0.Install(router.Get (1), rightleaf.Get (i));
          break;
        case 3:
          cr = p2p_leaf0.Install(router.Get (2), rightleaf.Get (i));
          break;
        case 4:
          cr = p2p_leaf0.Install(router.Get (3), rightleaf.Get (i));
          break;
        case 5:
          cr = p2p_leaf0.Install(router.Get (4), rightleaf.Get (i));
          break;      
        case 6:
          cr = p2p_leaf0.Install(router.Get (5), rightleaf.Get (i));
          break;       
        case 7:
          cr = p2p_leaf0.Install(router.Get (6), rightleaf.Get (i));
          break;         
        case 8:
          cr = p2p_leaf0.Install(router.Get (7), rightleaf.Get (i));
          break;         
        case 9:
          cr = p2p_leaf0.Install(router.Get (8), rightleaf.Get (i));
          break;      
      }      
    } else if (i < (num_cca0+num_cca1)) {
      cl= p2p_leaf1.Install(router.Get (0),
                      leftleaf.Get (i));
      cr = p2p_leaf1.Install(router.Get (1),
                            rightleaf.Get (i));                        
    } else if (i < (num_cca0+num_cca1+num_cca2)) {
      cl = p2p_leaf2.Install(router.Get (1),
                      leftleaf.Get (i));  
      cr = p2p_leaf2.Install(router.Get (2),
                            rightleaf.Get (i));                            
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3)) {
      cl = p2p_leaf3.Install(router.Get (2),
                      leftleaf.Get (i));    
      cr = p2p_leaf3.Install(router.Get (3),
                            rightleaf.Get (i));                          
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4)) {
      cl = p2p_leaf4.Install(router.Get (3),
                      leftleaf.Get (i)); 
      cr = p2p_leaf4.Install(router.Get (4),
                            rightleaf.Get (i));                             
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5)) {
      cl = p2p_leaf5.Install(router.Get (4),
                      leftleaf.Get (i));
      cr = p2p_leaf5.Install(router.Get (5),
                            rightleaf.Get (i));                          
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6)) {
      cl = p2p_leaf6.Install(router.Get (5),
                      leftleaf.Get (i)); 
      cr = p2p_leaf6.Install(router.Get (6),
                            rightleaf.Get (i));                         
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7)) {
      cl = p2p_leaf7.Install(router.Get (6),
                      leftleaf.Get (i));  
      cr = p2p_leaf7.Install(router.Get (7),
                            rightleaf.Get (i));                        
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7+num_cca8)) {
      cl = p2p_leaf8.Install(router.Get (7),
                      leftleaf.Get (i)); 
      cr = p2p_leaf8.Install(router.Get (8),
                            rightleaf.Get (i));                         
    }
    leftrouter_devices.Add (cl.Get (0));
    leftleaf_devices.Add (cl.Get (1));
    rightrouter_devices.Add (cr.Get (0));
    rightleaf_devices.Add (cr.Get (1));    
  }

  if (enable_debug) std::cout << "================== InternetStackHelper ==================" << std::endl;

  InternetStackHelper stack;
  for (uint32_t i = 0; i < num_leaf; ++i) {
    stack.Install (leftleaf.Get(i));
  }
  for (uint32_t i = 0; i < num_leaf; ++i) {
    stack.Install (rightleaf.Get(i));
  }
  for (uint32_t i = 0; i < num_cca; ++i) {
    stack.Install (router.Get(i));
  }

  if (enable_debug) std::cout << "================== Install TCP transport ==================" << std::endl;
  // 2 MB (large enough) TCP buffers to prevent the applications from bottlenecking the exp
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (1 << 21));
  Config::SetDefault ("ns3::TcpSocket::SndBufSize", UintegerValue (1 << 21));
  // Reset the default MSS ~500
  // IP MTU = IP header (20B-60B) + TCP header (20B-60B) + TCP MSS
  // Ethernet frame = Ethernet header (14B) + IP MTU + FCS (4B)
  // The additional header overhead for this instance is 20+20+14=54B, hence app_packet_size <= 1500-54 = 1446
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (app_packet_size));
  Config::SetDefault ("ns3::TcpSocketBase::Sack", BooleanValue (sack));
  // Config::SetDefault ("ns3::TcpSocket::InitialCwnd", UintegerValue (10));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (delackcount));
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

  if (enable_debug) std::cout << "================== Configure TrafficControlLayer ==================" << std::endl;
  // We keep the tch default ns3::FqCoDelQueueDisc (for point-to-point) untouched for sources and sinks.
  // Such DRR fair queueing (https://www.nsnam.org/docs/models/html/fq-codel.html) is useful upon multiple apps on a single sender node.

  TrafficControlHelper tch_switch;
  QueueDiscContainer qdiscs;
  if (queuedisc_type.compare("FifoQueueDisc") == 0) {
    tch_switch.SetRootQueueDisc ("ns3::FifoQueueDisc", "MaxSize", StringValue (switch_total_bufsize));
    qdiscs = tch_switch.Install(router_devices_right);
    Ptr<QueueDisc> q = qdiscs.Get (0);
    oss << "Configured FifoQueueDisc\n";
  } else if (queuedisc_type.compare("CebinaeQueueDisc") == 0) {
    Config::SetDefault ("ns3::CebinaeQueueDisc::debug", BooleanValue (enable_debug));
    Config::SetDefault ("ns3::CebinaeQueueDisc::dT", TimeValue (dt));
    Config::SetDefault ("ns3::CebinaeQueueDisc::vdT", TimeValue (vdt));
    Config::SetDefault ("ns3::CebinaeQueueDisc::L", TimeValue (l));
    Config::SetDefault ("ns3::CebinaeQueueDisc::P", UintegerValue (p));
    Config::SetDefault ("ns3::CebinaeQueueDisc::tau", DoubleValue (tau));
    Config::SetDefault ("ns3::CebinaeQueueDisc::delta_port", DoubleValue (delta_port));
    Config::SetDefault ("ns3::CebinaeQueueDisc::delta_flow", DoubleValue (delta_flow));
    Config::SetDefault ("ns3::CebinaeQueueDisc::pool", BooleanValue (pool));
    Config::SetDefault ("ns3::CebinaeQueueDisc::DataRate", StringValue (bottleneck_bw));

    tch_switch.SetRootQueueDisc ("ns3::CebinaeQueueDisc", "MaxSize", StringValue (switch_total_bufsize));

    qdiscs = tch_switch.Install(router_devices_right);
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
    tch_switch.SetRootQueueDisc ("ns3::FqCoDelQueueDisc", "MaxSize", StringValue (switch_total_bufsize),
                                                          "Flows", UintegerValue (4294967295));
    qdiscs = tch_switch.Install(router_devices_right);    
    oss << "Configured FqCoDelQueueDisc\n";
  } else {
    oss << "Configured NULL QueueDisc (which is the default FqCoDelQueueDisc and buffer size)\n";
  }

  if (enable_debug) std::cout << "================== Configure Ipv4AddressHelper ==================" << std::endl;

  Ipv4AddressHelper ipv4_left;
  ipv4_left.SetBase ("1.1.1.0", "255.255.255.0");  
  Ipv4AddressHelper ipv4_right("100.1.1.0", "255.255.255.0");
  Ipv4AddressHelper ipv4_router("200.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer leftleaf_ifc;
  Ipv4InterfaceContainer leftrouter_ifc;
  Ipv4InterfaceContainer rightleaf_ifc;
  Ipv4InterfaceContainer rightrouter_ifc;
  Ipv4InterfaceContainer router_ifc;

  for (uint32_t i = 0; i < num_cca-1; ++i) {
    NetDeviceContainer ndc;
    ndc.Add (router_devices_right.Get (i));
    ndc.Add (router_devices_left.Get (i));
    Ipv4InterfaceContainer ifc = ipv4_router.Assign (ndc);
    router_ifc.Add (ifc.Get(0));
    router_ifc.Add (ifc.Get(1));
  }
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

  if (enable_debug) std::cout << "================== Generate application ==================" << std::endl;

  Ptr<MySource>* sources;
  sources = new Ptr<MySource>[num_leaf];
  for (uint32_t i = 0; i < num_leaf; ++i) {
    if (enable_debug) std::cout << "================== Generate application for leaf " << i << " ==================" << std::endl;
    uint16_t sinkPort = 8080;
    Address sinkAddress (InetSocketAddress (rightleaf_ifc.GetAddress(i), sinkPort));
    // PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort)); 
    // ApplicationContainer sinkApps = packetSinkHelper.Install (rightleaf.Get(i));
    Ptr<PacketSink> sink = CreateObject<PacketSink> ();
    sink->SetAttribute ("Protocol", StringValue ("ns3::TcpSocketFactory"));
    sink->SetAttribute ("Local", AddressValue (InetSocketAddress (Ipv4Address::GetAny (), sinkPort)));
    rightleaf.Get(i)->AddApplication(sink);
    sink->SetStartTime (Seconds (0.));
    sink->SetStopTime (Seconds (app_seconds_end));  

    sink->TraceConnectWithoutContext("RxWithAddresses", MakeCallback(&RxWithAddressesPacketSink));

    if (enable_debug) std::cout << "================== Setup socket ==================" << std::endl;
    Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (leftleaf.Get (i), TcpSocketFactory::GetTypeId ());
    // TODO change node index
    // Config::ConnectWithoutContext ("/NodeList/"+std::to_string(2+i)+"/$ns3::TcpL4Protocol/SocketList/0/RTT", MakeBoundCallback (&TraceRtt, i));

    if (enable_debug) std::cout << "================== Setup app ==================" << std::endl;
    Ptr<MySource> app = CreateObject<MySource> ();
    if (i < num_cca0) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw0), i, false);
    } else if (i < (num_cca0+num_cca1)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw1), i, false);       
    } else if (i < (num_cca0+num_cca1+num_cca2)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw2), i, false);    
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw3), i, false);      
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw4), i, false);     
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw5), i, false);       
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw6), i, false);     
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw7), i, false);       
    } else if (i < (num_cca0+num_cca1+num_cca2+num_cca3+num_cca4+num_cca5+num_cca6+num_cca7+num_cca8)) {
      app->Setup (ns3TcpSocket, sinkAddress, app_packet_size, DataRate (app_bw8), i, false);      
    }                                    
    leftleaf.Get (i)->AddApplication (app);
    app->SetStartTime (Seconds (app_seconds_start));
    app->SetStopTime (Seconds (app_seconds_end));
    sources[i] = app;
  }

  if (enable_debug) std::cout << "================== Tracing ==================" << std::endl;
  // No longer trace throughput (intercepting PointToPointNetDevice), only gpt

  packetsink_mysourceidtag2bytecount.resize(num_leaf, 0);
  avg_tpt_app.resize(num_leaf, 0);
  num_tracing_periods = sim_seconds/(tracing_period_us/pow(10, 6));
  oss << "num_tracing_periods: " << num_tracing_periods << "\n";

  Simulator::Schedule(MicroSeconds(0+tracing_period_us), &TraceThroughputJFI, 
                      "bottleneck_tpt_"+std::to_string(tracing_period_us)+".dat",
                      "app_tpt_"+std::to_string(tracing_period_us)+".dat",
                      "jfi_"+std::to_string(tracing_period_us)+".dat");

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  if (printprogress) {
    Simulator::Schedule (MilliSeconds(progress_interval_ms), &PrintProgress, MilliSeconds(progress_interval_ms));
  }

  if (enable_debug) std::cout << "================== Run ==================" << std::endl;

  Simulator::Stop (Seconds (sim_seconds));
  auto start = std::chrono::high_resolution_clock::now();
  Simulator::Run ();
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = stop - start;

  if (enable_debug) std::cout << "================== Export digest ==================" << std::endl;

  std::cout << elapsed_seconds.count() << "s" << std::endl;

  oss << "=== Ipv4 addresses ===\n";
  oss << "--- leftleaf_ifc ---\n";
  for (uint32_t i = 0; i < num_leaf; i++) {
    oss << i << " " << leftleaf_ifc.GetAddress(i) << "\n";
  }
  oss << "--- leftrouter_ifc ---\n";
  for (uint32_t i = 0; i < num_leaf; i++) {
    oss << i << " " << leftrouter_ifc.GetAddress(i) << "\n";
  }
  oss << "--- rightleaf_ifc ---\n";
  for (uint32_t i = 0; i < num_leaf; i++) {
    oss << i << " " << rightleaf_ifc.GetAddress(i) << "\n";
  }  
  oss << "--- rightrouter_ifc ---\n";
  for (uint32_t i = 0; i < num_leaf; i++) {
    oss << i << " " << rightrouter_ifc.GetAddress(i) << "\n";
  }
  oss << "--- router_ifc ---\n";
  for (uint32_t i = 0; i < 2*(num_cca-1); i++) {
    oss << i << " " << router_ifc.GetAddress(i) << "\n";
  }  

  oss << "=== avg_tpt_app[*] ===\n";
  double sum = 0.0;
  for (uint32_t i = 0; i < avg_tpt_app.size(); i++) {
    sum += avg_tpt_app[i];     
    oss << std::fixed << std::setprecision (3) << i << " " << avg_tpt_app[i] << "\n";
  }
  oss << std::fixed << std::setprecision (3) << "Avg. Goodput [bps]: " << sum << "\n";

  oss << "====== Number of packets sent ======\n";
  for (uint32_t sourceid = 0; sourceid < num_leaf; sourceid++) {
    oss << "MySource " << sourceid << ":" << sources[sourceid]->GetPacketsSent() << "\n";
  }
  
  if (queuedisc_type.compare("CebinaeQueueDisc") == 0) {
    oss << "====== CebinaeQueueDisc digest ======\n";
    for (uint32_t i = 0; i < num_cca-1; i++) {
      oss << "====== Switch " << i << " ======\n";
      Ptr<QueueDisc> q = qdiscs.Get(i);
      oss << DynamicCast<CebinaeQueueDisc>(q)->DumpDigest();    

      std::ofstream cebinae_ofs (result_dir + "/cebinae_debug" + std::to_string(i), std::ios::out | std::ios::app);    
      cebinae_ofs << DynamicCast<CebinaeQueueDisc>(q)->DumpDebugEvents();  
    }      
  }

  oss << "\n=== Completion time [s]: " << elapsed_seconds.count() << "===\n";
  std::ofstream summary_ofs (result_dir + "/digest", std::ios::out | std::ios::app);  
  summary_ofs << oss.str();

  if (enable_stdout) {
    std::cout << oss.str() << std::endl;
  }
  std::cout << "Result_dir: " << result_dir << std::endl;

  Simulator::Destroy ();

  return 0;
}

