#!/usr/bin/env python3

import re

# generate pd_helpers.hpp by copying the most recent definitions from pd.h and pd.c

pdh_fn = "pd/pd/pd.h"
pdc_fn = "pd/src/pd.c"
pd_helpers_fn = "pd_helpers.hpp"

def patch_voidcast(src):
    # cast outputs of bf_sys_calloc to not be void...
    # in declarations.
    res = re.findall(r"(.*?)( \*.* = )(bf_sys_calloc.*)", src)
    for res in res:
        cast_str = "(%s*)"%res[0]
        newline = res[0]+res[1]+cast_str+res[2]
        oldline = res[0]+res[1]+res[2]
        # print ("----")
        # print (oldline)
        # print ("---> ")
        # print (newline)
        # print ("----")
        src = src.replace(oldline, newline)

    # stragglers...
    return src.replace("stful_query.data = bf_sys_calloc(pipe_count, sizeof *stful_query.data);", 
        "stful_query.data = (pipe_stful_mem_spec_t*)bf_sys_calloc(pipe_count, sizeof *stful_query.data);")

def patch_num_actually_read(src):
    return src.replace("int *num_actually_read,", "uint32_t *num_actually_read,")

def main():
    pdh = open(pdh_fn, "r").read()
    pdc = open(pdc_fn, "r").read()

    typedef_names = [
        # "p4_pd_main_Ingress_t_igr_tiForward_match_spec", 
        # "p4_pd_main_Ingress_t_igr_aiSetEgress_action_spec",
        "p4_pd_main_Ingress_t_igr_tiCalcF_match_spec",
        "p4_pd_main_Ingress_t_igr_tiGetRates_head_match_spec",
        "p4_pd_main_Ingress_t_igr_aiGetRates_head_action_spec",
        "p4_pd_main_Ingress_t_igr_tiGetRates_tail_match_spec",
        "p4_pd_main_Ingress_t_igr_aiGetRates_tail_action_spec",
        "p4_pd_main_Ingress_t_igr_tiReadLastSize_match_spec",
        "p4_pd_main_Ingress_t_igr_aiReadLastSize_action_spec",
        "p4_pd_main_Ingress_t_igr_tiCalcSaturated_match_spec"
        ]
    typedef_blocks = []
    for name in typedef_names:
        print ("extracting pd for: %s"%name)
        res = re.findall("typedef struct %s {.*?} %s_t;"%(name, name), pdh, re.DOTALL)
        typedef_blocks.append(res[0])

    fcn_names = [
    # forwarding table 
    # "build_key_Ingress_t_igr_tiForward", 
    # "build_match_spec_Ingress_t_igr_tiForward", 
    # "build_action_spec_Ingress_t_igr_aiSetEgress", 
    # "p4_pd_main_Ingress_t_igr_tiForward_table_add_with_Ingress_t_igr_aiSetEgress", 
    # "p4_pd_main_Ingress_t_igr_tiForward_table_delete", 
    # "p4_pd_main_Ingress_t_igr_tiForward_set_default_action_Ingress_t_igr_aiSetEgress",
    # saturated table
    "build_key_Ingress_t_igr_tiCalcSaturated", 
    "build_match_spec_Ingress_t_igr_tiCalcSaturated", 
    "p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiSaturated", 
    "p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_add_with_Ingress_t_igr_aiNotSaturated", 
    "p4_pd_main_Ingress_t_igr_tiCalcSaturated_table_delete_by_match_spec",
    # last size table 
    "build_key_Ingress_t_igr_tiReadLastSize", 
    "build_match_spec_Ingress_t_igr_tiReadLastSize", 
    "build_action_spec_Ingress_t_igr_aiReadLastSize", 
    "p4_pd_main_Ingress_t_igr_tiReadLastSize_table_add_with_Ingress_t_igr_aiReadLastSize", 
    "p4_pd_main_Ingress_t_igr_tiReadLastSize_table_modify_with_Ingress_t_igr_aiReadLastSize",
    # top flows table
    "build_key_Ingress_t_igr_tiCalcF", 
    "build_match_spec_Ingress_t_igr_tiCalcF",
    "p4_pd_main_Ingress_t_igr_tiCalcF_table_add_with_Ingress_t_igr_aiSetFTop",
    "p4_pd_main_Ingress_t_igr_tiCalcF_table_delete", 
    "p4_pd_main_Ingress_t_igr_tiCalcF_table_delete_by_match_spec",
    # tiGetRates_head
    "build_key_Ingress_t_igr_tiGetRates_head", 
    "build_match_spec_Ingress_t_igr_tiGetRates_head", 
    "build_action_spec_Ingress_t_igr_aiGetRates_head", 
    "p4_pd_main_Ingress_t_igr_tiGetRates_head_table_add_with_Ingress_t_igr_aiGetRates_head", 
    "p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head",
    "p4_pd_main_Ingress_t_igr_tiGetRates_head_table_modify_with_Ingress_t_igr_aiGetRates_head_by_match_spec",
    "p4_pd_main_Ingress_t_igr_tiGetRates_head_table_delete_by_match_spec",
    # tiGetRates_tail
    "build_key_Ingress_t_igr_tiGetRates_tail", 
    "build_match_spec_Ingress_t_igr_tiGetRates_tail", 
    "build_action_spec_Ingress_t_igr_aiGetRates_tail", 
    "p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_add_with_Ingress_t_igr_aiGetRates_tail", 
    "p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail",
    "p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_modify_with_Ingress_t_igr_aiGetRates_tail_by_match_spec",
    "p4_pd_main_Ingress_t_igr_tiGetRates_tail_table_delete_by_match_spec",
    # active head/tail register
    "register_Ingress_t_igr_ri_headq_value_pipe_to_pd",
    "register_Ingress_t_igr_ri_headq_value_pd_to_pipe",
    "register_Ingress_t_igr_ri_tailq_value_pipe_to_pd",
    "register_Ingress_t_igr_ri_tailq_value_pd_to_pipe",
    "p4_pd_main_register_read_Ingress_t_igr_ri_headq",
    "p4_pd_main_register_write_Ingress_t_igr_ri_headq",
    "p4_pd_main_register_read_Ingress_t_igr_ri_tailq",
    "p4_pd_main_register_write_Ingress_t_igr_ri_tailq",
    # egress port register polling
    "register_Egress_t_egr_port_cts_value_pipe_to_pd",
    "p4_pd_main_register_read_Egress_t_egr_port_cts",
    # egress flow register polling
    "register_Egress_t_egr_flow_src1_value_pipe_to_pd",
    "register_Egress_t_egr_flow_dst1_value_pipe_to_pd",
    "register_Egress_t_egr_flow_ct1_value_pipe_to_pd",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_src1",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_dst1",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_ct1",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_src1",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_dst1",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_ct1",
    "register_Egress_t_egr_flow_src2_value_pipe_to_pd",
    "register_Egress_t_egr_flow_dst2_value_pipe_to_pd",
    "register_Egress_t_egr_flow_ct2_value_pipe_to_pd",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_src2",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_dst2",
    "p4_pd_main_register_range_read_Egress_t_egr_flow_ct2",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_src2",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_dst2",
    "p4_pd_main_register_reset_all_Egress_t_egr_flow_ct2",
    # queue counter debug register
    "register_Ingress_t_igr_queueCounter_value_pipe_to_pd",
    "p4_pd_main_register_read_Ingress_t_igr_queueCounter",

    # debug registers
    "register_Ingress_t_igr_fCount_value_pipe_to_pd",
    "p4_pd_main_register_read_Ingress_t_igr_fCount",
    "register_Ingress_t_igr_riBytes_value_pipe_to_pd",
    "p4_pd_main_register_read_Ingress_t_igr_riBytes",
    "register_Ingress_t_igr_riRotateLastSize_value_pipe_to_pd",
    "p4_pd_main_register_read_Ingress_t_igr_riRotateLastSize"
    ]

    fcn_blocks = []
    for name in fcn_names:
        print ("extracting pd for: %s"%name)
        pat = re.compile(r"^[\w\s_]*?%s.*?^}"%(name), re.DOTALL | re.MULTILINE)
        res = re.findall(pat , pdc)
        fcn_blocks.append(res[0])

    blocks = typedef_blocks + fcn_blocks
    codeout = "\n".join(blocks)
    codeout = patch_voidcast(codeout)
    codeout = patch_num_actually_read(codeout)
    # print ("------")
    # print (codeout)
    # print ("------")
    open(pd_helpers_fn, "w").write(codeout)

if __name__ == '__main__':
    main()