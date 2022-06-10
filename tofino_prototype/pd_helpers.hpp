typedef struct p4_pd_main_Ingress_t_igr_tiCalcF_match_spec {
  uint32_t hdr_ip_src_addr;
  uint32_t hdr_ip_dst_addr;
} p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec {
  uint16_t f;
  uint32_t headq;
} p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec {
  uint32_t action_r_head;
  uint32_t action_r_head_x_dT;
} p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec {
  uint16_t f;
  uint32_t tailq;
} p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec {
  uint32_t action_r_tail;
  uint32_t action_r_tail_x_dT;
} p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec {
  uint16_t f;
} p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec {
  uint32_t action_lastRate_x_dT;
} p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t;
typedef struct p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec {
  uint16_t ig_tm_md_ucast_egress_port;
} p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t;

static inline void build_key_Ingress_t_igr_tiCalcSaturated
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->ig_tm_md_ucast_egress_port);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->ig_tm_md_ucast_egress_port) + 0, 2);
#endif
  match_bits += 2;

}

static inline void build_match_spec_Ingress_t_igr_tiCalcSaturated
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;
  pipe_match_spec->match_field_validity = 0;
  pipe_match_spec->match_field_validity_mask = 0;
  pipe_match_spec->num_match_validity_fields = 0;

  build_key_Ingress_t_igr_tiCalcSaturated(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_Ingress_t_igr_tiCalcSaturated(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777232, &pipe_match_spec,
					       536870934, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiNotSaturated
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_Ingress_t_igr_tiCalcSaturated(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777232, &pipe_match_spec,
					       536870935, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 9;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_Ingress_t_igr_tiCalcSaturated(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777232,
            &pipe_match_spec,
            0);
}

static inline void build_key_Ingress_t_igr_tiReadLastSize
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->f);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->f) + 0, 2);
#endif
  match_bits += 2;

}

static inline void build_match_spec_Ingress_t_igr_tiReadLastSize
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;
  pipe_match_spec->match_field_validity = 0;
  pipe_match_spec->match_field_validity_mask = 0;
  pipe_match_spec->num_match_validity_fields = 0;

  build_key_Ingress_t_igr_tiReadLastSize(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_action_spec_Ingress_t_igr_aiReadLastSize
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_lastRate_x_dT);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_lastRate_x_dT) + 0, 4);
#endif

  data_bits += 4;

}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[2];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[2];
  if (2) {
    memset(pipe_match_value_bits, 0, 2);
    memset(pipe_match_mask_bits, 0, 2);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 16;
  pipe_match_spec.num_match_bytes = 2;
  build_match_spec_Ingress_t_igr_tiReadLastSize(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiReadLastSize(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777226, &pipe_match_spec,
					       536870921, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[4];
  memset(pipe_action_data_bits, 0, 4);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 32;
  pipe_action_data_spec->num_action_data_bytes = 4;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiReadLastSize(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777226,
             entry_hdl,
             536870921,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

static inline void build_key_Ingress_t_igr_tiCalcF
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->hdr_ip_src_addr);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->hdr_ip_src_addr) + 0, 4);
#endif
  match_bits += 4;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->hdr_ip_dst_addr);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->hdr_ip_dst_addr) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_match_spec_Ingress_t_igr_tiCalcF
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;
  pipe_match_spec->match_field_validity = 0;
  pipe_match_spec->match_field_validity_mask = 0;
  pipe_match_spec->num_match_validity_fields = 0;

  build_key_Ingress_t_igr_tiCalcF(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[8];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[8];
  if (8) {
    memset(pipe_match_value_bits, 0, 8);
    memset(pipe_match_mask_bits, 0, 8);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 64;
  pipe_match_spec.num_match_bytes = 8;
  build_match_spec_Ingress_t_igr_tiCalcF(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[0];
  memset(pipe_action_data_bits, 0, 0);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 0;
  pipe_action_data_spec->num_action_data_bytes = 0;
  pipe_action_spec.resource_count = 0;


  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;

  {
    pipe_res_spec_t *res_spec = &pipe_action_spec.resources[pipe_action_spec.resource_count++];
    res_spec->tbl_hdl = 100663299;
    res_spec->tbl_idx = 0;
    res_spec->tag = PIPE_RES_ACTION_TAG_ATTACHED;
  }


  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777231, &pipe_match_spec,
					       536870932, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_delete
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl
)
{
  return pipe_mgr_mat_ent_del(sess_hdl,
            dev_id,
            16777231,
            entry_hdl,
            0 /* TODO */);
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiCalcF_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiCalcF_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[8];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[8];
  if (8) {
    memset(pipe_match_value_bits, 0, 8);
    memset(pipe_match_mask_bits, 0, 8);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 64;
  pipe_match_spec.num_match_bytes = 8;
  build_match_spec_Ingress_t_igr_tiCalcF(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777231,
            &pipe_match_spec,
            0);
}

static inline void build_key_Ingress_t_igr_tiGetRates_head
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->f);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->f) + 0, 2);
#endif
  match_bits += 2;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->headq);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->headq) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_match_spec_Ingress_t_igr_tiGetRates_head
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;
  pipe_match_spec->match_field_validity = 0;
  pipe_match_spec->match_field_validity_mask = 0;
  pipe_match_spec->num_match_validity_fields = 0;

  build_key_Ingress_t_igr_tiGetRates_head(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_action_spec_Ingress_t_igr_aiGetRates_head
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_r_head);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_r_head) + 0, 4);
#endif

  data_bits += 4;
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_r_head_x_dT);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_r_head_x_dT) + 0, 4);
#endif

  data_bits += 4;

}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_head(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiGetRates_head(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777237, &pipe_match_spec,
					       536870939, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiGetRates_head(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777237,
             entry_hdl,
             536870939,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_head(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiGetRates_head(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777237,
             &pipe_match_spec,
             536870939,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_head(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777237,
            &pipe_match_spec,
            0);
}

static inline void build_key_Ingress_t_igr_tiGetRates_tail
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec
)
{
  uint8_t *match_bits = pipe_match_spec->match_value_bits;
  (void) match_bits;
#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif


#ifdef LITTLE_ENDIAN_CALLER
  tmp16 = htons(match_spec->f);
  memcpy(match_bits, &tmp16, 2);
#else
  memcpy(match_bits, ((char *) &match_spec->f) + 0, 2);
#endif
  match_bits += 2;


#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(match_spec->tailq);
  memcpy(match_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(match_bits, ((char *) &match_spec->tailq) + 0, 4);
#endif
  match_bits += 4;

}

static inline void build_match_spec_Ingress_t_igr_tiGetRates_tail
(
 pipe_tbl_match_spec_t *pipe_match_spec,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec
)
{
  pipe_match_spec->partition_index = 0;
  pipe_match_spec->match_field_validity = 0;
  pipe_match_spec->match_field_validity_mask = 0;
  pipe_match_spec->num_match_validity_fields = 0;

  build_key_Ingress_t_igr_tiGetRates_tail(pipe_match_spec, match_spec);

  if (pipe_match_spec->num_match_bytes > 0) {
  /* we start by setting the mask entirely to 1s */
    memset(pipe_match_spec->match_mask_bits, 0xFF, pipe_match_spec->num_match_bytes);
  }

  pipe_match_spec->priority = 0;
  /* exact match: nothing to do with the mask */
}

static inline void build_action_spec_Ingress_t_igr_aiGetRates_tail
(
 pipe_action_data_spec_t *pipe_action_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec
)
{
  uint8_t *data_bits = pipe_action_spec->action_data_bits;
  (void) data_bits;

#ifdef LITTLE_ENDIAN_CALLER
  uint16_t tmp16;
  uint32_t tmp32;
  (void) tmp16;
  (void) tmp32;
#endif
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_r_tail);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_r_tail) + 0, 4);
#endif

  data_bits += 4;
#ifdef LITTLE_ENDIAN_CALLER
  tmp32 = htonl(action_spec->action_r_tail_x_dT);
  memcpy(data_bits, ((char *) &tmp32) + 0, 4);
#else
  memcpy(data_bits, ((char *) &action_spec->action_r_tail_x_dT) + 0, 4);
#endif

  data_bits += 4;

}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec,
 p4_pd_entry_hdl_t *entry_hdl
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_tail(&pipe_match_spec, match_spec);

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;

  build_action_spec_Ingress_t_igr_aiGetRates_tail(pipe_action_data_spec, action_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t ttl = 0;



  p4_pd_status_t status = pipe_mgr_mat_ent_add(sess_hdl, pipe_mgr_dev_tgt,
					       16777235, &pipe_match_spec,
					       536870940, &pipe_action_spec,
					       ttl,
					       0 /* TODO */,
					       entry_hdl);
  return status;
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail
(
 p4_pd_sess_hdl_t sess_hdl,
 bf_dev_id_t dev_id,
 p4_pd_entry_hdl_t entry_hdl,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec
)
{

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiGetRates_tail(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action(sess_hdl,
             dev_id,
             16777235,
             entry_hdl,
             536870940,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec,
 const p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec_t * const action_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_tail(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint8_t pipe_action_data_bits[8];
  memset(pipe_action_data_bits, 0, 8);
  pipe_action_spec_t pipe_action_spec = {0};
  pipe_action_spec.pipe_action_datatype_bmap = PIPE_ACTION_DATA_TYPE;
  pipe_action_data_spec_t *pipe_action_data_spec = &pipe_action_spec.act_data;
  pipe_action_data_spec->action_data_bits = pipe_action_data_bits;
  pipe_action_data_spec->num_valid_action_data_bits = 64;
  pipe_action_data_spec->num_action_data_bytes = 8;
  pipe_action_spec.resource_count = 0;
  build_action_spec_Ingress_t_igr_aiGetRates_tail(pipe_action_data_spec, action_spec);

  return pipe_mgr_mat_ent_set_action_by_match_spec(sess_hdl,
             pipe_mgr_dev_tgt,
             16777235,
             &pipe_match_spec,
             536870940,
             &pipe_action_spec,
             0 /* flags, TODO */);
}

p4_pd_status_t
p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete_by_match_spec
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 const p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec_t * const match_spec
)
{
  pipe_tbl_match_spec_t pipe_match_spec = {0};
  uint8_t pipe_match_value_bits[6];
  pipe_match_spec.match_value_bits = pipe_match_value_bits;
  uint8_t pipe_match_mask_bits[6];
  if (6) {
    memset(pipe_match_value_bits, 0, 6);
    memset(pipe_match_mask_bits, 0, 6);
  }
  pipe_match_spec.match_mask_bits = pipe_match_mask_bits;
  pipe_match_spec.num_valid_match_bits = 48;
  pipe_match_spec.num_match_bytes = 6;
  build_match_spec_Ingress_t_igr_tiGetRates_tail(&pipe_match_spec, match_spec);

  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_mgr_mat_ent_del_by_match_spec(sess_hdl,
            pipe_mgr_dev_tgt,
            16777235,
            &pipe_match_spec,
            0);
}






static void register_Ingress_t_igr_ri_headq_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_headq_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}

static void register_Ingress_t_igr_ri_tailq_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Ingress_t_igr_ri_tailq_value_pd_to_pipe(
    uint32_t *register_value,
    pipe_stful_mem_spec_t *stful_spec) {
  stful_spec->word = *register_value;
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663298,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663298, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_headq_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_headq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_headq_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663298, index,
					     &stful_spec, 0);
  return status;
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663300,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663300, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_ri_tailq_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_write_Ingress_t_igr_ri_tailq
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 uint32_t *register_value
)
{
  pipe_stful_mem_spec_t stful_spec;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;
  register_Ingress_t_igr_ri_tailq_value_pd_to_pipe(register_value, &stful_spec);

  p4_pd_status_t status = pipe_stful_ent_set(sess_hdl, pipe_mgr_dev_tgt,
					     100663300, index,
					     &stful_spec, 0);
  return status;
}

static void register_Egress_t_egr_port_cts_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}
p4_pd_status_t
p4_pd_main_register_read_Egress_t_egr_port_cts
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663305,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663305, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Egress_t_egr_port_cts_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

static void register_Egress_t_egr_flow_src1_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Egress_t_egr_flow_dst1_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Egress_t_egr_flow_ct1_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663306,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663306, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_src1_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663307,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663307, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_dst1_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663310,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663310, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_ct1_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_src1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663306,
                                NULL);
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_dst1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663307,
                                NULL);
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_ct1
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663310,
                                NULL);
}

static void register_Egress_t_egr_flow_src2_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Egress_t_egr_flow_dst2_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

static void register_Egress_t_egr_flow_ct2_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663308,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663308, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_src2_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663309,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663309, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_dst2_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_range_read_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int count,
 int flags,
 uint32_t *num_actually_read,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663311,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t *stful_query = (  pipe_stful_mem_query_t*)bf_sys_calloc(count, sizeof *stful_query);
  pipe_stful_mem_spec_t *pipe_data = (  pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count * count, sizeof *pipe_data);
  if (!stful_query || !pipe_data) {
    status = PIPE_NO_SYS_RESOURCES;
    goto free_query_data;
  }

  for (int j=0; j<count; ++j) {
    stful_query[j].pipe_count = pipe_count;
    stful_query[j].data = pipe_data + (pipe_count * j);
  }

  /* Perform the query. */
  status = pipe_stful_ent_query_range(sess_hdl, pipe_mgr_dev_tgt,
                                      100663311, index, count,
                                      stful_query, num_actually_read,
                                      pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;

  /* Convert the query data to PD format. */
  *value_count = 0;
  for (int i=0; i<*num_actually_read; ++i) {
    register_Egress_t_egr_flow_ct2_value_pipe_to_pd(stful_query+i, register_values, value_count);
    register_values += stful_query[i].pipe_count;
  }

free_query_data:
  if (stful_query) bf_sys_free(stful_query);
  if (pipe_data) bf_sys_free(pipe_data);
  return status;
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_src2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663308,
                                NULL);
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_dst2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663309,
                                NULL);
}

p4_pd_status_t
p4_pd_main_register_reset_all_Egress_t_egr_flow_ct2
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt
)
{
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  return pipe_stful_table_reset(sess_hdl, pipe_mgr_dev_tgt, 100663311,
                                NULL);
}

static void register_Ingress_t_igr_queueCounter_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_queueCounter
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663304,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663304, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_queueCounter_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

static void register_Ingress_t_igr_fCount_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_fCount
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663299,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663299, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_fCount_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

static void register_Ingress_t_igr_riBytes_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_riBytes
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663303,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663303, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_riBytes_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}

static void register_Ingress_t_igr_riRotateLastSize_value_pipe_to_pd(
    pipe_stful_mem_query_t *stful_query,
    uint32_t *register_values,
    int *value_count) {
  *value_count += stful_query->pipe_count;
  int p;
  for(p = 0; p < stful_query->pipe_count; p++) {
    register_values[p] = stful_query->data[p].word;
    }
}
p4_pd_status_t
p4_pd_main_register_read_Ingress_t_igr_riRotateLastSize
(
 p4_pd_sess_hdl_t sess_hdl,
 p4_pd_dev_target_t dev_tgt,
 int index,
 int flags,
 uint32_t *register_values,
 int *value_count
)
{
  p4_pd_status_t status;
  dev_target_t pipe_mgr_dev_tgt;
  pipe_mgr_dev_tgt.device_id = dev_tgt.device_id;
  pipe_mgr_dev_tgt.dev_pipe_id = dev_tgt.dev_pipe_id;

  uint32_t pipe_api_flags = flags & REGISTER_READ_HW_SYNC ?
                            PIPE_FLAG_SYNC_REQ : 0;
  /* Get the maximum number of elements the query can return. */
  int pipe_count;
  status = pipe_stful_query_get_sizes(sess_hdl,
                                      dev_tgt.device_id,
                                      100663301,
                                      &pipe_count);
  if(status != PIPE_MGR_SUCCESS) return status;
  /* Allocate space for the query results. */
  pipe_stful_mem_query_t stful_query;
  stful_query.pipe_count = pipe_count;
  stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);
  if (!stful_query.data) return PIPE_NO_SYS_RESOURCES;
  /* Perform the query. */
  status = pipe_stful_ent_query(sess_hdl, pipe_mgr_dev_tgt,
                                100663301, index,
                                &stful_query, pipe_api_flags);
  if(status != PIPE_MGR_SUCCESS) goto free_query_data;
  /* Convert the query data to PD format. */
  *value_count = 0;
  register_Ingress_t_igr_riRotateLastSize_value_pipe_to_pd(&stful_query, register_values, value_count);
  /* Free the space allocated for the pipe-mgr query data. */
  bf_sys_free(stful_query.data);
  return 0;
free_query_data:
  bf_sys_free(stful_query.data);
  return status;
}