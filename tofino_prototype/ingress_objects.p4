    bit<32> aggregate_size;
    bit<16> f;
    bit<32> pkt_len; // copy of packet length, set before bytes table.

    // debug. count packets in top and bottom groups.

    Register<bit<32>, bit<32>>(1024) fCount;
    RegisterAction<bit<32>, bit<32>, bit<32>>(fCount) raFCount = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = mem + 1;
        }
    };
    action aFtopCt() {
        raFCount.execute((bit<32>)0);
    }
    action aFbotCt() {
        raFCount.execute((bit<32>)1);
    }


    CRCPolynomial<bit<32>>(1, false, false, false, 0, 0) identity_poly;
    // copy the rotate header with hash units to reduce phv pressure 
    // on the bytes array's stateful alu.
    // Hash<bit<16>>(HashAlgorithm_t.CUSTOM, identity_poly) rotate_copy_f;
    // Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) rotate_copy_last_rate;
    // action ai_copy_rotate_f() {
    //     f = rotate_copy_f.get({hdr.rotate.f});
    // }

    action aiRotateF(bit<16> fval) {
        f = fval;
    }

    table tiRotateF {
        key = {hdr.pktgen.packet_id : exact;}
        actions = {aiRotateF;}
    }


    // 
    action aiReadLastSize(bit<32> lastRate_x_dT) {
        aggregate_size = lastRate_x_dT;
    }

    table tiReadLastSize {
        key = {f : exact;}
        actions = {aiReadLastSize;}
        const default_action = aiReadLastSize(0);
    }

    bit<32> ts;

    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher0;
    action aiSetPktLen() {
        pkt_len = identity_hasher0.get({hdr.ip.total_len});
    }
    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher2;
    action aiSetTs() {
        ts = identity_hasher2.get({ig_intr_md.ingress_mac_tstamp[42:10]});
    }

    action aiSetEgress(bit<9> egr_port) {
        ig_tm_md.ucast_egress_port = egr_port;
    }

    action aiNoop(){ }
    table tiForward {
        key = {
            md.ingress_port : exact;
            hdr.ethernet.dst_addr : exact;
        }
        actions = {
            aiSetEgress;
            aiNoop();
        }
        const default_action = aiNoop();
    }

    action aiSetFTop() {
        f = (bit<16>)ig_tm_md.ucast_egress_port << 1;
        aFtopCt();
    }
    action aiSetFBottom() {
        f = (bit<16>)ig_tm_md.ucast_egress_port;
        aFbotCt();
    }
    table tiCalcF {        
        key = {
            hdr.ip.src_addr : exact;
            hdr.ip.dst_addr : exact;
        }
        actions = {
            aiSetFTop; aiSetFBottom;
        }
        const default_action = aiSetFBottom();
    }

    bit<1> saturated;
    action aiSaturated() {
        saturated = 1;
    }
    action aiNotSaturated() {
        saturated = 0;
    }
    table tiCalcSaturated {
        key = {
            ig_tm_md.ucast_egress_port : exact;
        }
        actions = {
            aiSaturated;
            aiNotSaturated;
        }
        const default_action = aiNotSaturated();
    }


    // relative_round = ts - base_round[0];
    Register<bit<32>, bit<32>>(1, 0) ri_base_round_time;
    bit<32> base_round_time;
    bit<32> relative_round;
    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_base_round_time) siGetBaseRoundTime = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            retCell= ts - memCell;
        }
    };
    // action aiGetBaseRoundTime() {
    //     base_round_time=siGetBaseRoundTime.execute((bit<32>)0);

    // }
    action aiGetRelativeRound() {
        relative_round=siGetBaseRoundTime.execute((bit<32>)0);

        // =ts - base_round_time;
    }

    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_base_round_time) siRotateRoundTime = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            memCell = memCell + dT;
        }
    };
    action aiRotateRoundTime() {
        siRotateRoundTime.execute((bit<32>)0);
    }
    table tiRotateRoundTime {
        key = {
            f : exact;
        }
        actions = {aiRotateRoundTime;}
        const entries = {
            BOTTLENECK_PORT : aiRotateRoundTime();
        }
    }

    // get head queue
    Register<bit<32>, bit<32>>(1, 0) ri_headq;    
    bit<32> headq;
    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_headq) riGetHeadq = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            retCell=memCell;
        }
    };
    action aiGetHeadq() {
        headq=riGetHeadq.execute((bit<32>)0);
    }

    // get tail queue
    Register<bit<32>, bit<32>>(1, 0) ri_tailq;    
    bit<32> tailq;
    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_tailq) riGetTailq = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            retCell=memCell;
        }
    };
    action aiGetTailq() {
        tailq=riGetTailq.execute((bit<32>)0);
    }

    // rotate head and tail queue
    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_headq) riRotateHeadq = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            if (memCell == QUEUE_A) { // mem == 2 --> mem == 1
                memCell = QUEUE_B;
            } else {
                memCell = QUEUE_A; // mem != 2 --> mem == 2
            }
        }
    };
    action aiRotateHeadq() {
        headq=riRotateHeadq.execute((bit<32>)0);
    }
    table tiRotateHeadq {
        key = {
            f : exact;
        }
        actions = {aiRotateHeadq;}
        const entries = {
            BOTTLENECK_PORT : aiRotateHeadq();
        }
    }


    RegisterAction<bit<32>,bit<32>,bit<32>>(ri_tailq) riRotateTailq = {
        void apply(inout bit<32> memCell, out bit<32> retCell) {
            if (memCell == QUEUE_B) {
                memCell = QUEUE_A;
            } else {
                memCell = QUEUE_B;
            }
        }
    };
    action aiRotateTailq() {
        tailq=riRotateTailq.execute((bit<32>)0);
    }
    table tiRotateTailq {
        key = {
            f : exact;
        }
        actions = {aiRotateTailq;}
        const entries = {
            BOTTLENECK_PORT : aiRotateTailq();
        }
    }


    // get head and tail rates and queue sizes.
    bit<32> rate_head;
    bit<32> rate_tail;
    bit<32> rate_head_x_dT;
    bit<32> rate_tail_x_dT;

    action aiGetRates_head(
        bit<32> r_head, 
        bit<32> r_head_x_dT
        ){
      rate_head = r_head;
      rate_head_x_dT = r_head_x_dT;
    }
    // head_rate = rates[f][headq]
    table tiGetRates_head {
        key = { 
            f : exact; 
            headq : exact;
        }
        actions = {
            aiGetRates_head;
        }
        const default_action = aiGetRates_head(1, 1);
    }

    action aiGetRates_tail(
        bit<32> r_tail, 
        bit<32> r_tail_x_dT
        ){
      rate_tail = r_tail;
      rate_tail_x_dT = r_tail_x_dT;
    }
    // tail_rate = rates[f][tailq]
    table tiGetRates_tail {
        key = { 
            f : exact; 
            tailq : exact;
        }
        actions = {
            aiGetRates_tail;
        }
        const default_action = aiGetRates_tail(1, 1);
    }

    // Calculate aggregate size.
    /* 
    if relative_round < dt:
        aggregate_size = 
            rate_head * relative_round;
    else:
        aggregate_size = 
            (rate_head * dT)
            + ((relative_round - dT) * rate_tail);
    */
    // precompute for if test
    bit<32> dT_minus_relative_round;
    action aiPrecompute_relative_round_test() {
        dT_minus_relative_round = dT |-| relative_round;
    }

    /*** if branch ***/
    // estimate log based on highest order bit. 
    bit<8> log_rate_head;
    // log_rate_head = log2(rate_head);
    // generated by themis_printer.py
    #include "p4math/tiCalc_log_rate_head.p4" 

    bit<8> log_relative_round;
    // log_relative_round = log2(log_relative_round);
    // generated by themis_printer.py
    #include "p4math/tiCalc_log_relative_round.p4" 

    bit<8> log_aggregate_size;
    // log_aggregate_size = log_rate_head + log_relative_round;
    action aiCalc_log_aggregate_size() {
        log_aggregate_size = log_rate_head + log_relative_round;
    }
    // aggregate_size = 2^(log_aggregate_size);
    #include "p4math/tiExp_aggregate_size.p4"

    /*** else branch ***/

    // (relative_round - dT)
    bit<32> relative_round_m_dt;
    action aiCalc_relative_round_m_dt() {
        relative_round_m_dt = relative_round - dT;
    }
    // (relative_round - dT) * rate_head;
    bit<8> log_relative_round_m_dt;
    #include "p4math/tiCalc_log_relative_round_m_dt.p4"
    bit<8> log_rate_tail;
    #include "p4math/tiCalc_log_rate_tail.p4"

    bit<8> log_relative_round_m_dt_x_rate_tail;
    action aiCalc_log_relative_round_m_dt_x_rate_tail() {
        log_relative_round_m_dt_x_rate_tail = log_relative_round_m_dt + log_rate_tail;
    }

    /* 
        possible 1 stage optimization: combine
            log_c = log_a + log_b;
        and
            c = 2^log_c;
    */

    bit<32> relative_round_m_dt_x_rate_tail;
    #include "p4math/tiExp_relative_round_m_dt_x_rate_tail.p4"

    // Put everything together!
    action aiCalc_aggregate_size_else() {
        aggregate_size = rate_head_x_dT + relative_round_m_dt_x_rate_tail;
    }

    // calculate and update bytes
    // bytes = max(ri_bytes[f], aggregate_size) + pkt.size
    bit<32> bytes;
    Register<si_update_bytes_layout, bit<16>>(num_byte_counters) ri_bytes;
    // 4 highest-order bits as an approximation
    // MathUnit<bit<32>>(false, 2s0, 6s0, { 8w15, 8w14, 8w13, 8w12, 8w11, 8w10, 8w9, 8w8, 8w7, 8w6, 8w5, 8w4, 8w3, 8w2, 8w1, 8w0 }) mi_approx;

    const bit<32> mean_pkt_size = 512;
    RegisterAction<si_update_bytes_layout, bit<16>, bit<32>>(ri_bytes) si_update_bytes = {
        void apply(inout si_update_bytes_layout value, out bit<32> rv) {
            rv = 32w0;
            si_update_bytes_layout in_value;
            in_value = value;
            if (aggregate_size < in_value.lo) {
                value.lo = in_value.lo + pkt_len;
            }
            if (!(aggregate_size < in_value.lo)) {
                value.lo = aggregate_size + mean_pkt_size;
            }
            rv = value.lo;
        }
    };
    action aiCountBytes() {
        bytes=si_update_bytes.execute(f);
    }

    RegisterAction<si_update_bytes_layout, bit<16>, bit<32>>(ri_bytes) si_rotate_bytes = {
        void apply(inout si_update_bytes_layout value, out bit<32> rv) {
            si_update_bytes_layout in_value;
            in_value = value;
            value.lo = in_value.lo |-| aggregate_size; //NOTE: aggregate_size stores last rate in rotate packets.
            rv = value.lo; // Technically don't need this, but makes compilation easier.
        }
    };
    action ai_rotate_bytes() {
        bytes=si_rotate_bytes.execute(f);
    }



    // Log bytes for easy control plane debug
    Register<bit<32>, bit<32>>(1024) riBytes;
    RegisterAction<bit<32>, bit<32>, bit<32>>(riBytes) siDebugWriteBytes = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = bytes;
        }
    };
    action aiDebugWriteBytes() {
        siDebugWriteBytes.execute((bit<32>)f);
    }


    // Log last size from rotate packets... what are we subtracting?
    Register<bit<32>, bit<32>>(1024) riRotateLastSize;
    RegisterAction<bit<32>, bit<32>, bit<32>>(riRotateLastSize) siDebugLastSize = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = aggregate_size;
        }
    };
    action aiDebugLastSize() {
        siDebugLastSize.execute((bit<32>)f);
    }


    bit<32> past_head;
    bit<32> past_tail;

    /* 
    if (bytes - size_head) <= 0 --> to_headq



    */


    action aiCalc_past_head() {
        past_head = bytes |-| rate_head_x_dT; // past_head == 0 --> to head
        // past_tail = 1;
    }

    action aiCalc_past_tail() {
        past_tail = past_head |-| rate_tail_x_dT; // past_tail == 0 --> to tail
    }
    // last task: 
    // assign queue based on head and tail.

    // Count number of packets sent to head, tail, and drop queues
    Register<bit<32>, bit<32>>(1024) queueCounter;
    RegisterAction<bit<32>, bit<32>, bit<32>>(queueCounter) countQueueOps = {
        void apply(inout bit<32> mem, out bit<32> rv) {
            mem = mem + 1;
        }
    };

    action aiSetQueueHead() {
        ig_tm_md.qid = (bit<5>)headq;
        countQueueOps.execute(0);
    }
    action aiSetQueueTail() {
        ig_tm_md.qid = (bit<5>)tailq;
        countQueueOps.execute(1);
    }
    action aiDrop() {
        ig_dprsr_md.drop_ctl = 0x1;        
        countQueueOps.execute(2);
    }


    table tiSetQueue { 
        key = {
            past_head : ternary;
            past_tail : ternary;
        }
        actions = {
            aiSetQueueHead; aiSetQueueTail; aiDrop;
        }
        const entries = {
            (0, _) : aiSetQueueHead();
            (_, 0) : aiSetQueueTail();
            (_, _) : aiDrop();
        }
    }

    // ROTATE PACKET DEBUGGING
    Hash<bit<32>>(HashAlgorithm_t.CUSTOM, identity_poly) identity_hasher3;
    action aiDrop_rotate() {
        ig_dprsr_md.drop_ctl = 0x1;        
        // ig_tm_md.ucast_egress_port = 144;
        // hdr.ethernet.dst_addr = (bit<48>)identity_hasher3.get({f});
    }
    table tiDrop_rotate {
        key = {f : ternary;}
        actions = {aiDrop_rotate;}
        const entries = {
            _ : aiDrop_rotate();
        }
    }
    // END ROTATE PACKET DEBUGGING