# BFN Thrift RPC Input

include "res.thrift"


namespace py p4_pd_rpc
namespace cpp p4_pd_rpc
namespace c_glib p4_pd_rpc

typedef i32 EntryHandle_t
typedef i32 MemberHandle_t
typedef i32 GroupHandle_t
typedef binary MacAddr_t
typedef binary IPv6_t
typedef i32 SnapshotHandle_t
typedef i32 PvsHandle_t

struct main_counter_value_t {
  1: required i64 packets;
  2: required i64 bytes;
}

struct main_packets_meter_spec_t {
  1: required i64 cir_pps;
  2: required i64 cburst_pkts;
  3: required i64 pir_pps;
  4: required i64 pburst_pkts;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

struct main_bytes_meter_spec_t {
  1: required i64 cir_kbps;
  2: required i64 cburst_kbits;
  3: required i64 pir_kbps;
  4: required i64 pburst_kbits;
  5: required bool color_aware;
  6: optional bool is_set = 1;
}

enum main_lpf_type {
  TYPE_RATE = 0,
  TYPE_SAMPLE = 1
}

struct main_lpf_spec_t {
  1: required bool gain_decay_separate_time_constant;
  2: required double gain_time_constant;
  3: required double decay_time_constant;
  4: required double time_constant;
  5: required i32 output_scale_down_factor;
  6: required main_lpf_type lpf_type;
  7: optional bool is_set = 1;
}

struct main_wred_spec_t {
  1: required double time_constant;
  2: required i32 red_min_threshold;
  3: required i32 red_max_threshold;
  4: required double max_probability;
  5: optional bool is_set = 1;
}


enum main_idle_time_mode {
  POLL_MODE = 0,
  NOTIFY_MODE = 1,
  INVALID_MODE = 2
}

enum main_idle_time_hit_state {
  ENTRY_IDLE = 0,
  ENTRY_ACTIVE = 1
}

struct main_idle_time_params_t {
  1: required main_idle_time_mode mode;
  2: optional i32 ttl_query_interval;
  3: optional i32 max_ttl;
  4: optional i32 min_ttl;
  5: optional i32 cookie;
}

struct main_idle_tmo_expired_t {
  1: required i32 dev_id;
  2: required EntryHandle_t entry;
  3: required i32 cookie;
}

struct main_sel_update_t {
  1: required res.SessionHandle_t  sess_hdl;
  2: required res.DevTarget_t      dev_tgt;
  3: required i32                  cookie;
  4: required i32                  grp_hdl;
  5: required i32                  mbr_hdl;
  6: required i32                  index;
  7: required bool                 is_add;
}

enum main_grp_mbr_state {
  MBR_ACTIVE = 0,
  MBR_INACTIVE = 1
}


enum tbl_property_t
{
   TBL_PROP_TBL_ENTRY_SCOPE = 1,
   TBL_PROP_TERN_TABLE_ENTRY_PLACEMENT = 2,
   TBL_PROP_DUPLICATE_ENTRY_CHECK = 3,
   TBL_PROP_IDLETIME_REPEATED_NOTIFICATION = 4
}

enum tbl_property_value_t
{
   ENTRY_SCOPE_ALL_PIPELINES=0,
   ENTRY_SCOPE_SINGLE_PIPELINE=1,
   ENTRY_SCOPE_USER_DEFINED=2,
   TERN_ENTRY_PLACEMENT_DRV_MANAGED=0,
   TERN_ENTRY_PLACEMENT_APP_MANAGED=1,
   DUPLICATE_ENTRY_CHECK_DISABLE=0,
   DUPLICATE_ENTRY_CHECK_ENABLE=1,
   IDLETIME_REPEATED_NOTIFICATION_DISABLE = 0,
   IDLETIME_REPEATED_NOTIFICATION_ENABLE = 1
}

struct tbl_property_value_args_t
{
  1: required tbl_property_value_t value;
  2: required i32                  scope_args;
}

enum pvs_gress_t
{
   PVS_GRESS_INGRESS = 0,
   PVS_GRESS_EGRESS = 1,
   PVS_GRESS_ALL = 0xff
}

enum pvs_property_t {
  PVS_PROP_NONE = 0,
  PVS_GRESS_SCOPE,
  PVS_PIPE_SCOPE,
  PVS_PARSER_SCOPE
}

enum pvs_property_value_t {
  PVS_SCOPE_ALL_GRESS = 0,
  PVS_SCOPE_SINGLE_GRESS = 1,
  PVS_SCOPE_ALL_PIPELINES = 0,
  PVS_SCOPE_SINGLE_PIPELINE = 1,
  PVS_SCOPE_ALL_PARSERS = 0,
  PVS_SCOPE_SINGLE_PARSER = 1
}

enum tbl_dbg_counter_type_t {
  TBL_DBG_CNTR_DISABLED = 0,
  TBL_DBG_CNTR_LOG_TBL_MISS,
  TBL_DBG_CNTR_LOG_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_MISS,
  TBL_DBG_CNTR_GW_TBL_HIT,
  TBL_DBG_CNTR_GW_TBL_INHIBIT,
  TBL_DBG_CNTR_MAX
}

struct PVSSpec_t {
  1: required i32 parser_value;
  2: required i32 parser_value_mask;
}

struct TblCntrInfo_t {
  1: required tbl_dbg_counter_type_t type;
  2: required i32 value;
}

struct TblDbgStageInfo_t {
  1: required i32 num_counters;
  2: required list<string> tbl_name;
  3: required list<tbl_dbg_counter_type_t> type;
  4: required list<i32> value;
}

# not very space efficient but convenient
struct main_counter_flags_t {
  1: required bool read_hw_sync;
}

struct main_register_flags_t {
  1: required bool read_hw_sync;
}

struct main_snapshot_trig_spec_t {
  1: required string field_name;
  2: required i64 field_value;
  3: required i64 field_mask;
}

struct main_snapshot_tbl_data_t {
  1: required bool hit;
  2: required bool inhibited;
  3: required bool executed;
  4: required i32 hit_entry_handle;
}

enum main_input_fields__field_list_1_t {
  _FIELD_LIST_1_HDR_IP_TOTAL_LEN = 0,
}

enum main_input_field_attr_type_t {
  INPUT_FIELD_ATTR_TYPE_MASK,
  INPUT_FIELD_ATTR_TYPE_VALUE
}

enum main_input_field_attr_value_mask_t {
  INPUT_FIELD_EXCLUDED = 0,
  INPUT_FIELD_INCLUDED
}

enum main_Ingress_t_igr_identity_hasher0_configure_input_t {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_INPUT__FIELD_LIST_1,
}

union main_Ingress_t_igr_identity_hasher0_configure_input_fields_union_t {
  1: main_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union main_Ingress_t_igr_identity_hasher0_configure_input_field_attr_value_union_t {
  1: main_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required main_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum main_Ingress_t_igr_identity_hasher0_configure_algo_t {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER0_CONFIGURE_ALGORITHM_CRC_32,
}
enum main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1560_HASHER_1764_ALU_0_OPSTMT_CONFIGURE_INPUT__FIELD_LIST_1,
}

union main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_fields_union_t {
  1: main_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attr_value_union_t {
  1: main_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required main_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo_t {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1560_HASHER_1764_ALU_0_OPSTMT_CONFIGURE_ALGORITHM_CRC_10,
}
enum main_Ingress_t_igr_identity_hasher2_configure_input_t {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_INPUT__FIELD_LIST_1,
}

union main_Ingress_t_igr_identity_hasher2_configure_input_fields_union_t {
  1: main_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union main_Ingress_t_igr_identity_hasher2_configure_input_field_attr_value_union_t {
  1: main_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required main_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum main_Ingress_t_igr_identity_hasher2_configure_algo_t {
  P4_PD_MAIN_INGRESS_T_IGR_IDENTITY_HASHER2_CONFIGURE_ALGORITHM_CRC_32,
}
enum main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1562_HASHER_1766_ALU_0_OPSTMT_CONFIGURE_INPUT__FIELD_LIST_1,
}

union main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_fields_union_t {
  1: main_input_fields__field_list_1_t _field_list_1
  2: i32 id
}

union main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attr_value_union_t {
  1: main_input_field_attr_value_mask_t mask
  2: i64 attr_val
}

struct main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t {
  1: required i32 input_field;
  2: required main_input_field_attr_type_t type;
  3: i32 value;
  4: binary stream;
}

enum main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo_t {
  P4_PD_MAIN_EGRESS_T_EGR_DPT_1562_HASHER_1766_ALU_0_OPSTMT_CONFIGURE_ALGORITHM_CRC_10,
}


# Match structs

struct main_IngressParser__PORT_METADATA_match_spec_t {
  1: required i16 ig_intr_md_ingress_port;
}

struct main_Ingress_t_igr_tiForward_match_spec_t {
  1: required i16 md_ingress_port;
  2: required MacAddr_t hdr_ethernet_dst_addr;
}

struct main_Ingress_t_igr_tiRotateF_match_spec_t {
  1: required i16 hdr_pktgen_packet_id;
}

struct main_Ingress_t_igr_tiCalcF_match_spec_t {
  1: required i32 hdr_ip_src_addr;
  2: required i32 hdr_ip_dst_addr;
}

struct main_Ingress_t_igr_tiCalcSaturated_match_spec_t {
  1: required i16 ig_tm_md_ucast_egress_port;
}

struct main_Ingress_t_igr_tiReadLastSize_match_spec_t {
  1: required i16 f;
}

struct main_Ingress_t_igr_tiGetRates_tail_match_spec_t {
  1: required i16 f;
  2: required i32 tailq;
}

struct main_Ingress_t_igr_tiGetRates_head_match_spec_t {
  1: required i16 f;
  2: required i32 headq;
}

struct main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t {
  1: required i32 rate_tail;
  2: required i32 rate_tail_mask;
}

struct main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t {
  1: required i32 relative_round_m_dt;
  2: required i32 relative_round_m_dt_mask;
}

struct main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t {
  1: required i32 relative_round;
  2: required i32 relative_round_mask;
}

struct main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t {
  1: required i32 rate_head;
  2: required i32 rate_head_mask;
}

struct main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t {
  1: required byte log_relative_round_m_dt_x_rate_tail;
  2: required byte log_relative_round_m_dt_x_rate_tail_mask;
}

struct main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t {
  1: required i32 if_precomp1550;
  2: required i32 if_precomp1550_mask;
  3: required i32 if_precomp;
  4: required i32 if_precomp_mask;
  5: required i32 stored_dst;
  6: required i32 stored_dst_mask;
  7: required i32 stored_src;
  8: required i32 stored_src_mask;
}

struct main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t {
  1: required i32 if_precomp1550;
  2: required i32 if_precomp1550_mask;
  3: required i32 if_precomp;
  4: required i32 if_precomp_mask;
  5: required i32 stored_dst;
  6: required i32 stored_dst_mask;
  7: required i32 stored_src;
  8: required i32 stored_src_mask;
}

struct main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t {
  1: required i32 if_precomp1550;
  2: required i32 if_precomp1550_mask;
  3: required i32 if_precomp;
  4: required i32 if_precomp_mask;
  5: required i32 stored_dst;
  6: required i32 stored_dst_mask;
  7: required i32 stored_src;
  8: required i32 stored_src_mask;
}

struct main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t {
  1: required byte log_aggregate_size;
  2: required byte log_aggregate_size_mask;
}

struct main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t {
  1: required i32 if_precomp1550;
  2: required i32 if_precomp1550_mask;
  3: required i32 if_precomp;
  4: required i32 if_precomp_mask;
  5: required i32 stored_dst;
  6: required i32 stored_dst_mask;
  7: required i32 stored_src;
  8: required i32 stored_src_mask;
}

struct main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t {
  1: required i32 if_precomp1548;
  2: required i32 if_precomp1548_mask;
  3: required i32 if_precomp1547;
  4: required i32 if_precomp1547_mask;
  5: required i32 stored_dst2;
  6: required i32 stored_dst2_mask;
  7: required i32 stored_src2;
  8: required i32 stored_src2_mask;
  9: required i32 if_precomp1550;
  10: required i32 if_precomp1550_mask;
  11: required i32 if_precomp;
  12: required i32 if_precomp_mask;
  13: required i32 stored_dst;
  14: required i32 stored_dst_mask;
  15: required i32 stored_src;
  16: required i32 stored_src_mask;
}

struct main_Ingress_t_igr_tiSetQueue_match_spec_t {
  1: required i32 past_head;
  2: required i32 past_head_mask;
  3: required i32 past_tail;
  4: required i32 past_tail_mask;
}


# Match struct for Dynamic Key Mask Exm Table.


# Action structs

struct main_set_port_metadata_action_spec_t {
  1: required binary action_ig_intr_md;
}

struct main_Ingress_t_igr_aiSetEgress_action_spec_t {
  1: required i16 action_egr_port;
}

struct main_Ingress_t_igr_aiToggleCebinae_action_spec_t {
  1: required byte action_isOn;
}

struct main_Ingress_t_igr_aiRotateF_action_spec_t {
  1: required i16 action_fval;
}

struct main_Ingress_t_igr_aiReadLastSize_action_spec_t {
  1: required i32 action_lastRate_x_dT;
}

struct main_Ingress_t_igr_aiGetRates_tail_action_spec_t {
  1: required i32 action_r_tail;
  2: required i32 action_r_tail_x_dT;
}

struct main_Ingress_t_igr_aiGetRates_head_action_spec_t {
  1: required i32 action_r_head;
  2: required i32 action_r_head_x_dT;
}

struct main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t {
  1: required byte action_log_v;
}

struct main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t {
  1: required byte action_log_v;
}

struct main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t {
  1: required byte action_log_v;
}

struct main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t {
  1: required byte action_log_v;
}

union main_action_specs_t {
  1: main_set_port_metadata_action_spec_t main_set_port_metadata;
  2: main_Ingress_t_igr_aiSetEgress_action_spec_t main_Ingress_t_igr_aiSetEgress;
  3: main_Ingress_t_igr_aiToggleCebinae_action_spec_t main_Ingress_t_igr_aiToggleCebinae;
  4: main_Ingress_t_igr_aiRotateF_action_spec_t main_Ingress_t_igr_aiRotateF;
  5: main_Ingress_t_igr_aiReadLastSize_action_spec_t main_Ingress_t_igr_aiReadLastSize;
  6: main_Ingress_t_igr_aiGetRates_tail_action_spec_t main_Ingress_t_igr_aiGetRates_tail;
  7: main_Ingress_t_igr_aiGetRates_head_action_spec_t main_Ingress_t_igr_aiGetRates_head;
  8: main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t main_Ingress_t_igr_aiCalc_log_rate_tail;
  9: main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t main_Ingress_t_igr_aiCalc_log_relative_round_m_dt;
  10: main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t main_Ingress_t_igr_aiCalc_log_relative_round;
  11: main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t main_Ingress_t_igr_aiCalc_log_rate_head;
}

struct main_action_desc_t {
  1: required string name;
  2: required main_action_specs_t data;
}


# Register values

struct main_Ingress_t_igr_ri_bytes_value_t {
  1: required i32 f0;
  2: required i32 f1;
}


# Entry Descriptions

struct main_IngressParser__PORT_METADATA_entry_desc_t {
  1: required main_IngressParser__PORT_METADATA_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiForward_entry_desc_t {
  1: required main_Ingress_t_igr_tiForward_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiToggleCebinae_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiRotateF_entry_desc_t {
  1: required main_Ingress_t_igr_tiRotateF_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiRotateRoundTime_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalcF_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalcF_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalcSaturated_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiReadLastSize_entry_desc_t {
  1: required main_Ingress_t_igr_tiReadLastSize_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiDrop_rotate_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiRotateTailq_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_tbl_t_igr_aiGetTailq_st1_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiRotateHeadq_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_tbl_t_igr_aiGetHeadq_st1_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiGetRates_tail_entry_desc_t {
  1: required main_Ingress_t_igr_tiGetRates_tail_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiGetRates_head_entry_desc_t {
  1: required main_Ingress_t_igr_tiGetRates_head_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_2_merged_tbl_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalc_log_rate_tail_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalc_log_relative_round_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiCalc_log_rate_head_entry_desc_t {
  1: required main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_1_merged_tbl_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_4_merged_tbl_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_3_merged_tbl_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_entry_desc_t {
  1: required main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_5_merged_tbl_entry_desc_t {
  1: required bool has_mbr_hdl;
  2: required bool has_grp_hdl;
  3: required MemberHandle_t selector_grp_hdl;
  4: required MemberHandle_t action_mbr_hdl;
  5: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_7_merged_tbl_entry_desc_t {
  1: required main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_6_merged_tbl_entry_desc_t {
  1: required main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_8_merged_tbl_entry_desc_t {
  1: required main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiExp_aggregate_size_entry_desc_t {
  1: required main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_9_merged_tbl_entry_desc_t {
  1: required main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Egress_t_egr_dpt_10_merged_tbl_entry_desc_t {
  1: required main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}

struct main_Ingress_t_igr_tiSetQueue_entry_desc_t {
  1: required main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec;
  2: required bool has_mbr_hdl;
  3: required bool has_grp_hdl;
  4: required MemberHandle_t selector_grp_hdl;
  5: required MemberHandle_t action_mbr_hdl;
  6: required i32 priority;
  7: required main_action_desc_t action_desc;
}




exception InvalidTableOperation {
 1:i32 code
}

exception InvalidLearnOperation {
 1:i32 code
}

exception InvalidDbgOperation {
 1:i32 code
}

exception InvalidSnapshotOperation {
 1:i32 code
}

exception InvalidCounterOperation {
 1:i32 code
}

exception InvalidRegisterOperation {
 1:i32 code
}

exception InvalidMeterOperation {
 1:i32 code
}

exception InvalidLPFOperation {
 1:i32 code
}

exception InvalidWREDOperation {
 1:i32 code
}


service main {

    # Idle time config



    EntryHandle_t IngressParser__PORT_METADATA_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_IngressParser__PORT_METADATA_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcF_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcSaturated_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiReadLastSize_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiReadLastSize_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_tail_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_tail_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_head_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_head_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_match_spec_to_entry_hdl(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),


    # Dynamic Key Mask Exm Table.
      # set API

    # Table entry add functions

    EntryHandle_t IngressParser__PORT_METADATA_table_add_with_set_port_metadata(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_IngressParser__PORT_METADATA_match_spec_t match_spec, 4:main_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec, 4:main_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_table_add_with_Ingress_t_igr_aiRotateF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec, 4:main_Ingress_t_igr_aiRotateF_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFBottom(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiNotSaturated(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiReadLastSize_match_spec_t match_spec, 4:main_Ingress_t_igr_aiReadLastSize_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_tail_match_spec_t match_spec, 4:main_Ingress_t_igr_aiGetRates_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_head_match_spec_t match_spec, 4:main_Ingress_t_igr_aiGetRates_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_table_add_with_Ingress_t_igr_aiCalc_log_rate_tail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_add_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_table_add_with_Ingress_t_igr_aiCalc_log_relative_round(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_table_add_with_Ingress_t_igr_aiCalc_log_rate_head(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_add_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_table_add_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_table_add_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_0(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_4(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_5(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_6(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_7(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_8(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_9(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_10(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_11(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_12(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_13(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_14(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_15(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_16(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_17(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_18(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_19(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_20(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_21(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_22(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_23(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_24(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_25(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_26(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_27(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_28(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_29(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_30(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_add_with_Ingress_t_igr_aiExp_aggregate_size_31(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_table_add_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_table_add_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_table_add_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueHead(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiSetQueueTail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_table_add_with_Ingress_t_igr_aiDrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table entry modify functions
    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void IngressParser__PORT_METADATA_table_modify_with_set_port_metadata_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_IngressParser__PORT_METADATA_match_spec_t match_spec, 4:main_set_port_metadata_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiSetEgress_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec, 4:main_Ingress_t_igr_aiSetEgress_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_modify_with_Ingress_t_igr_aiNoop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRotateF_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRotateF_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiRotateF_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRotateF_table_modify_with_Ingress_t_igr_aiRotateF_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec, 4:main_Ingress_t_igr_aiRotateF_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFTop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcF_table_modify_with_Ingress_t_igr_aiSetFBottom_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiSaturated_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcSaturated_table_modify_with_Ingress_t_igr_aiNotSaturated_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiReadLastSize_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiReadLastSize_match_spec_t match_spec, 4:main_Ingress_t_igr_aiReadLastSize_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiGetRates_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_tail_match_spec_t match_spec, 4:main_Ingress_t_igr_aiGetRates_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiGetRates_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_head_match_spec_t match_spec, 4:main_Ingress_t_igr_aiGetRates_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_tail_table_modify_with_Ingress_t_igr_aiCalc_log_rate_tail_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_m_dt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_table_modify_with_Ingress_t_igr_aiCalc_log_relative_round_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry, 4:main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_head_table_modify_with_Ingress_t_igr_aiCalc_log_rate_head_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority, 5:main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_modify_with_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_modify_with_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_modify_with_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_0_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_1_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_2_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_3_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_4_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_5_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_6_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_7_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_8_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_9_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_10_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_11_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_12_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_13_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_14_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_15_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_16_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_17_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_18_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_19_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_20_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_21_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_22_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_23_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_24_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_25_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_26_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_27_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_28_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_29_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_30_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_modify_with_Ingress_t_igr_aiExp_aggregate_size_31_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_modify_with_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1635_merged_acn_6_noop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_modify_with_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_NoAction(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_NoAction_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueHead_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiSetQueueTail_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_modify_with_Ingress_t_igr_aiDrop_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table entry delete functions
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void IngressParser__PORT_METADATA_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_IngressParser__PORT_METADATA_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiForward_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiForward_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateF_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiRotateF_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiRotateF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcF_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcF_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcF_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcSaturated_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalcSaturated_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiReadLastSize_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiReadLastSize_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiReadLastSize_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_tail_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_tail_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_tail_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_head_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiGetRates_head_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiGetRates_head_match_spec_t match_spec) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_tail_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_tail_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_relative_round_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_relative_round_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_head_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiCalc_log_rate_head_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiCalc_log_rate_head_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_7_merged_tbl_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_7_merged_tbl_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_7_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_6_merged_tbl_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_6_merged_tbl_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_6_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_8_merged_tbl_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_8_merged_tbl_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_8_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_aggregate_size_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiExp_aggregate_size_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiExp_aggregate_size_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_9_merged_tbl_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_9_merged_tbl_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_9_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_10_merged_tbl_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Egress_t_egr_dpt_10_merged_tbl_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Egress_t_egr_dpt_10_merged_tbl_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiSetQueue_table_delete(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry) throws (1:InvalidTableOperation ouch),
    void Ingress_t_igr_tiSetQueue_table_delete_by_match_spec(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_tiSetQueue_match_spec_t match_spec, 4:i32 priority) throws (1:InvalidTableOperation ouch),

    # Table default entry get functions
    EntryHandle_t IngressParser__PORT_METADATA_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_IngressParser__PORT_METADATA_entry_desc_t IngressParser__PORT_METADATA_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiForward_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiForward_entry_desc_t Ingress_t_igr_tiForward_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiToggleCebinae_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiToggleCebinae_entry_desc_t Ingress_t_igr_tiToggleCebinae_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiRotateF_entry_desc_t Ingress_t_igr_tiRotateF_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateRoundTime_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiRotateRoundTime_entry_desc_t Ingress_t_igr_tiRotateRoundTime_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcF_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalcF_entry_desc_t Ingress_t_igr_tiCalcF_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcSaturated_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalcSaturated_entry_desc_t Ingress_t_igr_tiCalcSaturated_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiReadLastSize_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiReadLastSize_entry_desc_t Ingress_t_igr_tiReadLastSize_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiDrop_rotate_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiDrop_rotate_entry_desc_t Ingress_t_igr_tiDrop_rotate_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateTailq_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiRotateTailq_entry_desc_t Ingress_t_igr_tiRotateTailq_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t tbl_t_igr_aiGetTailq_st1_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_tbl_t_igr_aiGetTailq_st1_entry_desc_t tbl_t_igr_aiGetTailq_st1_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateHeadq_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiRotateHeadq_entry_desc_t Ingress_t_igr_tiRotateHeadq_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t tbl_t_igr_aiGetHeadq_st1_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_tbl_t_igr_aiGetHeadq_st1_entry_desc_t tbl_t_igr_aiGetHeadq_st1_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_tail_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiGetRates_tail_entry_desc_t Ingress_t_igr_tiGetRates_tail_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_head_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiGetRates_head_entry_desc_t Ingress_t_igr_tiGetRates_head_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_2_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_2_merged_tbl_entry_desc_t Egress_t_egr_dpt_2_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalc_log_rate_tail_entry_desc_t Ingress_t_igr_tiCalc_log_rate_tail_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_entry_desc_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalc_log_relative_round_entry_desc_t Ingress_t_igr_tiCalc_log_relative_round_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiCalc_log_rate_head_entry_desc_t Ingress_t_igr_tiCalc_log_rate_head_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_1_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_1_merged_tbl_entry_desc_t Egress_t_egr_dpt_1_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_4_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_4_merged_tbl_entry_desc_t Egress_t_egr_dpt_4_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_3_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_3_merged_tbl_entry_desc_t Egress_t_egr_dpt_3_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_entry_desc_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_5_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_5_merged_tbl_entry_desc_t Egress_t_egr_dpt_5_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_7_merged_tbl_entry_desc_t Egress_t_egr_dpt_7_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_6_merged_tbl_entry_desc_t Egress_t_egr_dpt_6_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_8_merged_tbl_entry_desc_t Egress_t_egr_dpt_8_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiExp_aggregate_size_entry_desc_t Ingress_t_igr_tiExp_aggregate_size_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_9_merged_tbl_entry_desc_t Egress_t_egr_dpt_9_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Egress_t_egr_dpt_10_merged_tbl_entry_desc_t Egress_t_egr_dpt_10_merged_tbl_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_table_get_default_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    main_Ingress_t_igr_tiSetQueue_entry_desc_t Ingress_t_igr_tiSetQueue_table_get_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    # Table default entry clear functions
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiToggleCebinae_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateF_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateRoundTime_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcF_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcSaturated_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiReadLastSize_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiDrop_rotate_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateTailq_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void tbl_t_igr_aiGetTailq_st1_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateHeadq_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void tbl_t_igr_aiGetHeadq_st1_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_tail_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_head_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_2_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_tail_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_head_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_1_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_4_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_3_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_5_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_7_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_6_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_8_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_aggregate_size_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_9_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_10_merged_tbl_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiSetQueue_table_reset_default_entry(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    i32 IngressParser__PORT_METADATA_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiForward_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiToggleCebinae_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRotateF_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRotateRoundTime_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalcF_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalcSaturated_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiReadLastSize_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiDrop_rotate_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRotateTailq_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 tbl_t_igr_aiGetTailq_st1_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiRotateHeadq_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 tbl_t_igr_aiGetHeadq_st1_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiGetRates_tail_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiGetRates_head_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_2_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalc_log_rate_tail_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalc_log_relative_round_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiCalc_log_rate_head_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_1_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_4_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_3_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_5_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_7_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_6_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_8_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiExp_aggregate_size_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_9_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Egress_t_egr_dpt_10_merged_tbl_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    i32 Ingress_t_igr_tiSetQueue_get_entry_count(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),


    # Get first entry handle functions
    EntryHandle_t IngressParser__PORT_METADATA_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> IngressParser__PORT_METADATA_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_IngressParser__PORT_METADATA_entry_desc_t IngressParser__PORT_METADATA_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiForward_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiForward_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiForward_entry_desc_t Ingress_t_igr_tiForward_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiToggleCebinae_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiToggleCebinae_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiToggleCebinae_entry_desc_t Ingress_t_igr_tiToggleCebinae_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRotateF_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRotateF_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiRotateF_entry_desc_t Ingress_t_igr_tiRotateF_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRotateRoundTime_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRotateRoundTime_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiRotateRoundTime_entry_desc_t Ingress_t_igr_tiRotateRoundTime_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalcF_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalcF_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalcF_entry_desc_t Ingress_t_igr_tiCalcF_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalcSaturated_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalcSaturated_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalcSaturated_entry_desc_t Ingress_t_igr_tiCalcSaturated_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiReadLastSize_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiReadLastSize_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiReadLastSize_entry_desc_t Ingress_t_igr_tiReadLastSize_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiDrop_rotate_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiDrop_rotate_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiDrop_rotate_entry_desc_t Ingress_t_igr_tiDrop_rotate_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRotateTailq_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRotateTailq_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiRotateTailq_entry_desc_t Ingress_t_igr_tiRotateTailq_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t tbl_t_igr_aiGetTailq_st1_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> tbl_t_igr_aiGetTailq_st1_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_tbl_t_igr_aiGetTailq_st1_entry_desc_t tbl_t_igr_aiGetTailq_st1_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiRotateHeadq_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiRotateHeadq_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiRotateHeadq_entry_desc_t Ingress_t_igr_tiRotateHeadq_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t tbl_t_igr_aiGetHeadq_st1_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> tbl_t_igr_aiGetHeadq_st1_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_tbl_t_igr_aiGetHeadq_st1_entry_desc_t tbl_t_igr_aiGetHeadq_st1_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiGetRates_tail_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiGetRates_tail_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiGetRates_tail_entry_desc_t Ingress_t_igr_tiGetRates_tail_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiGetRates_head_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiGetRates_head_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiGetRates_head_entry_desc_t Ingress_t_igr_tiGetRates_head_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_2_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_2_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_2_merged_tbl_entry_desc_t Egress_t_egr_dpt_2_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalc_log_rate_tail_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalc_log_rate_tail_entry_desc_t Ingress_t_igr_tiCalc_log_rate_tail_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalc_log_relative_round_m_dt_entry_desc_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalc_log_relative_round_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalc_log_relative_round_entry_desc_t Ingress_t_igr_tiCalc_log_relative_round_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiCalc_log_rate_head_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiCalc_log_rate_head_entry_desc_t Ingress_t_igr_tiCalc_log_rate_head_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_1_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_1_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_1_merged_tbl_entry_desc_t Egress_t_egr_dpt_1_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_4_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_4_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_4_merged_tbl_entry_desc_t Egress_t_egr_dpt_4_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_3_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_3_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_3_merged_tbl_entry_desc_t Egress_t_egr_dpt_3_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_entry_desc_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_5_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_5_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_5_merged_tbl_entry_desc_t Egress_t_egr_dpt_5_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_7_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_7_merged_tbl_entry_desc_t Egress_t_egr_dpt_7_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_6_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_6_merged_tbl_entry_desc_t Egress_t_egr_dpt_6_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_8_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_8_merged_tbl_entry_desc_t Egress_t_egr_dpt_8_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiExp_aggregate_size_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiExp_aggregate_size_entry_desc_t Ingress_t_igr_tiExp_aggregate_size_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_9_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_9_merged_tbl_entry_desc_t Egress_t_egr_dpt_9_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Egress_t_egr_dpt_10_merged_tbl_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Egress_t_egr_dpt_10_merged_tbl_entry_desc_t Egress_t_egr_dpt_10_merged_tbl_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),

    EntryHandle_t Ingress_t_igr_tiSetQueue_get_first_entry_handle(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    list<EntryHandle_t> Ingress_t_igr_tiSetQueue_get_next_entry_handles(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:EntryHandle_t entry_hdl, 4:i32 n) throws (1:InvalidTableOperation ouch),

    main_Ingress_t_igr_tiSetQueue_entry_desc_t Ingress_t_igr_tiSetQueue_get_entry(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:EntryHandle_t entry_hdl, 4:bool read_from_hw) throws (1:InvalidTableOperation ouch),



    # Table set default action functions

    EntryHandle_t Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiNoop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiToggleCebinae_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiToggleCebinae_set_default_action_Ingress_t_igr_aiToggleCebinae(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiToggleCebinae_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateF_set_default_action_Ingress_t_igr_aiRotateF(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiRotateF_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateRoundTime_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateRoundTime_set_default_action_Ingress_t_igr_aiRotateRoundTime(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcF_set_default_action_Ingress_t_igr_aiSetFBottom(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalcSaturated_set_default_action_Ingress_t_igr_aiNotSaturated(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiReadLastSize_set_default_action_Ingress_t_igr_aiReadLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiReadLastSize_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiDrop_rotate_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiDrop_rotate_set_default_action_Ingress_t_igr_aiDrop_rotate(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateTailq_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateTailq_set_default_action_Ingress_t_igr_aiRotateTailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t tbl_t_igr_aiGetTailq_st1_set_default_action_Ingress_t_igr_aiGetTailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateHeadq_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiRotateHeadq_set_default_action_Ingress_t_igr_aiRotateHeadq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t tbl_t_igr_aiGetHeadq_st1_set_default_action_Ingress_t_igr_aiGetHeadq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_tail_set_default_action_Ingress_t_igr_aiGetRates_tail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiGetRates_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiGetRates_head_set_default_action_Ingress_t_igr_aiGetRates_head(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiGetRates_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_2_merged_tbl_set_default_action_Egress_t_egr_dpt_1562_merged_acn_2_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_tail_set_default_action_Ingress_t_igr_aiCalc_log_rate_tail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiCalc_log_rate_tail_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_default_action_Ingress_t_igr_aiCalc_log_relative_round_m_dt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiCalc_log_relative_round_m_dt_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_relative_round_set_default_action_Ingress_t_igr_aiCalc_log_relative_round(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiCalc_log_relative_round_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiCalc_log_rate_head_set_default_action_Ingress_t_igr_aiCalc_log_rate_head(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_aiCalc_log_rate_head_action_spec_t action_spec) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_1_merged_tbl_set_default_action_Egress_t_egr_dpt_1559_merged_acn_1_acn_0_opstmt_1560_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_4_merged_tbl_set_default_action_Egress_t_egr_dpt_1564_merged_acn_4_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_3_merged_tbl_set_default_action_Egress_t_egr_dpt_1566_merged_acn_3_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_0(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_4(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_5(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_6(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_7(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_8(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_9(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_10(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_11(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_12(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_13(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_14(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_15(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_16(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_17(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_18(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_19(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_20(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_21(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_22(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_23(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_24(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_25(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_26(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_27(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_28(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_29(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_30(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_default_action_Ingress_t_igr_aiExp_relative_round_m_dt_x_rate_tail_31(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_5_merged_tbl_set_default_action_Egress_t_egr_dpt_1568_merged_acn_5_acn_0_opstmt_1570_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_7_merged_tbl_set_default_action_Egress_t_egr_dpt_1577_merged_acn_7_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_6_merged_tbl_set_default_action_Egress_t_egr_dpt_1581_merged_acn_6_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1576_merged_acn_8_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_8_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_0(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_3(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_4(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_5(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_6(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_7(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_8(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_9(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_10(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_11(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_12(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_13(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_14(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_15(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_16(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_17(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_18(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_19(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_20(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_21(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_22(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_23(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_24(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_25(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_26(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_27(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_28(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_29(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_30(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiExp_aggregate_size_set_default_action_Ingress_t_igr_aiExp_aggregate_size_31(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_9_merged_tbl_set_default_action_Egress_t_egr_dpt_1584_merged_acn_9_acn_0_opstmt_1586_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1635_merged_acn_6_noop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Egress_t_egr_dpt_10_merged_tbl_set_default_action_Egress_t_egr_dpt_1592_merged_acn_10_acn_0_opstmt(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_set_default_action_NoAction(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueHead(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiSetQueueTail(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),
    EntryHandle_t Ingress_t_igr_tiSetQueue_set_default_action_Ingress_t_igr_aiDrop(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidTableOperation ouch),

    
     # Table set/get property
# //::   if action_table_hdl: continue
    void IngressParser__PORT_METADATA_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t IngressParser__PORT_METADATA_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiForward_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiForward_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiToggleCebinae_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiToggleCebinae_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateF_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRotateF_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateRoundTime_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRotateRoundTime_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcF_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalcF_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalcSaturated_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalcSaturated_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiReadLastSize_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiReadLastSize_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiDrop_rotate_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiDrop_rotate_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateTailq_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRotateTailq_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void tbl_t_igr_aiGetTailq_st1_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t tbl_t_igr_aiGetTailq_st1_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiRotateHeadq_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiRotateHeadq_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void tbl_t_igr_aiGetHeadq_st1_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t tbl_t_igr_aiGetHeadq_st1_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_tail_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiGetRates_tail_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiGetRates_head_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiGetRates_head_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_2_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_2_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_tail_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalc_log_rate_tail_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_m_dt_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalc_log_relative_round_m_dt_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_relative_round_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalc_log_relative_round_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiCalc_log_rate_head_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiCalc_log_rate_head_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_1_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_1_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_4_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_4_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_3_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_3_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiExp_relative_round_m_dt_x_rate_tail_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_5_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_5_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_7_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_7_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_6_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_6_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_8_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_8_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiExp_aggregate_size_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiExp_aggregate_size_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_9_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_9_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Egress_t_egr_dpt_10_merged_tbl_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Egress_t_egr_dpt_10_merged_tbl_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),
# //::   if action_table_hdl: continue
    void Ingress_t_igr_tiSetQueue_set_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property, 4:tbl_property_value_t value, 5:i32 prop_args) throws (1:InvalidTableOperation ouch),

    tbl_property_value_args_t Ingress_t_igr_tiSetQueue_get_property(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:tbl_property_t property) throws (1:InvalidTableOperation ouch),

    # INDIRECT ACTION DATA AND MATCH SELECT






    void set_learning_timeout(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 usecs) throws (1:InvalidLearnOperation ouch),

    void tbl_dbg_counter_type_set(1:res.DevTarget_t dev_tgt, 2:string tbl_name, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblCntrInfo_t tbl_dbg_counter_get(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_clear(1:res.DevTarget_t dev_tgt, 2:string tbl_name) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_type_stage_set(1:res.DevTarget_t dev_tgt, 2:byte stage, 3:tbl_dbg_counter_type_t type) throws (1:InvalidDbgOperation ouch),

    TblDbgStageInfo_t tbl_dbg_counter_stage_get(1:res.DevTarget_t dev_tgt, 2:byte stage) throws (1:InvalidDbgOperation ouch),

    void tbl_dbg_counter_stage_clear(1:res.DevTarget_t dev_tgt, 2: byte stage) throws (1:InvalidDbgOperation ouch),

    SnapshotHandle_t snapshot_create(1:res.DevTarget_t dev_tgt, 2:byte start_stage, 3:byte end_stage, 4:byte direction) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_delete(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_state_set(1: SnapshotHandle_t handle, 2:i32 state, 3:i32 usecs) throws (1:InvalidSnapshotOperation ouch),

    i32 snapshot_state_get(1:SnapshotHandle_t handle, 2:i16 pipe) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_timer_enable(1: SnapshotHandle_t handle, 2:byte disable) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_set(1: SnapshotHandle_t handle,
                2:main_snapshot_trig_spec_t trig_spec,
                3:main_snapshot_trig_spec_t trig_spec2) throws (1:InvalidSnapshotOperation ouch),

    i64 snapshot_capture_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:i16 stage_id, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    main_snapshot_tbl_data_t snapshot_capture_tbl_data_get(1: SnapshotHandle_t handle, 2:i16 pipe, 3:string table_name) throws (1:InvalidSnapshotOperation ouch),

    void snapshot_capture_trigger_fields_clr(1:SnapshotHandle_t handle) throws (1:InvalidSnapshotOperation ouch),

    bool snapshot_field_in_scope(1:res.DevTarget_t dev_tgt, 2:byte stage,
                 3:byte direction, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    bool snapshot_trigger_field_in_scope(1:res.DevTarget_t dev_tgt, 2:byte stage,
                 3:byte direction, 4:string field_name) throws (1:InvalidSnapshotOperation ouch),

    # counters



    # registers

    void register_hw_sync_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_headq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_ct2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_riBytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<main_Ingress_t_igr_ri_bytes_value_t> register_read_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_Ingress_t_igr_ri_bytes_value_t register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:main_Ingress_t_igr_ri_bytes_value_t register_value) throws (1:InvalidRegisterOperation ouch),
    list<main_Ingress_t_igr_ri_bytes_value_t> register_range_read_Ingress_t_igr_ri_bytes(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_ct1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_fCount(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_queueCounter(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_base_round_time(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_port_cts(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_src1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_riRotateLastSize(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_src2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_dst1(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Ingress_t_igr_ri_tailq(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_hw_sync_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_read_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),
    void register_write_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    void register_reset_all_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt) throws (1:InvalidRegisterOperation ouch),
    void register_range_reset_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt 3:i32 index 4:i32 count) throws (1:InvalidRegisterOperation ouch),
    void register_write_all_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 register_value) throws (1:InvalidRegisterOperation ouch),
    list<i32> register_range_read_Egress_t_egr_flow_dst2(1:res.SessionHandle_t sess_hdl, 2:res.DevTarget_t dev_tgt, 3:i32 index, 4:i32 count, 5:main_register_flags_t flags) throws (1:InvalidRegisterOperation ouch),








    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher0_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_identity_hasher0_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher0_configure_input_t input, 4:list<main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher0_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_identity_hasher0_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<main_Ingress_t_igr_identity_hasher0_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input, 4:list<main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t> hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<main_Egress_t_egr_dpt_1560_hasher_1764_alu_0_opstmt_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher2_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Ingress_t_igr_identity_hasher2_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher2_configure_input_t input, 4:list<main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> hash_calc_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Ingress_t_igr_identity_hasher2_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Ingress_t_igr_identity_hasher2_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<main_Ingress_t_igr_identity_hasher2_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


    void hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algorithm_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algo_t algo) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_algorithm_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_seed_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i64 seed) throws (1:InvalidTableOperation ouch),

    i64 hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_seed_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id) throws (1:InvalidTableOperation ouch),

    void hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_set(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input, 4:list<main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t> array_of_attrs) throws (1:InvalidTableOperation ouch),

    i32 hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_count_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t> hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_get(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_t input) throws (1:InvalidTableOperation ouch),

    list<byte> hash_calc_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_calculate_hash_value(1:res.SessionHandle_t sess_hdl, 2:byte dev_id, 3:i32 attr_count, 4:list<main_Egress_t_egr_dpt_1562_hasher_1766_alu_0_opstmt_configure_input_field_attribute_t> array_of_attrs, 5:list<i32> attr_sizes) throws (1:InvalidTableOperation ouch),


} 
