#include <core.p4>
#include <tna.p4>

    struct fmt_port_cts {
        bit<32> lo;
    }
    struct fmt_flow_src1 {
        bit<32> lo;
    }
    struct fmt_flow_dst1 {
        bit<32> lo;
    }
    struct fmt_flow_ct1 {
        bit<32> lo;
    }
    struct fmt_flow_src2 {
        bit<32> lo;
    }
    struct fmt_flow_dst2 {
        bit<32> lo;
    }
    struct fmt_flow_ct2 {
        bit<32> lo;
    }
control Cebinae_egress(inout bit<32> port,inout bit<32> src,inout bit<32> dst,inout bit<32> pkt_len) {
 
    bit<10> h1;
    
    bit<10> h2;
    
    bit<32> stored_src;
    
    bit<32> stored_dst;
    
    bit<32> if_precomp;
    
    bit<32> if_precomp1550;
    
    bit<32> stored_src2;
    
    bit<32> stored_dst2;
    
    bit<32> if_precomp1547;
    
    bit<32> if_precomp1548;
    
    Register<fmt_port_cts, bit<32>>(32) port_cts;
    
    Register<fmt_flow_src1, bit<32>>(1024) flow_src1;
    
    Register<fmt_flow_dst1, bit<32>>(1024) flow_dst1;
    
    Register<fmt_flow_ct1, bit<32>>(1024) flow_ct1;
    
    Register<fmt_flow_src2, bit<32>>(1024) flow_src2;
    
    Register<fmt_flow_dst2, bit<32>>(1024) flow_dst2;
    
    Register<fmt_flow_ct2, bit<32>>(1024) flow_ct2;
    
    RegisterAction<fmt_port_cts,bit<32>,bit<32>>(port_cts) dpt_1559_sprog_1763_salu_0_opstmt = {
        void apply(inout fmt_port_cts remote, out bit<32> remoteRet) {
            fmt_port_cts local = remote;
            remote.lo=local.lo + pkt_len;
        }
    };
    action dpt_1559_salu_0_opstmt() {
        dpt_1559_sprog_1763_salu_0_opstmt.execute((bit<32>)port);
    }
    
    CRCPolynomial<bit<10>>(101, false, false, false, 0, 0) dpt_1765_poly;
    Hash<bit<10>>(HashAlgorithm_t.CUSTOM, dpt_1765_poly) dpt_1560_hasher_1764_alu_0_opstmt;
    action dpt_1560_alu_0_opstmt() {
        h1 = dpt_1560_hasher_1764_alu_0_opstmt.get({src, dst});
        }
    
    action dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt( ){
        dpt_1560_alu_0_opstmt();
        dpt_1559_salu_0_opstmt();
        //next tables: [dpt_1562_tbl_0_opstmt, dpt_1560_tbl_0_opstmt]
        
    }
    
    @ignore_table_dependency("Ingress.dpt_2_merged_tbl")
    table dpt_1_merged_tbl {
        actions = {
            dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt;
        }
        const default_action = dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt();
        
    }
    
    CRCPolynomial<bit<10>>(107, false, false, false, 0, 0) dpt_1767_poly;
    Hash<bit<10>>(HashAlgorithm_t.CUSTOM, dpt_1767_poly) dpt_1562_hasher_1766_alu_0_opstmt;
    action dpt_1562_alu_0_opstmt() {
        h2 = dpt_1562_hasher_1766_alu_0_opstmt.get({src, dst});
        }
    
    action dpt_1562_merged_acn_2_acn_0_opstmt( ){
        dpt_1562_alu_0_opstmt();
        //next tables: [dpt_1564_tbl_0_opstmt]
        
    }
    
    @ignore_table_dependency("Ingress.dpt_1_merged_tbl")
    table dpt_2_merged_tbl {
        actions = {
            dpt_1562_merged_acn_2_acn_0_opstmt;
        }
        const default_action = dpt_1562_merged_acn_2_acn_0_opstmt();
        
    }
    
    RegisterAction<fmt_flow_dst1,bit<32>,bit<32>>(flow_dst1) dpt_1566_sprog_1768_salu_0_opstmt = {
        void apply(inout fmt_flow_dst1 remote, out bit<32> remoteRet) {
            fmt_flow_dst1 local = remote;
            remoteRet=local.lo;
            if (local.lo + 0 == 0){
                remote.lo=dst;;
            }
            if (!(local.lo + 0 == 0)){
                remote.lo=local.lo;;
            }
        }
    };
    action dpt_1566_salu_0_opstmt() {
        stored_dst=dpt_1566_sprog_1768_salu_0_opstmt.execute((bit<32>)h1);
    }
    
    action dpt_1566_merged_acn_3_acn_0_opstmt( ){
        dpt_1566_salu_0_opstmt();
        //next tables: [dpt_1568_tbl_0_opstmt]
        
    }
    
    @ignore_table_dependency("Ingress.dpt_4_merged_tbl")
    table dpt_3_merged_tbl {
        actions = {
            dpt_1566_merged_acn_3_acn_0_opstmt;
        }
        const default_action = dpt_1566_merged_acn_3_acn_0_opstmt();
        
    }
    
    RegisterAction<fmt_flow_src1,bit<32>,bit<32>>(flow_src1) dpt_1564_sprog_1769_salu_0_opstmt = {
        void apply(inout fmt_flow_src1 remote, out bit<32> remoteRet) {
            fmt_flow_src1 local = remote;
            remoteRet=local.lo;
            if (local.lo + 0 == 0){
                remote.lo=src;;
            }
            if (!(local.lo + 0 == 0)){
                remote.lo=local.lo;;
            }
        }
    };
    action dpt_1564_salu_0_opstmt() {
        stored_src=dpt_1564_sprog_1769_salu_0_opstmt.execute((bit<32>)h1);
    }
    
    action dpt_1564_merged_acn_4_acn_0_opstmt( ){
        dpt_1564_salu_0_opstmt();
        //next tables: [dpt_1566_tbl_0_opstmt]
        
    }
    
    @ignore_table_dependency("Ingress.dpt_3_merged_tbl")
    table dpt_4_merged_tbl {
        actions = {
            dpt_1564_merged_acn_4_acn_0_opstmt;
        }
        const default_action = dpt_1564_merged_acn_4_acn_0_opstmt();
        
    }
    
    action dpt_1568_alu_0_opstmt( ){
        if_precomp = stored_src - src;
        
    }
    
    action dpt_1570_alu_0_opstmt( ){
        if_precomp1550 = stored_dst - dst;
        
    }
    
    action dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt( ){
        dpt_1570_alu_0_opstmt();
        dpt_1568_alu_0_opstmt();
        //next tables: [dpt_1576_tbl_0_opstmt, dpt_1577_tbl_0_opstmt, dpt_1570_tbl_0_opstmt]
        
    }
    
    table dpt_5_merged_tbl {
        actions = {
            dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt;
        }
        const default_action = dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt();
        
    }
    
    RegisterAction<fmt_flow_dst2,bit<32>,bit<32>>(flow_dst2) dpt_1581_sprog_1770_salu_0_opstmt = {
        void apply(inout fmt_flow_dst2 remote, out bit<32> remoteRet) {
            fmt_flow_dst2 local = remote;
            remoteRet=local.lo;
            if (local.lo + 0 == 0){
                remote.lo=dst;;
            }
            if (!(local.lo + 0 == 0)){
                remote.lo=local.lo;;
            }
        }
    };
    action dpt_1581_salu_0_opstmt() {
        stored_dst2=dpt_1581_sprog_1770_salu_0_opstmt.execute((bit<32>)h2);
    }
    
    action dpt_1581_merged_acn_6_acn_0_opstmt( ){
        dpt_1581_salu_0_opstmt();
        //next tables: [dpt_1584_tbl_0_opstmt]
        
    }
    
    action dpt_1635_merged_acn_6_noop( ){
        //next tables: []
        
    }
    
    @ignore_table_dependency("Ingress.dpt_8_merged_tbl")
    @ignore_table_dependency("Ingress.dpt_7_merged_tbl")
    table dpt_6_merged_tbl {
        key = {
            if_precomp1550 : ternary;
            if_precomp : ternary;
            stored_dst : ternary;
            stored_src : ternary;
        }
        actions = {
            dpt_1635_merged_acn_6_noop;
            dpt_1581_merged_acn_6_acn_0_opstmt;
        }
        const entries = {
            (_, _, 0, 0) : dpt_1635_merged_acn_6_noop();
            (0, 0, _, _) : dpt_1635_merged_acn_6_noop();
            (_, _, _, _) : dpt_1581_merged_acn_6_acn_0_opstmt();
        }
        
    }
    
    RegisterAction<fmt_flow_src2,bit<32>,bit<32>>(flow_src2) dpt_1577_sprog_1771_salu_0_opstmt = {
        void apply(inout fmt_flow_src2 remote, out bit<32> remoteRet) {
            fmt_flow_src2 local = remote;
            remoteRet=local.lo;
            if (local.lo + 0 == 0){
                remote.lo=src;;
            }
            if (!(local.lo + 0 == 0)){
                remote.lo=local.lo;;
            }
        }
    };
    action dpt_1577_salu_0_opstmt() {
        stored_src2=dpt_1577_sprog_1771_salu_0_opstmt.execute((bit<32>)h2);
    }
    
    action dpt_1577_merged_acn_7_acn_0_opstmt( ){
        dpt_1577_salu_0_opstmt();
        //next tables: [dpt_1581_tbl_0_opstmt]
        
    }
    
    @ignore_table_dependency("Ingress.dpt_8_merged_tbl")
    @ignore_table_dependency("Ingress.dpt_6_merged_tbl")
    table dpt_7_merged_tbl {
        key = {
            if_precomp1550 : ternary;
            if_precomp : ternary;
            stored_dst : ternary;
            stored_src : ternary;
        }
        actions = {
            dpt_1635_merged_acn_6_noop;
            dpt_1577_merged_acn_7_acn_0_opstmt;
        }
        const entries = {
            (_, _, 0, 0) : dpt_1635_merged_acn_6_noop();
            (0, 0, _, _) : dpt_1635_merged_acn_6_noop();
            (_, _, _, _) : dpt_1577_merged_acn_7_acn_0_opstmt();
        }
        
    }
    
    RegisterAction<fmt_flow_ct1,bit<32>,bit<32>>(flow_ct1) dpt_1576_sprog_1772_salu_0_opstmt = {
        void apply(inout fmt_flow_ct1 remote, out bit<32> remoteRet) {
            fmt_flow_ct1 local = remote;
            remote.lo=local.lo + pkt_len;
        }
    };
    action dpt_1576_salu_0_opstmt() {
        dpt_1576_sprog_1772_salu_0_opstmt.execute((bit<32>)h1);
    }
    
    action dpt_1576_merged_acn_8_acn_0_opstmt( ){
        dpt_1576_salu_0_opstmt();
        //next tables: []
        
    }
    
    @ignore_table_dependency("Ingress.dpt_7_merged_tbl")
    @ignore_table_dependency("Ingress.dpt_6_merged_tbl")
    table dpt_8_merged_tbl {
        key = {
            if_precomp1550 : ternary;
            if_precomp : ternary;
            stored_dst : ternary;
            stored_src : ternary;
        }
        actions = {
            dpt_1576_merged_acn_8_acn_0_opstmt;
            dpt_1635_merged_acn_6_noop;
        }
        const entries = {
            (_, _, 0, 0) : dpt_1576_merged_acn_8_acn_0_opstmt();
            (0, 0, _, _) : dpt_1576_merged_acn_8_acn_0_opstmt();
            (_, _, _, _) : dpt_1635_merged_acn_6_noop();
        }
        
    }
    
    action dpt_1584_alu_0_opstmt( ){
        if_precomp1547 = stored_src2 - src;
        
    }
    
    action dpt_1586_alu_0_opstmt( ){
        if_precomp1548 = stored_dst2 - dst;
        
    }
    
    action dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt( ){
        dpt_1586_alu_0_opstmt();
        dpt_1584_alu_0_opstmt();
        //next tables: [dpt_1592_tbl_0_opstmt, dpt_1586_tbl_0_opstmt]
        
    }
    
    table dpt_9_merged_tbl {
        key = {
            if_precomp1550 : ternary;
            if_precomp : ternary;
            stored_dst : ternary;
            stored_src : ternary;
        }
        actions = {
            dpt_1635_merged_acn_6_noop;
            dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt;
        }
        const entries = {
            (_, _, 0, 0) : dpt_1635_merged_acn_6_noop();
            (0, 0, _, _) : dpt_1635_merged_acn_6_noop();
            (_, _, _, _) : dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt();
        }
        
    }
    
    RegisterAction<fmt_flow_ct2,bit<32>,bit<32>>(flow_ct2) dpt_1592_sprog_1773_salu_0_opstmt = {
        void apply(inout fmt_flow_ct2 remote, out bit<32> remoteRet) {
            fmt_flow_ct2 local = remote;
            remote.lo=local.lo + pkt_len;
        }
    };
    action dpt_1592_salu_0_opstmt() {
        dpt_1592_sprog_1773_salu_0_opstmt.execute((bit<32>)h2);
    }
    
    action dpt_1592_merged_acn_10_acn_0_opstmt( ){
        dpt_1592_salu_0_opstmt();
        //next tables: []
        
    }
    
    table dpt_10_merged_tbl {
        key = {
            if_precomp1548 : ternary;
            if_precomp1547 : ternary;
            stored_dst2 : ternary;
            stored_src2 : ternary;
            if_precomp1550 : ternary;
            if_precomp : ternary;
            stored_dst : ternary;
            stored_src : ternary;
        }
        actions = {
            dpt_1635_merged_acn_6_noop;
            dpt_1592_merged_acn_10_acn_0_opstmt;
        }
        const entries = {
            (_, _, 0, 0, _, _, 0, 0) : dpt_1635_merged_acn_6_noop();
            (_, _, 0, 0, 0, 0, _, _) : dpt_1635_merged_acn_6_noop();
            (_, _, 0, 0, _, _, _, _) : dpt_1592_merged_acn_10_acn_0_opstmt();
            (0, 0, _, _, _, _, 0, 0) : dpt_1635_merged_acn_6_noop();
            (0, 0, _, _, 0, 0, _, _) : dpt_1635_merged_acn_6_noop();
            (0, 0, _, _, _, _, _, _) : dpt_1592_merged_acn_10_acn_0_opstmt();
            (_, _, _, _, _, _, _, _) : dpt_1635_merged_acn_6_noop();
        }
        
    }
    
	apply{
 
    dpt_1_merged_tbl.apply();
    dpt_2_merged_tbl.apply();
    dpt_3_merged_tbl.apply();
    dpt_4_merged_tbl.apply();
    dpt_5_merged_tbl.apply();
    dpt_6_merged_tbl.apply();
    dpt_7_merged_tbl.apply();
    dpt_8_merged_tbl.apply();
    dpt_9_merged_tbl.apply();
    dpt_10_merged_tbl.apply();
	}
}