#!/usr/bin/env python3

# run trials to measure accuracy
import sys, subprocess
import pickle as pkl
import math
from pcaplibs import *

# configuration parameters
prog = "egress.dpt"
pcapfn = "caidaSample.pcap"

# intermediate output
configfn = "egress.json"
symbfn = "egress.symb"

# final output
resultsfn = "results.pkl"

lucid_interp = "/cebinae/vm/lucid_binaries/dpt"
# REMOVE FOR USE IN VM
lucid_interp = "./dpt"



# set symbolic variables for trial
def generate_symb(n_stages, log_slots_per_stage):
    symb = {
        "sizes" : {
            "n_stages" : n_stages,
            "log_slots_per_stage" : log_slots_per_stage
        },
        "symbolics" : {
            "slots_per_stage" : 2**log_slots_per_stage
        }
    }
    symb_json_str = json.dumps(symb, indent=2)

    open(symbfn, "w").write(symb_json_str)


# generate interpreter configuration, including 
# input event trace, for a trial
def generate_config(delta, trial, start_ts_ms, interval):
    config = {
      "python path":"/Users/jsonch/opt/anaconda3/lib/libpython3.9.dylib",
      "python file": "egress.py",
      "switches": 1,
      "max time": 10000000,
      "random seed": 0,
      "recirculation_ports": [196],
      "events": []
    }
    def deparse_as_egress_event(pkt):
        if ("ip" in pkt.parsed_hdrs):
            ip = pkt.parsed_hdrs["ip"]
            event_rec = {
            "name": "Cebinae_egress",
            "args" : [0, ip.src, ip.dst, ip.len],
            "timestamp" : pkt.frame_hdr.tsUs  * 1000
            }
            return event_rec
        else:
            return None

    end_ts_ms = start_ts_ms + interval
    start_ts_us = start_ts_ms * 1000 
    end_ts_us = end_ts_ms * 1000
    for pkt in PcapReader(pcapfn).read():
        # skip packets from before selected interval
        if (pkt.frame_hdr.tsUs < start_ts_us):
            continue
        if (pkt.frame_hdr.tsUs > end_ts_us):
            break
        event = deparse_as_egress_event(parse_ip(parse_eth(pkt)))
        if (event != None):
            config["events"].append(event)
    # set max simulation time
    config["max time"] = (end_ts_us * 1000) + len(config["events"]) # add len(events) to be sure there's enough time for everything
    # add the final event
    config["events"].append({"name": "finish_trial", "args":[interval, trial, int(delta * 100)], "timestamp":(end_ts_us * 1000) + 1})
    # dump to file 
    print ("packets: %s"%(len(config["events"])))
    # print ("converted %s samples covering from %sms --> %sms"%(len(config["events"]), start_ts_ms, end_ts_ms))
    config_json_str = json.dumps(config, indent=2)
    open(configfn, "w").write(config_json_str)


triallogfn = "latest_trial_log.txt"
def run_trial():
    cmd = "%s %s --suppress-final-state"%(lucid_interp, prog)
    print ("running command: %s"%cmd)
    proc = subprocess.Popen(cmd.split(" "), stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    f = open(triallogfn, "w")
    f.write("---------- stdout --------------\n")
    out = str(out.decode("utf-8"))
    f.write(out)
    f.write("---------- stderr --------------\n")
    f.write(str(err.decode("utf-8")))
    f.close()

def analyze_trials(filename):
    results = pkl.load(open(filename, "rb"))
    # get unique memory configurations
    memory_params = list(set([r["memory_params"] for r in results]))
    for (n_stages, log_n_slots_per_stage) in memory_params:
        selected_results = [r for r in results if r["memory_params"] == (n_stages, log_n_slots_per_stage)]

        # get intervals
        intervals = list(set([r["interval"] for r in selected_results]))
        # print ("---- results for %s slots ----"%num_slots)
        result_tups = []
        for i in intervals:
            i_results = [r for r in selected_results if r["interval"] == i]
            mean_fpr = sum([r["fpr"] for r in i_results])/float(len(i_results))
            mean_fnr = sum([r["fnr"] for r in i_results])/float(len(i_results))
            result_tups.append((i, len(i_results), mean_fpr, mean_fnr))
        result_tups = sorted(result_tups, key = lambda tup : tup[0])
        print ("----- stages: %s slots per stage: %s-----"%(n_stages, 2**log_n_slots_per_stage))
        for result in result_tups:
            print ("interval: %sms # trials: %s mean fpr: %s mean fnr: %s"%result)

def load_trial_result(delta, interval, trial):
    fn = "trials/delta_%s_interval_%sms_trial%s.pkl"%(delta, interval, trial)
    rec = pkl.load(open(fn, "rb"))
    # print (rec)
    return rec

def run_experiment(resultfn):
    print ("trials starting. Results will be written to: %s"%resultfn)
    all_results = []
    delta = .1
    for (n_stages, log_n_slots) in [(1, 12), (2, 11), (4, 10)]:
        for interval in range(10, 101, 10):
            for trial in range(100):
                print ("------ starting trial %s with interval %s ------"%(trial, interval))
                generate_config(delta, trial, interval * trial, interval)
                generate_symb(n_stages, log_n_slots)
                run_trial()
                results = load_trial_result(delta, interval, trial)
                results["memory_params"] = (n_stages, log_n_slots)
                all_results.append(results)
                pkl.dump(all_results, open(resultfn, "wb"))
                print ("n_stages: %s log_n_slots: %s trial: %s interval: %s nflows: %s perfect measurement? %s fpr: %s fnr: %s"%(results["memory_params"][0], results["memory_params"][1], trial, interval, results["nflows"], results["perfect"], results["fpr"], results["fnr"]))

def main():
    if len(sys.argv) == 1:
        run_experiment(resultsfn)
        print("now run <measure_accuracy.py plot> to plot results")
    if len(sys.argv) > 1:
        if (sys.argv[1]) == "run":
            if (len(sys.argv) > 2):
                run_experiment(sys.argv[2])
            else:
                run_experiment(resultsfn)
            print("now run <measure_accuracy.py plot> to plot results")
        elif (sys.argv[1] == "plot"):
            if (len(sys.argv) > 2):
                analyze_trials(sys.argv[2])
            else:
                analyze_trials(resultsfn)

if __name__ == '__main__':
    main()

