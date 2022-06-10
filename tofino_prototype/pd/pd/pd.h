#ifndef _PD_MAIN_PD_H
#define _PD_MAIN_PD_H

#include <stdint.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN_
#define LITTLE_ENDIAN_CALLER 1
#endif

#include <tofino/pdfixed/pd_common.h>
#include <pipe_mgr/pipe_mgr_intf.h>



/* MATCH STRUCTS */

typedef struct p4_pd_main_IngressParser__PORT_METADATA_match_spec {
  uint16_t ig_intr_md_ingress_port;
} p4_pd_main_IngressParser__PORT_METADATA_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiForward_match_spec {
  uint16_t md_ingress_port;
  uint8_t hdr_ethernet_dst_addr[6];
} p4_pd_main_Ingress_t_igr_tiForward_match_spec_t;

/* Ingress_t_igr_tiToggleCebinae has no match fields */

typedef struct p4_pd_main_Ingress_t_igr_tiRotateF_match_spec {
  uint16_t hdr_pktgen_packet_id;
} p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t;

/* Ingress_t_igr_tiRotateRoundTime has no match fields */

typedef struct p4_pd_main_Ingress_t_igr_tiCalcF_match_spec {
  uint32_t hdr_ip_src_addr;
  uint32_t hdr_ip_dst_addr;
} p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec {
  uint16_t ig_tm_md_ucast_egress_port;
} p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec {
  uint16_t f;
} p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t;

/* Ingress_t_igr_tiDrop_rotate has no match fields */

/* Ingress_t_igr_tiRotateTailq has no match fields */

/* tbl_t_igr_aiGetTailq_st1 has no match fields */

/* Ingress_t_igr_tiRotateHeadq has no match fields */

/* tbl_t_igr_aiGetHeadq_st1 has no match fields */

typedef struct p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec {
  uint16_t f;
  uint32_t tailq;
} p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec {
  uint16_t f;
  uint32_t headq;
} p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t;

/* Egress_t_egr_dpt_2_merged_tbl has no match fields */

typedef struct p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec {
  uint32_t rate_tail;
  uint32_t rate_tail_mask;
} p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec {
  uint32_t relative_round_m_dt;
  uint32_t relative_round_m_dt_mask;
} p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec {
  uint32_t relative_round;
  uint32_t relative_round_mask;
} p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec {
  uint32_t rate_head;
  uint32_t rate_head_mask;
} p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t;

/* Egress_t_egr_dpt_1_merged_tbl has no match fields */

/* Egress_t_egr_dpt_4_merged_tbl has no match fields */

/* Egress_t_egr_dpt_3_merged_tbl has no match fields */

typedef struct p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec {
  uint8_t log_relative_round_m_dt_x_rate_tail;
  uint8_t log_relative_round_m_dt_x_rate_tail_mask;
} p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t;

/* Egress_t_egr_dpt_5_merged_tbl has no match fields */

typedef struct p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec {
  uint32_t if_precomp1550;
  uint32_t if_precomp1550_mask;
  uint32_t if_precomp;
  uint32_t if_precomp_mask;
  uint32_t stored_dst;
  uint32_t stored_dst_mask;
  uint32_t stored_src;
  uint32_t stored_src_mask;
} p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec {
  uint32_t if_precomp1550;
  uint32_t if_precomp1550_mask;
  uint32_t if_precomp;
  uint32_t if_precomp_mask;
  uint32_t stored_dst;
  uint32_t stored_dst_mask;
  uint32_t stored_src;
  uint32_t stored_src_mask;
} p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec {
  uint32_t if_precomp1550;
  uint32_t if_precomp1550_mask;
  uint32_t if_precomp;
  uint32_t if_precomp_mask;
  uint32_t stored_dst;
  uint32_t stored_dst_mask;
  uint32_t stored_src;
  uint32_t stored_src_mask;
} p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec {
  uint8_t log_aggregate_size;
  uint8_t log_aggregate_size_mask;
} p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec {
  uint32_t if_precomp1550;
  uint32_t if_precomp1550_mask;
  uint32_t if_precomp;
  uint32_t if_precomp_mask;
  uint32_t stored_dst;
  uint32_t stored_dst_mask;
  uint32_t stored_src;
  uint32_t stored_src_mask;
} p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec {
  uint32_t if_precomp1548;
  uint32_t if_precomp1548_mask;
  uint32_t if_precomp1547;
  uint32_t if_precomp1547_mask;
  uint32_t stored_dst2;
  uint32_t stored_dst2_mask;
  uint32_t stored_src2;
  uint32_t stored_src2_mask;
  uint32_t if_precomp1550;
  uint32_t if_precomp1550_mask;
  uint32_t if_precomp;
  uint32_t if_precomp_mask;
  uint32_t stored_dst;
  uint32_t stored_dst_mask;
  uint32_t stored_src;
  uint32_t stored_src_mask;
} p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec {
  uint32_t past_head;
  uint32_t past_head_mask;
  uint32_t past_tail;
  uint32_t past_tail_mask;
} p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t;



/* Dynamic Exm Table Key Mask */

/* IngressParser__PORT_METADATA has no dynamic key masks */

/* Ingress_t_igr_tiForward has no dynamic key masks */

/* Ingress_t_igr_tiToggleCebinae has no match fields */

/* Ingress_t_igr_tiRotateF has no dynamic key masks */

/* Ingress_t_igr_tiRotateRoundTime has no match fields */

/* Ingress_t_igr_tiCalcF has no dynamic key masks */

/* Ingress_t_igr_tiCalcSaturated has no dynamic key masks */

/* Ingress_t_igr_tiReadLastSize has no dynamic key masks */

/* Ingress_t_igr_tiDrop_rotate has no match fields */

/* Ingress_t_igr_tiRotateTailq has no match fields */

/* tbl_t_igr_aiGetTailq_st1 has no match fields */

/* Ingress_t_igr_tiRotateHeadq has no match fields */

/* tbl_t_igr_aiGetHeadq_st1 has no match fields */

/* Ingress_t_igr_tiGetRates_tail has no dynamic key masks */

/* Ingress_t_igr_tiGetRates_head has no dynamic key masks */

/* Egress_t_egr_dpt_2_merged_tbl has no match fields */

/* Ingress_t_igr_tiCalc_log_rate_tail has no dynamic key masks */

/* Ingress_t_igr_tiCalc_log_relative_round_m_dt has no dynamic key masks */

/* Ingress_t_igr_tiCalc_log_relative_round has no dynamic key masks */

/* Ingress_t_igr_tiCalc_log_rate_head has no dynamic key masks */

/* Egress_t_egr_dpt_1_merged_tbl has no match fields */

/* Egress_t_egr_dpt_4_merged_tbl has no match fields */

/* Egress_t_egr_dpt_3_merged_tbl has no match fields */

/* Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail has no dynamic key masks */

/* Egress_t_egr_dpt_5_merged_tbl has no match fields */

/* Egress_t_egr_dpt_7_merged_tbl has no dynamic key masks */

/* Egress_t_egr_dpt_6_merged_tbl has no dynamic key masks */

/* Egress_t_egr_dpt_8_merged_tbl has no dynamic key masks */

/* Ingress_t_igr_tiExp_aggregate_size has no dynamic key masks */

/* Egress_t_egr_dpt_9_merged_tbl has no dynamic key masks */

/* Egress_t_egr_dpt_10_merged_tbl has no dynamic key masks */

/* Ingress_t_igr_tiSetQueue has no dynamic key masks */



/* ACTION STRUCTS */

/* Enum of all action names. */
typedef enum p4_pd_main_action_names {
  p4_pd_main_set_port_metadata,
  p4_pd_main_Ingress_t_igr_aiSetEgress,
  p4_pd_main_Ingress_t_igr_aiNoop,
  p4_pd_main_NoAction,
  p4_pd_main_Ingress_t_igr_aiToggleCebinae,
  p4_pd_main_Ingress_t_igr_aiRotateF,
  p4_pd_main_Ingress_t_igr_aiRotateRoundTime,
  p4_pd_main_Ingress_t_igr_aiSetFTop,
  p4_pd_main_Ingress_t_igr_aiSetFBottom,
  p4_pd_main_Ingress_t_igr_aiSaturated,
  p4_pd_main_Ingress_t_igr_aiNotSaturated,
  p4_pd_main_Ingress_t_igr_aiReadLastSize,
  p4_pd_main_Ingress_t_igr_aiDrop_rotate,
  p4_pd_main_Ingress_t_igr_aiRotateTailq,
  p4_pd_main_Ingress_t_igr_aiGetTailq,
  p4_pd_main_Ingress_t_igr_aiRotateHeadq,
  p4_pd_main_Ingress_t_igr_aiGetHeadq,
  p4_pd_main_Ingress_t_igr_aiGetRates_tail,
  p4_pd_main_Ingress_t_igr_aiGetRates_head,
  p4_pd_main_Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt,
  p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail,
  p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt,
  p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round,
  p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head,
  p4_pd_main_Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30,
  p4_pd_main_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31,
  p4_pd_main_Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1635_merged_acn_6_noop,
  p4_pd_main_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_0,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_1,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_2,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_3,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_4,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_5,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_6,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_7,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_8,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_9,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_10,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_11,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_12,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_13,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_14,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_15,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_16,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_17,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_18,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_19,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_20,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_21,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_22,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_23,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_24,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_25,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_26,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_27,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_28,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_29,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_30,
  p4_pd_main_Ingress_t_igr_aiExp_aggregate_size_31,
  p4_pd_main_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt,
  p4_pd_main_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt,
  p4_pd_main_Ingress_t_igr_aiSetQueueHead,
  p4_pd_main_Ingress_t_igr_aiSetQueueTail,
  p4_pd_main_Ingress_t_igr_aiDrop,
  p4_pd_main_action_names_t_invalid
} p4_pd_main_action_names_t;

const char* p4_pd_main_action_enum_to_string(p4_pd_main_action_names_t e);

p4_pd_main_action_names_t p4_pd_main_action_string_to_enum(const char* s);

typedef struct p4_pd_main_set_port_metadata_action_spec {
  uint8_t action_ig_intr_md[8];
} p4_pd_main_set_port_metadata_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec {
  uint16_t action_egr_port;
} p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec_t;

  /* Ingress_t_igr_aiNoop has no parameters */

  /* NoAction has no parameters */

typedef struct p4_pd_main_Ingress_t_igr_aiToggleCebinae_action_spec {
  uint8_t action_isOn;
} p4_pd_main_Ingress_t_igr_aiToggleCebinae_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiRotateF_action_spec {
  uint16_t action_fval;
} p4_pd_main_Ingress_t_igr_aiRotateF_action_spec_t;

  /* Ingress_t_igr_aiRotateRoundTime has no parameters */

  /* Ingress_t_igr_aiSetFTop has no parameters */

  /* Ingress_t_igr_aiSetFBottom has no parameters */

  /* Ingress_t_igr_aiSaturated has no parameters */

  /* Ingress_t_igr_aiNotSaturated has no parameters */

typedef struct p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec {
  uint32_t action_lastRate_x_dT;
} p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t;

  /* Ingress_t_igr_aiDrop_rotate has no parameters */

  /* Ingress_t_igr_aiRotateTailq has no parameters */

  /* Ingress_t_igr_aiGetTailq has no parameters */

  /* Ingress_t_igr_aiRotateHeadq has no parameters */

  /* Ingress_t_igr_aiGetHeadq has no parameters */

typedef struct p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec {
  uint32_t action_r_tail;
  uint32_t action_r_tail_x_dT;
} p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec {
  uint32_t action_r_head;
  uint32_t action_r_head_x_dT;
} p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t;

  /* Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt has no parameters */

typedef struct p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec {
  uint8_t action_log_v;
} p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec {
  uint8_t action_log_v;
} p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec {
  uint8_t action_log_v;
} p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t;

typedef struct p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec {
  uint8_t action_log_v;
} p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t;

  /* Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30 has no parameters */

  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31 has no parameters */

  /* Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1635_merged_acn_6_noop has no parameters */

  /* Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_0 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_1 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_2 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_3 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_4 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_5 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_6 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_7 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_8 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_9 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_10 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_11 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_12 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_13 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_14 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_15 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_16 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_17 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_18 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_19 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_20 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_21 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_22 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_23 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_24 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_25 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_26 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_27 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_28 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_29 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_30 has no parameters */

  /* Ingress_t_igr_aiExp_aggregate_size_31 has no parameters */

  /* Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt has no parameters */

  /* Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt has no parameters */

  /* Ingress_t_igr_aiSetQueueHead has no parameters */

  /* Ingress_t_igr_aiSetQueueTail has no parameters */

  /* Ingress_t_igr_aiDrop has no parameters */


typedef struct p4_pd_main_action_specs_t {
  p4_pd_main_action_names_t name;
  union {
    struct p4_pd_main_set_port_metadata_action_spec p4_pd_main_set_port_metadata;
    struct p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec p4_pd_main_Ingress_t_igr_aiSetEgress;
  /* Ingress_t_igr_aiNoop has no parameters */
  /* NoAction has no parameters */
    struct p4_pd_main_Ingress_t_igr_aiToggleCebinae_action_spec p4_pd_main_Ingress_t_igr_aiToggleCebinae;
    struct p4_pd_main_Ingress_t_igr_aiRotateF_action_spec p4_pd_main_Ingress_t_igr_aiRotateF;
  /* Ingress_t_igr_aiRotateRoundTime has no parameters */
  /* Ingress_t_igr_aiSetFTop has no parameters */
  /* Ingress_t_igr_aiSetFBottom has no parameters */
  /* Ingress_t_igr_aiSaturated has no parameters */
  /* Ingress_t_igr_aiNotSaturated has no parameters */
    struct p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec p4_pd_main_Ingress_t_igr_aiReadLastSize;
  /* Ingress_t_igr_aiDrop_rotate has no parameters */
  /* Ingress_t_igr_aiRotateTailq has no parameters */
  /* Ingress_t_igr_aiGetTailq has no parameters */
  /* Ingress_t_igr_aiRotateHeadq has no parameters */
  /* Ingress_t_igr_aiGetHeadq has no parameters */
    struct p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec p4_pd_main_Ingress_t_igr_aiGetRates_tail;
    struct p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec p4_pd_main_Ingress_t_igr_aiGetRates_head;
  /* Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt has no parameters */
    struct p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail;
    struct p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt;
    struct p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round;
    struct p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head;
  /* Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30 has no parameters */
  /* Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31 has no parameters */
  /* Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1635_merged_acn_6_noop has no parameters */
  /* Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_0 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_1 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_2 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_3 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_4 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_5 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_6 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_7 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_8 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_9 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_10 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_11 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_12 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_13 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_14 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_15 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_16 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_17 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_18 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_19 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_20 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_21 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_22 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_23 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_24 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_25 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_26 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_27 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_28 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_29 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_30 has no parameters */
  /* Ingress_t_igr_aiExp_aggregate_size_31 has no parameters */
  /* Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt has no parameters */
  /* Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt has no parameters */
  /* Ingress_t_igr_aiSetQueueHead has no parameters */
  /* Ingress_t_igr_aiSetQueueTail has no parameters */
  /* Ingress_t_igr_aiDrop has no parameters */
  } u;
} p4_pd_main_action_specs_t;

void p4_pd_main_init(void);

/* HA TESTING INFRASTRUCTURE */

/* REGISTER VALUES */

typedef struct p4_pd_main_Ingress_t_igr_ri_bytes_value {
  uint32_t f0;
  uint32_t f1;
} p4_pd_main_Ingress_t_igr_ri_bytes_value_t;


/* IDLE TIME CONFIG */


p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_to_entry_hdl
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);



/* Dynamic Exm Table Key Mask */


/* ADD ENTRIES */

/**
 * @brief p4_pd_main_IngressParser__PORT_METADATA_table_add_with_set_port_metadata
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_add_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_main_set_port_metadata_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_add_with_Ingress_t_igr_aiRotateF
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_add_with_Ingress_t_igr_aiRotateF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiRotateF_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFBottom
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFBottom
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiNotSaturated
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiNotSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_Ingress_t_igr_aiCalc_log_rate_tail
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_Ingress_t_igr_aiCalc_log_rate_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_add_with_Ingress_t_igr_aiCalc_log_relative_round
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_add_with_Ingress_t_igr_aiCalc_log_relative_round
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_add_with_Ingress_t_igr_aiCalc_log_rate_head
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_add_with_Ingress_t_igr_aiCalc_log_rate_head
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_0
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_0
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_1
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_2
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_3
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_4
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_4
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_5
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_5
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_6
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_6
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_7
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_7
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_8
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_8
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_9
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_9
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_10
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_10
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_11
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_11
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_12
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_12
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_13
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_13
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_14
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_14
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_15
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_15
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_16
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_16
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_17
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_17
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_18
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_18
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_19
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_19
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_20
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_20
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_21
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_21
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_22
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_22
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_23
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_23
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_24
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_24
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_25
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_25
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_26
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_26
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_27
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_27
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_28
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_28
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_29
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_29
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_30
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_30
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_31
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_31
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueHead
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueHead
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueTail
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueTail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiDrop
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiDrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority,
 p4_pd_entry_hdl_t *entry_hdl
);


/* DELETE ENTRIES */

/**
 * @brief p4_pd_main_IngressParser__PORT_METADATA_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_IngressParser__PORT_METADATA_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_IngressParser__PORT_METADATA_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_delete
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_delete_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority
);


/* Get default entry handle */

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_get_default_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 p4_pd_entry_hdl_t* entry_hdl
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_get_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);


/* Clear default entry */

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_reset_default_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t pd_dev_tgt
);


/* MODIFY TABLE PROPERTIES */

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_set_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t value,
 p4_pd_tbl_prop_args_t args
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_get_property
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_tbl_prop_type_t property,
 p4_pd_tbl_prop_value_t *value,
 p4_pd_tbl_prop_args_t *args
);


/* MODIFY ENTRIES */

/**
 * @brief p4_pd_main_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_set_port_metadata_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_IngressParser__PORT_METADATA_match_spec_t * const match_spec,
 const p4_pd_main_set_port_metadata_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiRotateF_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiRotateF_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
 * @param action_spec
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * const match_spec,
 int priority,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t * const action_spec
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_NoAction
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_NoAction_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_NoAction_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop
 * @param sess_hdl
 * @param dev_id
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t ent_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop_by_match_spec
 * @param sess_hdl
 * @param dev_tgt
 * @param match_spec
 * @param priority
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * const match_spec,
 int priority
);



/* SET DEFAULT_ACTION */

/**
 * @brief p4_pd_main_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiToggleCebinae_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiToggleCebinae_set_default_action_Ingress_t_igr_aiToggleCebinae
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_set_default_action_Ingress_t_igr_aiToggleCebinae
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiToggleCebinae_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateF_set_default_action_Ingress_t_igr_aiRotateF
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_set_default_action_Ingress_t_igr_aiRotateF
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiRotateF_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateRoundTime_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateRoundTime_set_default_action_Ingress_t_igr_aiRotateRoundTime
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_set_default_action_Ingress_t_igr_aiRotateRoundTime
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcF_set_default_action_Ingress_t_igr_aiSetFBottom
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_set_default_action_Ingress_t_igr_aiSetFBottom
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalcSaturated_set_default_action_Ingress_t_igr_aiNotSaturated
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_set_default_action_Ingress_t_igr_aiNotSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiReadLastSize_set_default_action_Ingress_t_igr_aiReadLastSize
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_set_default_action_Ingress_t_igr_aiReadLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiDrop_rotate_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiDrop_rotate_set_default_action_Ingress_t_igr_aiDrop_rotate
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_set_default_action_Ingress_t_igr_aiDrop_rotate
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateTailq_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateTailq_set_default_action_Ingress_t_igr_aiRotateTailq
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_set_default_action_Ingress_t_igr_aiRotateTailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_tbl_t_igr_aiGetTailq_st1_set_default_action_Ingress_t_igr_aiGetTailq
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_set_default_action_Ingress_t_igr_aiGetTailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateHeadq_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiRotateHeadq_set_default_action_Ingress_t_igr_aiRotateHeadq
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_set_default_action_Ingress_t_igr_aiRotateHeadq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_tbl_t_igr_aiGetHeadq_st1_set_default_action_Ingress_t_igr_aiGetHeadq
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_set_default_action_Ingress_t_igr_aiGetHeadq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_tail_set_default_action_Ingress_t_igr_aiGetRates_tail
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_set_default_action_Ingress_t_igr_aiGetRates_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiGetRates_head_set_default_action_Ingress_t_igr_aiGetRates_head
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_set_default_action_Ingress_t_igr_aiGetRates_head
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_set_default_action_Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_set_default_action_Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_Ingress_t_igr_aiCalc_log_rate_tail
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_Ingress_t_igr_aiCalc_log_rate_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_Ingress_t_igr_aiCalc_log_relative_round_m_dt
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_Ingress_t_igr_aiCalc_log_relative_round_m_dt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_set_default_action_Ingress_t_igr_aiCalc_log_relative_round
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_set_default_action_Ingress_t_igr_aiCalc_log_relative_round
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_set_default_action_Ingress_t_igr_aiCalc_log_rate_head
 * @param sess_hdl
 * @param dev_tgt
 * @param action_spec
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_set_default_action_Ingress_t_igr_aiCalc_log_rate_head
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_set_default_action_Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_set_default_action_Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_set_default_action_Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_set_default_action_Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_set_default_action_Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_set_default_action_Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_set_default_action_Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_set_default_action_Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_0
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_0
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_1
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_2
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_3
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_3
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_4
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_4
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_5
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_5
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_6
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_6
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_7
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_7
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_8
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_8
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_9
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_9
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_10
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_10
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_11
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_11
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_12
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_12
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_13
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_13
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_14
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_14
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_15
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_15
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_16
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_16
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_17
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_17
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_18
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_18
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_19
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_19
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_20
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_20
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_21
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_21
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_22
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_22
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_23
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_23
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_24
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_24
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_25
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_25
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_26
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_26
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_27
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_27
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_28
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_28
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_29
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_29
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_30
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_30
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_31
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_31
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_NoAction
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_NoAction
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueHead
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueHead
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueTail
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueTail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);

/**
 * @brief p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiDrop
 * @param sess_hdl
 * @param dev_tgt
 * @param entry_hdl
*/
p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiDrop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_hdl
);



/* INDIRECT ACTION DATA AND MATCH SELECT */






p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_get_entry_count
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *count
);



p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_IngressParser__PORT_METADATA_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_IngressParser__PORT_METADATA_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiForward_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiForward_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiToggleCebinae_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateF_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiRotateF_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateRoundTime_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiDrop_rotate_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateTailq_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetTailq_st1_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiRotateHeadq_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_tbl_t_igr_aiGetHeadq_st1_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * match_spec,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_2_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_1_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_4_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_3_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_5_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_get_first_entry_handle
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t *entry_handle
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_get_next_entry_handles
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_entry_hdl_t entry_handle,
 int n,
 p4_pd_entry_hdl_t *next_entry_handles
);

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiSetQueue_get_entry
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 bool read_from_hw,
 p4_pd_main_Ingress_t_igr_tiSetQueue_match_spec_t * match_spec,
 int *priority,
 p4_pd_main_action_specs_t * const action_spec
);






p4_pd_status_t
p4_pd_main_set_learning_timeout(p4_pd_sess_hdl_t shdl,
                                    uint8_t          device_id,
                                    uint32_t         usecs);

/* COUNTERS */




// REGISTERS

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 p4_pd_main_Ingress_t_igr_ri_bytes_value_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 p4_pd_main_Ingress_t_igr_ri_bytes_value_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_main_Ingress_t_igr_ri_bytes_value_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_ri_bytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 p4_pd_main_Ingress_t_igr_ri_bytes_value_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_ri_base_round_time
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_hw_sync_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 p4_pd_register_sync_cb cb_fn,
 void *cb_cookie
);

p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
);

p4_pd_status_t
p4_pd_main_register_write_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
);

p4_pd_status_t
p4_pd_main_register_range_reset_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count
);

p4_pd_status_t
p4_pd_main_register_write_all_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 uint32_t *register_value
);

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 int *num_actually_read,
 uint32_t *register_values,
 int *value_count
);



/* METERS */


/* LPF */


/* WRED */



typedef struct __attribute__((__packed__)) p4_pd_main_ig_snapshot_trig_spec {
  uint16_t Ingress_t_igr_ri_headq_index;
  uint16_t Ingress_t_igr_ri_tailq_index;
  uint8_t hdr_ethernet_dst_addr[6];
  uint16_t hdr_ethernet_ether_type;
  uint8_t hdr_ethernet_src_addr[6];
  uint32_t hdr_ip_dst_addr;
  uint8_t hdr_ip_flags;
  uint16_t hdr_ip_frag_offset;
  uint16_t hdr_ip_hdr_checksum;
  uint16_t hdr_ip_identification;
  uint8_t hdr_ip_ihl;
  uint8_t hdr_ip_protocol;
  uint32_t hdr_ip_src_addr;
  uint8_t hdr_ip_tos;
  uint16_t hdr_ip_total_len;
  uint8_t hdr_ip_ttl;
  uint8_t hdr_ip_version;
  uint16_t hdr_pktgen_packet_id;
  uint8_t ig_intr_md_ingress_mac_tstamp[6];
  uint8_t ig_intr_md_for_dprsr_drop_ctl;
  uint8_t ig_intr_md_for_tm_qid;
  uint16_t ig_intr_md_for_tm_ucast_egress_port;
  uint16_t md_ingress_port;
  uint32_t t_igr_aggregate_size;
  uint32_t t_igr_bytes;
  uint32_t t_igr_dT_minus_relative_round;
  uint16_t t_igr_f;
  uint32_t t_igr_headq;
  uint8_t t_igr_log_aggregate_size;
  uint8_t t_igr_log_rate_head;
  uint8_t t_igr_log_rate_tail;
  uint8_t t_igr_log_relative_round;
  uint8_t t_igr_log_relative_round_m_dt;
  uint8_t t_igr_log_relative_round_m_dt_x_rate_tail;
  uint32_t t_igr_past_head;
  uint32_t t_igr_past_tail;
  uint32_t t_igr_pkt_len;
  uint32_t t_igr_rate_head;
  uint32_t t_igr_rate_head_x_dT;
  uint32_t t_igr_rate_tail;
  uint32_t t_igr_rate_tail_x_dT;
  uint32_t t_igr_relative_round;
  uint32_t t_igr_relative_round_m_dt;
  uint32_t t_igr_relative_round_m_dt_x_rate_tail;
  uint8_t t_igr_saturated;
  uint32_t t_igr_tailq;
  uint32_t t_igr_ts;
  uint8_t t_igr_useCebinae;
  /* POV fields */
  uint8_t hdr_ethernet_valid;
  uint8_t hdr_ip_valid;

} p4_pd_main_ig_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_main_eg_snapshot_trig_spec {
  uint16_t eg_intr_md_egress_port;
  uint8_t hdr_ethernet_dst_addr[6];
  uint16_t hdr_ethernet_ether_type;
  uint8_t hdr_ethernet_src_addr[6];
  uint32_t hdr_ip_dst_addr;
  uint8_t hdr_ip_flags;
  uint16_t hdr_ip_frag_offset;
  uint16_t hdr_ip_hdr_checksum;
  uint16_t hdr_ip_identification;
  uint8_t hdr_ip_ihl;
  uint8_t hdr_ip_protocol;
  uint32_t hdr_ip_src_addr;
  uint8_t hdr_ip_tos;
  uint16_t hdr_ip_total_len;
  uint8_t hdr_ip_ttl;
  uint8_t hdr_ip_version;
  uint32_t len_0;
  uint32_t port_0;
  uint16_t t_egr_h1;
  uint16_t t_egr_h2;
  uint32_t t_egr_if_precomp;
  uint32_t t_egr_if_precomp1547;
  uint32_t t_egr_if_precomp1548;
  uint32_t t_egr_if_precomp1550;
  uint32_t t_egr_stored_dst;
  uint32_t t_egr_stored_dst2;
  uint32_t t_egr_stored_src;
  uint32_t t_egr_stored_src2;
  /* POV fields */
  uint8_t hdr_ethernet_valid;
  uint8_t hdr_ip_valid;

} p4_pd_main_eg_snapshot_trig_spec_t;


typedef struct __attribute__((__packed__)) p4_pd_main_snapshot_trig_spec {
    union {
        p4_pd_main_ig_snapshot_trig_spec_t ig;
        p4_pd_main_eg_snapshot_trig_spec_t eg;
    } u;
}  p4_pd_main_snapshot_trig_spec_t;


typedef p4_pd_main_ig_snapshot_trig_spec_t p4_pd_main_ig_snapshot_capture_data_t;
typedef p4_pd_main_eg_snapshot_trig_spec_t p4_pd_main_eg_snapshot_capture_data_t;


typedef struct __attribute__ ((__packed__)) p4_pd_main_snapshot_capture {
     union {
         p4_pd_main_ig_snapshot_capture_data_t ig;
         p4_pd_main_eg_snapshot_capture_data_t eg;
     } u;
} p4_pd_main_snapshot_capture_t;

/* Array of snapshot captures if start and en stage are different */
typedef struct p4_pd_main_snapshot_capture_arr {
    p4_pd_main_snapshot_capture_t captures[BF_MAX_SNAPSHOT_CAPTURES];
} p4_pd_main_snapshot_capture_arr_t;


/**
 * @brief Set snapshot trigger.
 * @param hdl Snapshot handle.
 * @param trig_spec Trigger spec.
 * @param trig_mask Trigger mask.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_capture_trigger_set(
              pipe_snapshot_hdl_t hdl,
              p4_pd_main_snapshot_trig_spec_t *trig_spec,
              p4_pd_main_snapshot_trig_spec_t *trig_mask);

/**
 * @brief Get snapshot capture data.
 * @param hdl Snapshot handle.
 * @param pipe Pipe.
 * @param capture Captured data
 * @param num_captures Num of captures
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_capture_data_get(
              pipe_snapshot_hdl_t hdl,
              bf_dev_pipe_t dev_pipe_id,
              p4_pd_main_snapshot_capture_arr_t *capture,
              bf_snapshot_capture_ctrl_info_arr_t *capture_ctrl_arr,
              int *num_captures);

/**
 * @brief Create a snapshot.
 * @param dev_tgt Device information.
 * @param start_stage_id Start stage.
 * @param end_stage_id End stage.
 * @param direction Ingress or egress
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_create(
            p4_pd_dev_target_t dev_tgt,
            uint8_t start_stage_id, uint8_t end_stage_id,
            bf_snapshot_dir_t direction,
            pipe_snapshot_hdl_t *hdl);

/**
 * @brief Delete snapshot.
 * @param hdl Snapshot handle.
 * @return status.
*/
p4_pd_status_t
p4_pd_main_snapshot_delete(
            pipe_snapshot_hdl_t hdl);





typedef enum p4_pd_main_input_fields__field_list_1{
  P4_PD_INPUT_FIELD__FIELD_LIST_1_HDR_IP_TOTAL_LEN = 0,
} p4_pd_main_input_fields__field_list_1_t;

typedef enum p4_pd_main_input_field_attr_type {
  P4_PD_INPUT_FIELD_ATTR_TYPE_MASK = 0,
  P4_PD_INPUT_FIELD_ATTR_TYPE_VALUE,
} p4_pd_main_input_field_attr_type_t;

typedef enum p4_pd_main_input_field_attr_value_mask {
  P4_PD_INPUT_FIELD_EXCLUDED = 0,
  P4_PD_INPUT_FIELD_INCLUDED
} p4_pd_main_input_field_attr_value_mask_t;

typedef enum p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input{
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t;

typedef struct p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute{
  union {
    p4_pd_main_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_main_input_field_attr_type_t type;
  union {
    p4_pd_main_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t;

typedef enum p4_pd_main_Ingress_t_igr_identity_hasher0_configure_algo {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32,
} p4_pd_main_Ingress_t_igr_identity_hasher0_configure_algo_t;

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t input
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t *input
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_algo_t algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
);
typedef enum p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input{
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1560_HASHER_1764_ALU_0_OPSTMT_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute{
  union {
    p4_pd_main_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_main_input_field_attr_type_t type;
  union {
    p4_pd_main_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t;

typedef enum p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1560_HASHER_1764_ALU_0_OPSTMT_CONFIGURE_ALGORITHM_CRC_10,
} p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo_t;

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t *input
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo_t algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input,
 uint32_t attr_count,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
);
typedef enum p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input{
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t;

typedef struct p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute{
  union {
    p4_pd_main_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_main_input_field_attr_type_t type;
  union {
    p4_pd_main_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t;

typedef enum p4_pd_main_Ingress_t_igr_identity_hasher2_configure_algo {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32,
} p4_pd_main_Ingress_t_igr_identity_hasher2_configure_algo_t;

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t input
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t *input
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_algo_t algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

p4_pd_status_t
p4_pd_main_hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
);
typedef enum p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input{
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1562_HASHER_1766_ALU_0_OPSTMT_CONFIGURE_INPUT__FIELD_LIST_1,
} p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t;

typedef struct p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute{
  union {
    p4_pd_main_input_fields__field_list_1_t _field_list_1;
    uint32_t id;
  } input_field;
  p4_pd_main_input_field_attr_type_t type;
  union {
    p4_pd_main_input_field_attr_value_mask_t mask;
    uint32_t val;
    uint8_t *stream;
  } value;
} p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t;

typedef enum p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1562_HASHER_1766_ALU_0_OPSTMT_CONFIGURE_ALGORITHM_CRC_10,
} p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo_t;

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t *input
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algorithm_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo_t algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algorithm_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo_t *algo
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_seed_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_seed_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint64_t *seed
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_set
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input,
 uint32_t attr_count,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_count_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input,
 uint32_t *attr_count
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_get
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input,
 uint32_t max_attr_count,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *num_attr_filled
);

p4_pd_status_t
p4_pd_main_hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_calculate_hash_value
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 uint32_t attr_count,
 p4_pd_main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t *array_of_attrs,
 uint32_t *attr_sizes,
 uint8_t *hash,
 uint32_t hash_len
);

#endif
