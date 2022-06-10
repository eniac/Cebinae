// Themis ingress
#define DATA_PKT 1
#define ROTATE_PKT 2
#define num_ports 32
#define num_byte_counters 64
#define dT 0x1000000
#define dT_bitmask 0xff000000
#define log_dT 24
#define vdT 1

#include <core.p4>
#include <tna.p4>

// the two queue ids that we rotate between
// head and tail rotate between queue_a and queue_b
const bit<32> QUEUE_A = 1;
const bit<32> QUEUE_B = 2;



struct si_update_bytes_layout {
    bit<32> lo;
    bit<32> hi;
}


control Cebinae_igr(
        inout header_t hdr, 
        inout metadata_t md,
        inout ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md,
        in ingress_intrinsic_metadata_t ig_intr_md,        
        inout ingress_intrinsic_metadata_for_tm_t ig_tm_md)
    {
    // toggle cebinae on / off
    bit<8> useCebinae;
    action aiToggleCebinae(bit<8> isOn) {
        useCebinae = isOn;
    }
    table tiToggleCebinae {
        actions = {aiToggleCebinae;}
        // const default_action = aiToggleCebinae(0);
    }
    #include "ingress_objects.p4"
    apply {
        // rotate packets.
        if (hdr.ethernet.ether_type == ETHERTYPE_ROTATE) {
            // ai_copy_rotate_f();     // f = hdr.rotate.f;
            tiRotateF.apply(); // f = tiRotateF[hdr.pktgen.packet_id];
            tiRotateRoundTime.apply();  // if (f == BOTTLENECK_PORT): base_round_time[0] += dT  
            tiRotateHeadq.apply();      // if (f == BOTTLENECK_PORT): headq[0] = !headq[0] 
            tiRotateTailq.apply();      // if (f == BOTTLENECK_PORT): tailq[0] = !tailq[0]
            tiReadLastSize.apply();     // pkt_len = lastSizeTable[f]; // (last_rate * dT)
            ai_rotate_bytes();          // bytes[f] = bytes[f] |-| last_rate * dT;
            aiDebugLastSize();
            tiDrop_rotate.apply();
            // aiDrop_rotate();
        }
        // normal packets. 
        else {
            tiToggleCebinae.apply(); // useCebinae = 1 or 0 (for demo)
            // pkt_len = copy(hdr.ip.total_len);
            aiSetPktLen();
            // ts = copy(ingress_mac_tstamp);
            aiSetTs();
            // egr_port = tiForward[(dst_ip)];
            tiForward.apply();
            // f = egr_port << topTable[(src, dst)] 
            tiCalcF.apply();
            // saturated = saturatedTable[egr_port]
            tiCalcSaturated.apply();

            // all the below statements are precomputes for branch: {if (saturated == 1)}
            // observation: we can precompute everything up to count_bytes...
                // relative_round = ts - base_round_time;
                // (this is an optimization for when vdT = 1)
                aiGetRelativeRound();
                // headq = headq[0];
                aiGetHeadq();
                // tailq = tailq[0];
                aiGetTailq();
                // if (headq == QUEUE_A) {
                //     rate_head = rhead[f];
                //     rate_tail = rtail[f];
                // } else {
                //     rate_tail = rhead[f];
                //     rate_head = rtail[f];
                // }
                // rate_head, rate_x_dt_head = rateTable[f][headq]
                tiGetRates_head.apply();
                // rate_tail, rate_x_dt_tail = rateTable[f][tailq]
                tiGetRates_tail.apply();

                // precompute for {dT_minus_relative_round != 0}: 
                // relative_round_m_dt = relative_round - dT;
                aiCalc_relative_round_m_dt();

                // calculate aggregate size
                // want to test: relative_round < dT === 
                //               relative_round >= dT ===
                //               dT |-| relative_round == 0
                // dT_minus_relative_round = dT |-| relative_round;
                aiPrecompute_relative_round_test();
                if (dT_minus_relative_round == 0) { // relative_round < dT
                    // *** multi-stage approximate calculation *** 
                    // aggregate_size = rate_head * relative_round;
                    tiCalc_log_rate_head.apply();
                    tiCalc_log_relative_round.apply();
                    aiCalc_log_aggregate_size();
                    // tiExp_aggregate_size is the instruction that can't be precomputed.
                    tiExp_aggregate_size.apply(); 

                } else {
                    // *** multi-stage approximate calculation *** 
                    // aggregate_size = rate_head * dT + ((relative_round - dT) * rate_tail);
                    // note: several subexpressions are precomputed:
                    // rate_head * dT, relative_round - dT
                    tiCalc_log_relative_round_m_dt.apply();
                    tiCalc_log_rate_tail.apply();
                    aiCalc_log_relative_round_m_dt_x_rate_tail();
                    tiExp_relative_round_m_dt_x_rate_tail.apply();
                    aiCalc_aggregate_size_else();
                }
            // if the port is saturated and cebinae is turned on
            if (saturated == 1 && useCebinae == 1) {
                // bytes[f] = max(bytes[f], aggregate_size) + pkt_len;
                // note: pkt_len can only be used when bytes[f] is the output of max. 
                //       otherwise, a constant is used in its place.
                aiCountBytes();
                aiDebugWriteBytes();
                // past_head = bytes |-| rate_head_x_dT;
                aiCalc_past_head();
                // past_tail = past_head - rate_tail_x_dT;
                aiCalc_past_tail();
                // queue = queueTable[(past_head, past_tail)];
                tiSetQueue.apply();
            }
        }
    }
}

