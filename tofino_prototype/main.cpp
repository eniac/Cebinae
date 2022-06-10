/* Cebinae control plane prototype */



#include "libs/mgr.h"

#ifdef __cplusplus
extern "C" {
#endif
#include <tofino/pdfixed/pd_common.h>
#include <pipe_mgr/pipe_mgr_intf.h>
#include <pipe_mgr/pipe_mgr_mirror_intf.h>
#include <dvm/bf_drv_intf.h>

#include <tofino/pdfixed/pd_ms.h>

#include <time.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bfsys/bf_sal/bf_sys_assert.h>
#include <bfsys/bf_sal/bf_sys_sem.h>
#include <bfsys/bf_sal/bf_sys_mem.h>
    
#ifdef __cplusplus
}
#endif

#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include <set>
#include <map>
using namespace std;


// application level configuration
#define EGR_FLOWTABLE_SIZE 1024
#define DT_MS 1000
#define L_MS 152
#define DT_MINUS_L_MS DT_MS - L_MS // must estimate by profiling this app

// The two queues we are rotating between -- sync with p4 code
uint8_t QUEUE_A = 1;
uint8_t QUEUE_B = 2;
// the default queue -- mainly for debugging
uint8_t QUEUE_DEFAULT = 0;

// port rate and thresholds
uint64_t PORT_RATE_GBPS = 25;
double port_bottleneck_thresh = 0.1; // 90% utilization
double flow_bottleneck_thresh = 0.1;
double tax_rate = 0.05; // tax a flow by 10% of its bandwidth

// platform level configuration
#define NUM_PORTS 1
#define NUM_FS NUM_PORTS*2
#define BOTTLENECK_PORT 128
#define NUM_PIPES 2 // number of pipes on the device.
#define TEST_PIPE 1 // all the ports we care about are on port 1 (128 - 196)

// Builtins for using the tofino drivers
#define PKTGEN_APP_1 0x1
#define MIN_PKTGEN_SIZE 54
#define PKTGEN_SRC_PORT_PIPE0 68
#define PIPE_MGR_SUCCESS 0
#define ALL_PIPES 0xffff



/*=============================================
=            low level PD wrappers            =
=============================================*/
// low-level helpers to install table rules 
// poll registers, etc. uses code in pd_helpers.hpp, 
// which is copied from the tofino-compiler generated 
// pd.h and pd.c
#include "pd_helpers.hpp"

p4_pd_dev_target pd_dev_tgt_tables;
p4_pd_sess_hdl_t pd_sess_hdl;

// debugging functions
#include "debug.hpp"

void setup_dev_tgt() {
    pd_sess_hdl = 1;
    pd_dev_tgt_tables.device_id = 0;
    pd_dev_tgt_tables.dev_pipe_id = ALL_PIPES;
}

// // add a setEgress rule to the tiForward table
// p4_pd_entry_hdl_t tiForward_add_setEgress(uint16_t igr_port, uint16_t egrport) {
//     // build match and action structs
//     p4_pd_main_Ingress_t_igr_tiForward_match_spec_t matchSpec;
//     matchSpec.md_ingress_port = igr_port;
//     p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec_t acnSpec;
//     acnSpec.action_egr_port = egrport;
//     // add rule
//     p4_pd_entry_hdl_t entry_hdl;
//     p4_pd_status_t pd_status = 
//         p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress(
//             pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &acnSpec, &entry_hdl);
//     if (pd_status != 0) {
//         std::cout << "[tiForward_add_setEgress] pd_status error." << std::endl;
//     }
//     return entry_hdl;    
// }
// void tiForward_delete(p4_pd_entry_hdl_t entry_hdl) {
//     p4_pd_status_t pd_stat = p4_pd_main_Ingress_t_igr_tiForward_table_delete(pd_sess_hdl, pd_dev_tgt_tables.device_id, entry_hdl);
//     if (pd_stat != 0) {
//         std::cout << "[tiForward_delete] pd_status error." << std::endl;
//     }
//     return;
// }
// uint32_t uint_of_ipstr(const char * cp) {
//     struct in_addr sock_addr;
//     inet_aton(cp, &sock_addr);
//     return (uint32_t)sock_addr.s_addr;
// }

// add an entry to the top table based on flow key.
p4_pd_entry_hdl_t tiCalcF_add_aiSetFTop(uint32_t srcip, uint32_t dstip) {
    // build match struct
    p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t matchSpec;
    matchSpec.hdr_ip_src_addr = htonl(srcip);
    matchSpec.hdr_ip_dst_addr = htonl(dstip);
    // add rule
    p4_pd_entry_hdl_t entry_hdl;
    p4_pd_status_t pd_status = 
        p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop(
            pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &entry_hdl);
    if (pd_status != 0) {
        std::cout << "[tiCalcF_add_aiSetFTop] pd_status error." << std::endl;
    }
    return entry_hdl;    
}

// delete an entry into the top table based on flow key.
void tiCalcF_delete(uint32_t srcip, uint32_t dstip) {
    // build match struct
    p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t matchSpec;
    matchSpec.hdr_ip_src_addr = htonl(srcip); // htonl because driver auto-converts to h
    matchSpec.hdr_ip_dst_addr = htonl(dstip);
    // delete rule
    p4_pd_status_t pd_status = 
        p4_pd_main_Ingress_t_igr_tiCalcF_table_delete_by_match_spec(
            pd_sess_hdl, pd_dev_tgt_tables, &matchSpec);
    if (pd_status != 0) {
        std::cout << "[tiCalcF_delete_aiSetFTop] pd_status error -- maybe entry did not exist?" << std::endl;
    }
    return;
}

map<pair<uint16_t, uint32_t>, pair<p4_pd_entry_hdl_t, p4_pd_entry_hdl_t>> tiGetRates_entries;

// update the rates for f (top or bottom for a specific port). 
// install an entry if there is none, else update current entry
// update the head and tail rate tables at rates[f][current_headq] = (new_head, new_size);
void tiGetRates_update(uint16_t f, uint32_t current_headq, uint32_t r_head, uint32_t size_head) {

    // 1. set head table[f][current_headq]
    // 2. set tail table[f][current_headq]

    // build action struct for head table. 
    p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t acnSpecHead; 
    acnSpecHead.action_r_head = htons(r_head);
    acnSpecHead.action_r_head_x_dT = htons(size_head);

    // action struct for tail table.
    p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t acnSpecTail; 
    acnSpecTail.action_r_tail = htons(r_head);
    acnSpecTail.action_r_tail_x_dT = htons(size_head);


    // Update head table
    // entry does not exist.
    if (tiGetRates_entries.find({f, current_headq}) == tiGetRates_entries.end()) {
        // entry for current headq id doesn't exist. Create one in both tables.
        // HEAD
        // cout << "adding new tiGetRates_head entry for f="<<f<<endl;
        // build match spec.
        p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec matchSpecHead;
        matchSpecHead.f = htons(f);
        matchSpecHead.headq = htonl(current_headq);
        // add entry. 
        p4_pd_entry_hdl_t new_entry_hdl_head;
        p4_pd_status_t pd_status = 
            p4_pd_main_Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head(
                pd_sess_hdl, pd_dev_tgt_tables, &matchSpecHead, &acnSpecHead, &new_entry_hdl_head);
        if (pd_status != 0) {
            std::cout << "[tiGetRates_update] pd_status error while adding new head entry" << std::endl;
        }
        // TAIL
        // build match spec.
        p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec matchSpecTail;
        matchSpecTail.f = htons(f);
        matchSpecTail.tailq = htonl(current_headq);
        // add entry. 
        p4_pd_entry_hdl_t new_entry_hdl_tail;
        pd_status = 
            p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail(
                pd_sess_hdl, pd_dev_tgt_tables, &matchSpecTail, &acnSpecTail, &new_entry_hdl_tail);
        if (pd_status != 0) {
            std::cout << "[tiGetRates_update] pd_status error while adding new tail entry" << std::endl;
        }
        // update handler map
        tiGetRates_entries[{f, current_headq}] = {new_entry_hdl_head, new_entry_hdl_tail};        
    }
    // entry exists, so modify instead of add
    else {
        // cout << "updating current tiGetRates entry for f="<<f<<endl;
        auto current_entry_hdl_pair = tiGetRates_entries[{f, current_headq}];
        auto current_entry_hdl_head = current_entry_hdl_pair.first;
        p4_pd_status_t pd_status = 
            p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head(
                pd_sess_hdl, pd_dev_tgt_tables.device_id, current_entry_hdl_head, &acnSpecHead);
        if (pd_status != 0) {
            std::cout << "[tiGetRates_update] pd_status error while modifying head entry" << std::endl;
        }
        auto current_entry_hdl_tail = current_entry_hdl_pair.second;
        pd_status = 
            p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail(
                pd_sess_hdl, pd_dev_tgt_tables.device_id, current_entry_hdl_tail, &acnSpecTail);
        if (pd_status != 0) {
            std::cout << "[tiGetRates_update] pd_status error while modifying tail entry" << std::endl;
        }
    }
    return;
}

// read the current headq id
uint32_t ri_headq_read() {
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    uint32_t regvals[NUM_PIPES];
    int valct = 0;
    p4_pd_status_t pd_status = p4_pd_main_register_read_Ingress_t_igr_ri_headq(pd_sess_hdl, pd_dev_tgt_tables, 0, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[ri_headq_read] pd_status error." << endl;
    }
    return regvals[TEST_PIPE];        
}
uint32_t ri_tailq_read() {
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    uint32_t regvals[NUM_PIPES];
    int valct = 0;
    p4_pd_status_t pd_status = p4_pd_main_register_read_Ingress_t_igr_ri_tailq(pd_sess_hdl, pd_dev_tgt_tables, 0, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[ri_tailq_read] pd_status error." << endl;
    }
    return regvals[TEST_PIPE];        
}

// set current headq id
void ri_headq_write(uint32_t val) {
    uint32_t v = val;
    p4_pd_status_t pd_status = p4_pd_main_register_write_Ingress_t_igr_ri_headq(pd_sess_hdl, pd_dev_tgt_tables, 0, &v);
    if (pd_status != 0) {
        cout << "[ri_headq_write] pd_status error." << endl;
    }
    return;        
}
void ri_tailq_write(uint32_t val) {
    uint32_t v = val;
    p4_pd_status_t pd_status = p4_pd_main_register_write_Ingress_t_igr_ri_tailq(pd_sess_hdl, pd_dev_tgt_tables, 0, &v);
    if (pd_status != 0) {
        cout << "[ri_tailq_write] pd_status error." << endl;
    }
    return;        
}

// read a single index from the ports count table
uint32_t egr_port_cts_read(int idx) {
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    uint32_t regvals[NUM_PIPES]; // one for each pipe
    int valct = 0;
    p4_pd_status_t pd_status = p4_pd_main_register_read_Egress_t_egr_port_cts(pd_sess_hdl, pd_dev_tgt_tables, idx, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[egr_port_cts_read] pd_status error." << endl;
    }
    return regvals[TEST_PIPE];
}


typedef p4_pd_status_t (*range_reader_t)(p4_pd_sess_hdl_t, p4_pd_dev_target_t, int, int, int, uint32_t*, uint32_t*, int*); 

typedef p4_pd_status_t (*reset_t)(p4_pd_sess_hdl_t, p4_pd_dev_target_t);

// do a range read for the register accessed by reader function
void range_read_by_fcn(range_reader_t reader, uint32_t *read_vals, int count){
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    auto idx = 0;
    uint32_t num_actually_read; // per pipe, should equal count if success
    uint32_t regvals[count*NUM_PIPES]; // for all pipes 
    int value_count;
    p4_pd_status_t pd_status = reader(
        pd_sess_hdl, pd_dev_tgt_tables, idx, 
        count, flags, &num_actually_read, 
        regvals, &value_count);
    if (pd_status != 0) {
        cout << "[egr_flowtable_read] pd_status error." << endl;
    }
    // assumes only 1 pipe, otherwise the results would be striped
    for (int i = 0; i < count; i+=1) {
        // read just the values for the test pipe
        auto addr = (i * NUM_PIPES) + TEST_PIPE;
        read_vals[i] = regvals[addr];
    }    
    return;
}

void reset_by_fcn(reset_t resetter) {
    p4_pd_status_t pd_status = resetter(
        pd_sess_hdl, pd_dev_tgt_tables);
    if (pd_status != 0) {
        cout << "[reset_by_fcn] pd_status error." << endl;
    }    
}

/*=====  End of low level PD wrappers  ======*/


/*=================================================
=            Application-level helpers            =
=================================================*/

// Poll the egress flow table.
void egr_flowtable_read(uint32_t *src, uint32_t *dst, uint32_t *count) {
    // read from stage 1
    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_src1, src, EGR_FLOWTABLE_SIZE);
    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_dst1, dst, EGR_FLOWTABLE_SIZE);
    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_ct1, count, EGR_FLOWTABLE_SIZE);
    // read from stage 2

    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_src2, src+EGR_FLOWTABLE_SIZE, EGR_FLOWTABLE_SIZE);
    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_dst2, dst+EGR_FLOWTABLE_SIZE, EGR_FLOWTABLE_SIZE);
    range_read_by_fcn(p4_pd_main_register_range_read_Egress_t_egr_flow_ct2, count+EGR_FLOWTABLE_SIZE, EGR_FLOWTABLE_SIZE);

    // reset stage 1
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_src1);
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_dst1);
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_ct1);
    // reset stage 2
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_src2);
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_dst2);
    reset_by_fcn(p4_pd_main_register_reset_all_Egress_t_egr_flow_ct2);
}

// DEPRECIATED. Do this in python. 
// void add_fwd_rules() {
//     // 144 --> 155 and 155 --> 144
//     uint16_t port_144 = htons(144);
//     uint16_t port_155 = htons(155);
//     std::cout << "adding forwarding rules" << std::endl;
//     p4_pd_entry_hdl_t rule_hdl = tiForward_add_setEgress(port_155, port_144);
//     rule_hdl = tiForward_add_setEgress(port_144, port_155);
//     // std::cout << "done adding forwarding rule, sleeping 1s then deleting..." << std::endl;
//     // std::cout << "deleting forwarding rule.." << std::endl;
//     // tiForward_delete(rule_hdl);
//     std::cout << "done." << std::endl;
//     return;
// }

// find the heavy hitter on port p
int max_flow_idx(uint32_t p, uint32_t *counts) {
    uint32_t maxCt = 0;
    auto maxIdx = 0;
    for (auto i = 0; i < EGR_FLOWTABLE_SIZE; i += 1) {
        if (counts[i] > maxCt) {
            maxCt = counts[i];
            maxIdx = i;
        }
    }
    return maxIdx;
}
set<uint16_t> saturatedPorts;

void set_saturated(uint16_t port) {
    // if not already saturated, set as saturated
    if (saturatedPorts.find(port) == saturatedPorts.end()) {
        // build match spec
        p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec matchSpec;
        matchSpec.ig_tm_md_ucast_egress_port = htons(port); // htons because this comes from the controller.
        // add set saturated entry
        p4_pd_entry_hdl_t entry_hdl;
        p4_pd_status_t pd_status = 
            p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated(
                pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &entry_hdl);
        if (pd_status != 0) {
            std::cout << "[set_saturated] pd_status error." << std::endl;
        }
        saturatedPorts.insert(port);
    }
        return;
}

void unset_saturated(uint16_t port) {
    // if saturated, set as not saturated (delete rule)
    if (saturatedPorts.find(port) != saturatedPorts.end()) {
        // build match spec
        p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec matchSpec;
        matchSpec.ig_tm_md_ucast_egress_port = htons(port);
        // delete saturated entry
        p4_pd_entry_hdl_t entry_hdl;
        p4_pd_status_t pd_status = 
            p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec(
                pd_sess_hdl, 
                pd_dev_tgt_tables, 
                &matchSpec
                );
        if (pd_status != 0) {
            std::cout << "[unset_saturated] pd_status error." << std::endl;
        }
        saturatedPorts.erase(port);        
    }
    return;
    
}


// add the flow to the top group
void set_bottlenecked(uint32_t src, uint32_t dst) {
    // cout << "adding flow to top group: src="<<src<<" dst="<<dst<<endl;
    tiCalcF_add_aiSetFTop(src, dst);
    return;
}

// remove flow from the top group
void unset_bottlenecked(uint32_t src, uint32_t dst) {
    // cout << "removing flow from top group: src="<<src<<" dst="<<dst<<endl;
    tiCalcF_delete(src, dst);
    return;    
}




// set rates[port<<(is_top)][headq] = rate;
// rates are in B/us -- this has a rate granularity of 1MB/s
// note: there are two rate tables to set. That is handled in tiGetRates_update.
void set_top_rate(uint16_t port, uint32_t headq, uint32_t n_bytes) {
    uint16_t f = port << 1;
    double dT_us = DT_MS * 1000.0; // 1s = 1,000,000
    // the smallest r_head is 1B / us --> 1MB/s
    uint32_t r_head = int(double(n_bytes) / dT_us); // bytes/us
    uint32_t size_head = n_bytes;
    tiGetRates_update(f, headq, r_head, size_head);
    return;
}

void set_bottom_rate(uint16_t port, uint32_t headq, uint32_t n_bytes) {
    uint16_t f = port;
    double dT_us = DT_MS * 1000.0; // 1s = 1,000,000
    // the smallest r_head is 1B / us --> 1MB/s
    uint32_t r_head = int(double(n_bytes) / dT_us); // bytes/us
    uint32_t size_head = n_bytes;
    tiGetRates_update(f, headq, r_head, size_head);
    return;
}


// the current last size entry for each f. If one exists, use update instead of 
// add.
map<uint16_t,p4_pd_entry_hdl_t> tiReadLastSize_entries;


void set_last_size(uint16_t f, uint32_t n_bytes) {
    // build match and action structs
    p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t matchSpec;
    matchSpec.f = htons(f);
    p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t acnSpec;
    acnSpec.action_lastRate_x_dT = htons(n_bytes);

    // entry does not exist.
    if (tiReadLastSize_entries.find(f) == tiReadLastSize_entries.end()) {
        p4_pd_entry_hdl_t entry_hdl;
        p4_pd_status_t pd_status = 
            p4_pd_main_Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize(
                pd_sess_hdl, pd_dev_tgt_tables, &matchSpec, &acnSpec, &entry_hdl);
        if (pd_status != 0) {
            std::cout << "[set_last_top_size.add] pd_status error." << std::endl;
        }
        tiReadLastSize_entries[f] = entry_hdl;        
        return;
    } else {
        p4_pd_status_t pd_status = p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize(
            pd_sess_hdl, pd_dev_tgt_tables.device_id, tiReadLastSize_entries[f], &acnSpec);
        if (pd_status != 0) {
            std::cout << "[set_last_top_size.update] pd_status error." << std::endl;
        }
    }

}



struct FlowKey {
    uint32_t src;
    uint32_t dst;
};

bool operator<(const FlowKey &a, const FlowKey &b) {
    return (a.src + a.dst) < (b.src + b.dst);
}


/* **** pktgen configuration ****
https://github.com/eniac/OrbWeaver/blob/main/p4v16/main.cpp#L77
*/


/*==============================================
=            Rotate packet creation            =
==============================================*/


// The contents of the rotate packet actually don't 
// matter at all. We just use the packet_id field 
// in the autogenerated pktgen header, with a table 
// that converts packet_id to f
uint8_t rotate_pkt[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, // arbitrary dmac
    0x06, 0x07, 0x08, 0x09, 0x10, 0x11, // arbitrary smac
    0x12, 0x34, // ETHERTYPE_ROTATE
    0x00, 0x00,  // placeholder for f -- actually not needed
    // 16B header above, 48B pad payload below
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa
};

void init_pktgen(int pipe_id, int app_id, int pkt_offset, int timer_ns, int batch_size, uint8_t *pkt, int pkt_len) {
  int buffer_len = (pkt_len < MIN_PKTGEN_SIZE)? MIN_PKTGEN_SIZE:pkt_len;

  p4_pd_dev_target_t p4_pd_device;
  p4_pd_device.device_id = 0;
  p4_pd_device.dev_pipe_id = pipe_id;

  p4_pd_status_t pd_status;

  // Or full pkt but buffer_len-6, upkt+6
  pd_status = p4_pd_pktgen_write_pkt_buffer(pd_sess_hdl, p4_pd_device, pkt_offset, buffer_len, pkt);
 
  if (pd_status != 0) {
    printf("Pktgen: Writing Packet buffer failed!\n");
    return;
  }
  p4_pd_complete_operations(pd_sess_hdl);
  pd_status = p4_pd_pktgen_enable(pd_sess_hdl, 0, PKTGEN_SRC_PORT_PIPE0+128*pipe_id);  
  // port PKTGEN_SRC_PORT_PIPE0 (68) is port 196 on pipe 1
  // pd_status = p4_pd_pktgen_enable(pd_sess_hdl, 0, PKTGEN_SRC_PORT_PIPE0);
  if (pd_status != 0) {
    printf("Failed to enable pktgen status = %d!!\n", pd_status);
    return;
  }

  struct p4_pd_pktgen_app_cfg prob_app_cfg;
        
  prob_app_cfg.trigger_type = PD_PKTGEN_TRIGGER_TIMER_PERIODIC;
  
  prob_app_cfg.batch_count = 0;
  prob_app_cfg.packets_per_batch = NUM_FS-1;
  prob_app_cfg.pattern_value = 0;
  prob_app_cfg.pattern_mask = 0;
  prob_app_cfg.timer_nanosec = timer_ns;
  prob_app_cfg.ibg = 0;
  prob_app_cfg.ibg_jitter = 0;
  prob_app_cfg.ipg = 0;
  prob_app_cfg.ipg_jitter = 0;
  prob_app_cfg.source_port = PKTGEN_SRC_PORT_PIPE0;
  // BUG: DO NOT INCLUDE PIPE ID IN SOURCE PORT here (the +128... stuff is doign that)
  // prob_app_cfg.source_port = PKTGEN_SRC_PORT_PIPE0+128*pipe_id;
  prob_app_cfg.increment_source_port = 0;

  prob_app_cfg.pkt_buffer_offset = pkt_offset;
  prob_app_cfg.length = buffer_len;

  pd_status = p4_pd_pktgen_cfg_app(pd_sess_hdl,
            p4_pd_device,
            app_id,
            prob_app_cfg);

  if (pd_status != 0) {
    printf("pktgen app configuration failed\n");
    return;
  }

  pd_status = p4_pd_pktgen_app_enable(pd_sess_hdl, p4_pd_device, app_id);
  if (pd_status != 0) {
    printf("Pktgen : App enable Failed!\n");
    return;
  }
  printf("Launched pktgen for pipe %d\n", pipe_id);
//  sleep(1);
//  pd_status = p4_pd_pktgen_app_disable(pd_sess_hdl, p4_pd_device, app_id);
//  if (pd_status != 0) {
//    printf("Pktgen : App disable Failed!\n");
//    return;
//  }
}

/*=====  End of Rotate packet creation  ======*/

/*===============================================
=            Queue priority rotation            =
===============================================*/

// swap queue priorities
// https://github.com/eniac/OrbWeaver/blob/main/p4v16/main.cpp#L147

#define DEV_ID 0
void set_egress_q_prio(int pipeid){
  int port_num  = 64;
  int q_count = 8;
  uint8_t q_mapping[8];
  int base_use_limit_cell_num = 1;
  int hysteresis = 0;
  int i;
  for(i = 0; i < q_count; ++i)
    q_mapping[i] = i;
  for(i = 0; i < port_num; ++i){
    bf_tm_port_q_mapping_set(DEV_ID, 128*pipeid+i, q_count, q_mapping);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 0, BF_TM_SCH_PRIO_7);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 1, BF_TM_SCH_PRIO_6);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 2, BF_TM_SCH_PRIO_5);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 3, BF_TM_SCH_PRIO_4);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 4, BF_TM_SCH_PRIO_3);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 5, BF_TM_SCH_PRIO_2);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 6, BF_TM_SCH_PRIO_1);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*pipeid+i, 7, BF_TM_SCH_PRIO_0);  // IDLE
    // Disable burst absorption factor for static limit of IDLE queue size (tail drop upon violation)
    bf_tm_q_app_pool_usage_set(DEV_ID, 128*pipeid+i, 7, BF_TM_EG_APP_POOL_3, base_use_limit_cell_num, BF_TM_Q_BAF_DISABLE, hysteresis);
  }
}

// initial queue configuration

uint32_t top_queue = QUEUE_A;
void configure_queues() {
    /* want: queues for port BOTTLENECK_PORT with queue ids 111 and 222 */
    int q_count = 3;
    uint8_t q_mapping[] = {QUEUE_DEFAULT, QUEUE_A, QUEUE_B};
    int base_use_limit_cell_num = 1;
    int hysteresis = 0;
    // carve BOTTLENECK_PORT into three queues
    bf_tm_port_q_mapping_set(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, q_count, q_mapping);

    // Default queue is highest priority, 
    // QUEUE_A is highest priority rotate queue at first, QUEUE_B is lower
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_DEFAULT, BF_TM_SCH_PRIO_7);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_A, BF_TM_SCH_PRIO_1);
    p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_B, BF_TM_SCH_PRIO_0);
}

uint32_t high_prio_queue = QUEUE_A;
void reconfigure_queues() {
    if (high_prio_queue == QUEUE_A) {
        // cout << "high_prio_queue from QUEUE_A --> QUEUE_B" << endl;
        p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_B, BF_TM_SCH_PRIO_1);
        p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_A, BF_TM_SCH_PRIO_0);
        high_prio_queue = QUEUE_B;    
    } else {
        // cout << "high_prio_queue from QUEUE_B --> QUEUE_A" << endl;
        p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_A, BF_TM_SCH_PRIO_1);
        p4_pd_tm_set_q_sched_priority(DEV_ID, 128*TEST_PIPE+BOTTLENECK_PORT, QUEUE_B, BF_TM_SCH_PRIO_0);
        high_prio_queue = QUEUE_A;    
    }

}


/*=====  End of Queue priority rotation  ======*/


// Poll the debug register to see how many packets got sent to 
// each queue (head, tail, and drop)
uint32_t to_head = 0;
uint32_t to_tail = 0;
uint32_t to_drop = 0;

void pollQueueCounter() {
    int flags = REGISTER_READ_HW_SYNC; // sync with hw
    uint32_t regvals[NUM_PIPES];
    int valct = 0;
    p4_pd_status_t pd_status = p4_pd_main_register_read_Ingress_t_igr_queueCounter(pd_sess_hdl, pd_dev_tgt_tables, 0, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[pollQueueCounter] pd_status error." << endl;
    }
    to_head = regvals[TEST_PIPE];
    valct = 0;
    pd_status = p4_pd_main_register_read_Ingress_t_igr_queueCounter(pd_sess_hdl, pd_dev_tgt_tables, 1, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[pollQueueCounter] pd_status error." << endl;
    }
    to_tail = regvals[TEST_PIPE];

    valct = 0;
    pd_status = p4_pd_main_register_read_Ingress_t_igr_queueCounter(pd_sess_hdl, pd_dev_tgt_tables, 2, flags, regvals, &valct);
    if (pd_status != 0) {
        cout << "[pollQueueCounter] pd_status error." << endl;
    }
    to_drop = regvals[TEST_PIPE];
    return;
}



/*=====  End of Application-level helpers  ======*/



void cebinae_loop() {
    // sleep for 1 second to let the python script start and install rules, etc.
    cout << "cebinae main control loop starting in 2s..." << endl;
    configure_queues();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // we're just looking at 1 port, the bottleneck port.
    std::array<uint32_t, 1> ports = {BOTTLENECK_PORT};

    // Init packetgen
    init_pktgen(1, PKTGEN_APP_1, 0, DT_MS * 1000000, 0, rotate_pkt, 64);

    // how many bytes can a single port send in a single dT interval?  
    uint32_t port_bytes_per_dt = (uint32_t)(double(PORT_RATE_GBPS * 1000000000.0 / 8.0) * double(DT_MS / 1000.0));

    auto last_poll_time = std::chrono::high_resolution_clock::now();

    // port bytes table
    uint32_t port_bytes[1] = {0};
    uint32_t last_port_bytes[NUM_PORTS] = {0};

    // previous flow table
    // uint32_t last_egr_port[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t last_src[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t last_dst[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t last_count[EGR_FLOWTABLE_SIZE*2] = {0}; 

    // current flow table
    // uint32_t egr_port[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t src[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t dst[EGR_FLOWTABLE_SIZE*2] = {0}; 
    uint32_t count[EGR_FLOWTABLE_SIZE*2] = {0}; 

    // flow change counters, for flows in current
    uint32_t flow_bytes[EGR_FLOWTABLE_SIZE*2] = {0}; 

    // local copy of bottleneck / "top" flows set
    set <FlowKey> topSet;

    // to prevent thrashing, force a port to stay in 
    // bottleneck state for at least so many intervals.
    uint32_t min_bottleneck_interval_ct = 5;
    uint32_t bottleneck_start_interval = 0;
    bool was_bottlenecked = false;

    // f : size
    map<uint16_t, uint32_t> lastHeadSize;
    for (auto p : ports) {
        uint16_t p_top = p<<1;
        uint16_t p_bot = p;
        lastHeadSize[p_top] = 0;
        lastHeadSize[p_bot] = 0;
    }

    uint32_t last_headq = 0;
    int intervalCt = 0;
    int continueCt = 0;
    uint32_t last_heavy_hitter_idx = 0;
    while(true) {
        uint32_t headq = ri_headq_read();
        if (headq == last_headq) {
            // cout << "        continue # " << continueCt;
            // cout << " headq/last_headq: " << headq << endl;
            continueCt += 1;
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // print_debug(intervalCt, last_headq, headq);
            continue;
        }
        // print_debug_registers();
        last_headq = headq;
        // sleep for DT - L ms
        std::this_thread::sleep_for(std::chrono::milliseconds(DT_MINUS_L_MS));

        auto last_high_prio_queue = high_prio_queue;
        reconfigure_queues();
        auto cur_high_prio_queue = high_prio_queue;

        // get current time and time since last poll.
        auto poll_time = std::chrono::high_resolution_clock::now();
        auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(poll_time - last_poll_time).count();
        auto elapsed_s = double(elapsed_us) / 1000000.0;
        last_poll_time = poll_time;

        // poll port table (just the rate of BOTTLENECK_PORT for now)
        auto p_idx = 0;
        port_bytes[p_idx] = egr_port_cts_read(BOTTLENECK_PORT);
        auto byte_count = port_bytes[p_idx] - last_port_bytes[p_idx];
        last_port_bytes[p_idx] = port_bytes[p_idx];

        // poll flow table 
        egr_flowtable_read(src, dst, count);
        // compute change since last poll and copy flowtable to last_flowtable

        // logic for always reset data structure -- just copy everything 
        // because it was cleared at the end of the last interval. 
        for (auto i = 0; i < EGR_FLOWTABLE_SIZE*2; i+=1) {
            last_src[i] = src[i];
            last_dst[i] = dst[i];
            flow_bytes[i] = uint32_t((uint64_t(count[i])+uint64_t(last_count[i]))/uint64_t(2)); // smoothing: average over last two intervals
            if (flow_bytes[i] > 4000000000) {
                cout << "last_count: " << last_count[i] << endl;
                cout << "count: " << count[i] << endl;
                cout << "flow_bytes: " << flow_bytes[i] << endl;
            }
            last_count[i] = count[i];
        }

        // start top flows and rate calculation
        for (auto p : ports) {
            // print_debug_start(intervalCt, 
            //     last_headq, headq,
            //      last_high_prio_queue, cur_high_prio_queue, 
            //      byte_count, elapsed_s, 
            //      port_bytes_per_dt);
            if (double(byte_count) / double(port_bytes_per_dt) < (1.0 - port_bottleneck_thresh)) {
                if (was_bottlenecked) {
                    auto intervals_since_bottleneck = intervalCt - bottleneck_start_interval;
                    if (intervals_since_bottleneck > min_bottleneck_interval_ct) {
                        unset_saturated(p);
                        cout << "port " << p << " is NO LONGER saturated" << endl;    
                        was_bottlenecked = false;
                        bottleneck_start_interval = 0;
                        continue;        
                    }
                }
                // port wasn't bottlenecked -- keep un bottlenecked 
                else {
                    // unset_saturated(p);
                    // cout << "port " << p << " remains unsaturated" << endl;    
                    continue;        
                }

            } else {
                if (!was_bottlenecked) {
                    cout << "port " << p << " is SATURATED" << endl;            
                    set_saturated(p);                    
                }
                was_bottlenecked = true;
                bottleneck_start_interval = intervalCt;

            }
            // if the port is saturated, go on...
            // find the heavy hitter.
            auto max_idx = max_flow_idx(p, flow_bytes);
            // if a heavy hitter was found...
            bool print_update = false;
            if (flow_bytes[max_idx] != 0) {
                if (max_idx != last_heavy_hitter_idx) {
                    cout << "--- NEW HEAVY HITTER --- " << endl;
                    print_flow(src[max_idx], dst[max_idx], flow_bytes[max_idx], elapsed_s);
                    print_update = true;
                }
                last_heavy_hitter_idx = max_idx;
                auto max_flow_bytes = flow_bytes[max_idx];
                double bottleneck_bytes = 0;
                // find all the other flows within delta of the heavy hitter.
                for (auto f_idx = 0; f_idx < EGR_FLOWTABLE_SIZE*2; f_idx += 1) {
                    if (double(flow_bytes[f_idx])  >= (double(max_flow_bytes) * (1.0 - flow_bottleneck_thresh))) {
                        // put each flow in the top group
                        // (if not already there)
                        FlowKey key; 
                        key.src = src[f_idx];
                        key.dst = dst[f_idx];
                        if (topSet.find(key) == topSet.end()) {
                            cout << "adding flow to topset:" << endl;
                            print_flow(src[f_idx], dst[f_idx], flow_bytes[f_idx], elapsed_s);

                            topSet.insert(key);
                            set_bottlenecked(src[f_idx], dst[f_idx]);
                        }
                        // increment the rate of the top group.
                        bottleneck_bytes += flow_bytes[f_idx];
                    } else {
                        // if the flow is not a bottleneck, 
                        // but was in the top group, remove it.
                        FlowKey key; 
                        key.src = src[f_idx];
                        key.dst = dst[f_idx];
                        if (topSet.find(key) != topSet.end()) {
                            cout << "erasing flow from topset:" << endl;
                            print_flow(src[f_idx], dst[f_idx], flow_bytes[f_idx], elapsed_s);
                            topSet.erase(topSet.find(key));
                            unset_bottlenecked(src[f_idx], dst[f_idx]);
                        }
                    }
                }
                // set top and bottom rates based on bottleneck bytes
                bottleneck_bytes = uint32_t(double(bottleneck_bytes) * (1.0 - tax_rate));
                uint32_t top_bytes = bottleneck_bytes;
                uint32_t bottom_bytes = port_bytes_per_dt - bottleneck_bytes;

                set_top_rate(p, headq, top_bytes);
                set_bottom_rate(p, headq, bottom_bytes);
                if (top_bytes < lastHeadSize[p<<1]) {
                    cout << "top bytes DECREASED: " << lastHeadSize[p<<1] << " --> " << top_bytes << endl;
                } else {
                    cout << "top bytes INCREASED: " << lastHeadSize[p<<1] << " --> " << top_bytes << endl;

                }
                if (print_update)
                    print_debug_rates(top_bytes, bottom_bytes, lastHeadSize[p<<1], lastHeadSize[p]);

                // set the last head rate in the shadow table
                set_last_size(p<<1, lastHeadSize[p<<1]);
                set_last_size(p, lastHeadSize[p]);
                lastHeadSize[p<<1] = top_bytes;
                lastHeadSize[p] = bottom_bytes;


                // pollQueueCounter();
                // print_debug_queuects(to_head, to_tail, to_drop);

            } 
            else {
                // this branch should not be reached once program is complete -- 
                // when there's no activity, 
                // the port below capacity check will cause a continue.
                cout << "no flow activity during interval" << intervalCt << endl;
            }
            p_idx += 1;

        }
        intervalCt += 1;
    }
}
void start_cebinae_ctl() {
  setup_dev_tgt();
  cebinae_loop();
  return;    
}


int main(int argc, char **argv) {
  // start bf-switchd in the background
  start_switchd(argc, argv);
  
  start_cebinae_ctl();

  // when our program is done, join switchd
  return join_switchd();
}