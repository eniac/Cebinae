#include <core.p4>
#include <tna.p4>

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_ROTATE 0x1234

// the port from 128 --> 136 is the bottleneck.
#define BOTTLENECK_PORT 128

/*=============================================
=            Headers and metadata.            =
=============================================*/
typedef bit<48> mac_addr_t;
header ethernet_h {
    mac_addr_t dst_addr;
    mac_addr_t src_addr;
    bit<16> ether_type;
}

typedef bit<32> ipv4_addr_t;
header ipv4_h {
    bit<4> version;
    bit<4> ihl;
    bit<8> tos;
    bit<16> total_len;
    bit<16> identification;
    bit<3> flags;
    bit<13> frag_offset;
    bit<8> ttl;
    bit<8> protocol;
    bit<16> hdr_checksum;
    ipv4_addr_t src_addr;
    ipv4_addr_t dst_addr;
}

header rotate_h {
    bit<16> f;
}

struct header_t {
    pktgen_timer_header_t pktgen;
    ethernet_h ethernet;
    rotate_h rotate;
    ipv4_h ip;
}
struct metadata_t { 
    bit<16> ingress_port;
}

#include "ingress.p4"
#include "egress.dpt.p4"

/*===============================
=            Parsing            =
===============================*/
// Parser for tofino-specific metadata.
parser TofinoIngressParser(
        packet_in pkt,        
        out ingress_intrinsic_metadata_t ig_intr_md,
        out header_t hdr,
        out metadata_t md) {
    state start {
        pkt.extract(ig_intr_md);
        md.ingress_port = (bit<16>)ig_intr_md.ingress_port;
        pkt.advance(64); // skip port metadata
        transition select(ig_intr_md.ingress_port) {
            196 : parse_pktgen;
            68 : parse_pktgen;
            default : accept;
        }
        // transition accept;
    }
    // LEFT OFF HERE: just added parse_pktgen.
    // Look at the pktgen packets coming to the host. 
    // Figure out the batch number or packet number, 
    // so that you can increment it and use it as F.
    // NEXT: add F table, then start testing for real.
    state parse_pktgen {
        pkt.extract(hdr.pktgen);
        transition accept;
    }

}

parser EthIpParser(packet_in pkt, out header_t hdr, out metadata_t md){
    state start {
        pkt.extract(hdr.ethernet);
        transition select(hdr.ethernet.ether_type) {
            ETHERTYPE_ROTATE : parse_rotate;
            ETHERTYPE_IPV4 : parse_ip;
            default : accept;
        }
    }
    state parse_rotate {
        pkt.extract(hdr.rotate);
        transition accept;
    }
    state parse_ip {
        pkt.extract(hdr.ip);
        transition accept;
    }
}


parser TofinoEgressParser(
        packet_in pkt,
        out egress_intrinsic_metadata_t eg_intr_md) {
    state start {
        pkt.extract(eg_intr_md);
        transition accept;
    }
}

/*========================================
=            Ingress parsing             =
========================================*/

parser IngressParser(
        packet_in pkt,
        out header_t hdr, 
        out metadata_t md,
        out ingress_intrinsic_metadata_t ig_intr_md)
{
    state start {
        TofinoIngressParser.apply(pkt, ig_intr_md, hdr, md);
        EthIpParser.apply(pkt, hdr, md);
        transition accept;
    }
}


/*===========================================
=            ingress match-action             =
===========================================*/
control Ingress(
        inout header_t hdr, 
        inout metadata_t md,
        in ingress_intrinsic_metadata_t ig_intr_md,
        in ingress_intrinsic_metadata_from_parser_t ig_prsr_md,
        inout ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md,
        inout ingress_intrinsic_metadata_for_tm_t ig_tm_md) {

    Cebinae_igr() t_igr;

    apply {        
        t_igr.apply(hdr, md, ig_dprsr_md, ig_intr_md, ig_tm_md);
        // ig_tm_md.qid = (bit<5>) assigned_queue;
    }
}

control IngressDeparser(
        packet_out pkt, 
        inout header_t hdr, 
        in metadata_t md,
        in ingress_intrinsic_metadata_for_deparser_t ig_dprsr_md) {
    apply {
        // pkt.emit(hdr);
        // skip pktgen and rotate headers
        pkt.emit(hdr.ethernet);
        pkt.emit(hdr.ip);
    }
}

/*======================================
=            Egress parsing            =
======================================*/
parser EgressParser(
        packet_in pkt,
        out header_t hdr, 
        out metadata_t eg_md,
        out egress_intrinsic_metadata_t eg_intr_md) {
    TofinoEgressParser() tofino_parser;
    EthIpParser() eth_ip_parser; 
    state start {
        tofino_parser.apply(pkt, eg_intr_md);
        transition parse_packet;
    }
    state parse_packet {
        eth_ip_parser.apply(pkt, hdr, eg_md);
        transition accept;        
    }
}

/*=========================================
=            Egress match-action            =
=========================================*/
control Egress(
        inout header_t hdr, 
        inout metadata_t eg_mg,
        in egress_intrinsic_metadata_t eg_intr_md,
        in egress_intrinsic_metadata_from_parser_t eg_prsr_md,
        inout egress_intrinsic_metadata_for_deparser_t eg_dprsr_md,
        inout egress_intrinsic_metadata_for_output_port_t eg_oport_md){

        Cebinae_egress() t_egr;
    apply { 
        bit<32> port = (bit<32>)eg_intr_md.egress_port;
        bit<32> len = (bit<32>)hdr.ip.total_len;
        if (port == BOTTLENECK_PORT) {
            t_egr.apply(
                port, 
                hdr.ip.src_addr,
                hdr.ip.dst_addr, 
                len
            );            
        }
    }
}

control EgressDeparser(
        packet_out pkt,
        inout header_t hdr, 
        in metadata_t eg_md,
        in egress_intrinsic_metadata_for_deparser_t eg_dprsr_md) {
    apply {
        // pkt.emit(hdr);
        // skip pktgen and rotate headers
        pkt.emit(hdr.ethernet);
        pkt.emit(hdr.ip);
    }
}
/*==============================================
=            The switch's pipeline             =
==============================================*/
Pipeline(
    IngressParser(), Ingress(), IngressDeparser(),
    EgressParser(), Egress(), EgressDeparser()) pipe;

Switch(pipe) main;