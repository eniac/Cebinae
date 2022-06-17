import pickle as pkl
import os
# measurement externs used in themis_egress.dpt
# these only execute when running in the lucid interpreter

# {(src, dst):byte count}
groundtruth_flow_table = {}

# [[(src, dst, byte count)],[(src, dst, byte count)]]
dataplane_flow_table = [[(0, 0, 0) for i in range(4096)] for k in range(4)]

delta = None

def log_groundtruth_flowtable_update(src, dst, pkt_len):    
    # update the exact / full / ground truth table
    groundtruth_flow_table[(src, dst)] = groundtruth_flow_table.get((src, dst), 0) + pkt_len

def log_real_flowtable_update(stage, idx, src, dst, pkt_len):    
    # update the copy of the data plane table
    dataplane_flow_table[stage][idx] = (src, dst, pkt_len)

def print_true_flows():
    print ("---- true flows ----")
    flows = sorted(groundtruth_flow_table.items(), key = lambda tup : tup[1])
    for (k, v) in flows:
        print ("%s: %s"%(k, v))

def print_measured_flows():
    print ("---- measured flows ----")
    l = [((k, v), c) for (k, v, c) in dataplane_flow_table]
    flows = sorted(l, key = lambda tup : tup[1])
    for (k, v) in flows:
        if (v != 0):
            print ("%s: %s"%(k, v))

def find_true_top_n():
    top_n_keys, top_n_rates = [], []
    maxbytect = 0
    for bytect in groundtruth_flow_table.values():
        if bytect > maxbytect:
            maxbytect = bytect
    for (key, bytect) in groundtruth_flow_table.items():
        if (bytect >= maxbytect * (1 - delta)):
            top_n_keys.append(key)
            top_n_rates.append(bytect)
    return top_n_keys, top_n_rates

def find_measured_top_n():
    top_n_keys, top_n_rates = [], []
    maxbytect = 0
    for (_, _, bytect) in dataplane_flow_table:
        if bytect > maxbytect:
            maxbytect = bytect
    for (src, dst, bytect) in dataplane_flow_table:
        if (bytect >= maxbytect * (1 - delta)):
            top_n_keys.append((src, dst))
            top_n_rates.append(bytect)
    return top_n_keys, top_n_rates


def fpr(false_positives, negatives):
    false_positives = predicted_positives-true_positives
    return len(false_positives) / float(false_positives + true_negatives)

def calculate_accuracy(interval, trial, d):
    global delta
    global dataplane_flow_table
    # flatten dataplane table for analysis
    dataplane_flow_table = dataplane_flow_table[0] + dataplane_flow_table[1]
    delta = d / 100.0
    # print_true_flows()
    # print_measured_flows()

    true_top_n, true_top_rates = find_true_top_n()
    true_top_n = set(true_top_n)
    measured_top_n, measured_top_rates = find_measured_top_n()
    measured_top_n = set(measured_top_n)
    perfect = False
    if (true_top_n == measured_top_n):
        perfect = True
    print ("true top n:")
    print (true_top_n)
    print ("rate: %s"%sum(true_top_rates))    
    print ("measured_top_n: ")
    print (measured_top_n)
    print ("rate: %s"%sum(measured_top_rates))    

    all_keys = set(groundtruth_flow_table.keys())
    positives = set(true_top_n)
    negatives = all_keys - positives
    predicted_positives = set(measured_top_n)
    predicted_negatives = all_keys - predicted_positives

    false_positives = predicted_positives - positives
    fpr = len(false_positives) / float(len(negatives))

    false_negatives = positives - predicted_positives
    fnr = len(false_negatives) / float(len(positives))

    fn = "trials/delta_%s_interval_%sms_trial%s.pkl"%(delta, interval, trial)
    print ("writing results to: %s"%fn)
    try:
        os.mkdir("trials")
    except OSError as e:
        pass
    rec = {
        "delta":delta, 
        "interval":interval, 
        "trial":trial, 
        "nflows": len(groundtruth_flow_table.values()),
        "fpr": fpr,
        "fnr": fnr,
        "perfect": perfect
    }
    pkl.dump(rec, open(fn, "wb"))

