#!/usr/bin/env python3
# generate math function P4 blocks
import math

def main():
    print_log_tbl("rate_head")
    print_log_tbl("relative_round")
    print_log_tbl("relative_round_m_dt")
    print_log_tbl("rate_tail")
    print_exp_tbl("aggregate_size")
    print_exp_tbl("relative_round_m_dt_x_rate_tail")


    print_exp_log_sum_tbl("log_relative_round_m_dt", 
        "log_rate_tail", 
        "relative_round")

# print table to approximate log_invar = log2(inVar);
def print_log_tbl(inVar):    
    strs = []
    outVar = "log_"+inVar
    acnName = "aiCalc_%s"%outVar
    tblName = "tiCalc_%s"%outVar
    strs.append("action %s(bit<8> log_v) {%s = log_v;}"%(acnName, outVar))
    strs.append("""table %s {
    key = { %s : ternary; }
    actions = { %s; }"""%(tblName, inVar, acnName))
    strs.append("\tconst entries = {")
    for i in range(0, 32):
      exp_i = math.pow(2, i)
      strs.append("\t\t%i &&& %i : %s(%i);"%((exp_i), (exp_i), acnName, i))            
    strs.append("\t\t_ : %s(0);"%acnName)
    strs.append("\t}\n}")
    open(tblName+".p4", "w").write("\n".join(strs))


# print table for var = 2^log_Var;
def print_exp_tbl(var): 
    logVar = "log_"+var
    acnName = "aiExp_%s"%var
    tblName = "tiExp_%s"%var
    strs = []
    for i in range(0, 32):
        strs.append("action %s_%i() {%s = (bit<32>)1 << %i;}"%(acnName, i, var, i))
    strs.append("""table %s {
    key = { %s : ternary; }
    actions = { """%(tblName, logVar))
    for i in range(0, 32):
        strs.append("%s_%i; "%(acnName, i))
    strs.append("}")    

    strs.append("\tconst entries = {")
    for i in range(0, 32):
      strs.append("\t\t%i : %s_%i();"%((i), acnName, i))            
    strs.append("\t}\n}")
    open(tblName+".p4", "w").write("\n".join(strs))

# var_c = 2^(loga + logb)
def print_exp_log_sum_tbl(loga, logb, varc):
    acnName = "aiSumAndExp_%s"%varc
    tblName = "tiSumAndExp_%s"%varc
    strs = []
    entries = ""
    for a in range(0, 32):
        bits_left = 31 - a
        for b in range(0, bits_left):
            entries += "(%i, %i) : %s(%i);\n"%(a, b, acnName, int(math.pow(2, a+b)))
    strs.append("""action %s(bit<32> result_val) {\n%s=result_val;}"""%(acnName, varc))
    strs.append("""table %s {
        key = {
            %s : exact;
            %s : exact;
        }
        actions = { %s; }
        entries = { %s }
    }"""%(tblName, loga, logb, acnName, entries))
    open(tblName+".p4", "w").write("\n".join(strs))


if __name__ == '__main__':
    main()