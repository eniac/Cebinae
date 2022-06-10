#!/usr/bin/env python3

# run trials to measure accuracy
import sys, subprocess
import pickle as pkl
import math
from pcaplibs import *

# configuration parameters
infn = "caidaSample.pcap"
outfn = "egress.json"

prog = "egress.dpt"
lucid_interp = "./dpt"

resultsfn_base = "allresults.pkl"
def resultsfn(num_slots):
    return "allresults%s.pkl"%num_slots

# generate a configuration file for one trial
def generate_config(delta, trial, start_ts_ms, interval):
    config = {
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
    for pkt in PcapReader(infn).read():
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
    open(outfn, "w").write(config_json_str)


# outlog = "latest_trial_log.txt"

def run_trial():
    cmd = "%s %s --suppress-final-state"%(lucid_interp, prog)
    print ("running command: %s"%cmd)
    proc = subprocess.Popen(cmd.split(" "), stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    out, err = proc.communicate()
    # f = open(outlog, "w")
    # f.write("---------- stdout --------------\n")
    # out = str(out)
    # out.split("\n")
    # for l in out:
    #     f.write(l)
    # f.write("---------- stderr --------------\n")
    # f.write(str(err))
    # f.close()

def analyze_trials(filename):
    results = pkl.load(open(filename, "rb"))
    intervals = list(set([r["interval"] for r in results]))
    # print ("---- results for %s slots ----"%num_slots)
    result_tups = []
    for i in intervals:
        i_results = [r for r in results if r["interval"] == i]
        mean_fpr = sum([r["fpr"] for r in i_results])/float(len(i_results))
        mean_fnr = sum([r["fnr"] for r in i_results])/float(len(i_results))
        result_tups.append((i, len(i_results), mean_fpr, mean_fnr))
    result_tups = sorted(result_tups, key = lambda tup : tup[0])
    for result in result_tups:
        print ("interval: %sms # trials: %s mean fpr: %s mean fnr: %s"%result)

def load_trial_result(delta, interval, trial):
    fn = "trials/delta_%s_interval_%sms_trial%s.pkl"%(delta, interval, trial)
    rec = pkl.load(open(fn, "rb"))
    # print (rec)
    return rec

def run_experiment():
    fn = resultsfn(1024)
    print ("trials starting. Results will be written to: %s"%fn)
    all_results = []
    # 1. run trials and get results.
    delta = .1
    for interval in range(5, 55, 5):
        for trial in range(100):
            print ("------ starting trial %s with interval %s ------"%(trial, interval))
            generate_config(delta, trial, interval * trial, interval)
            run_trial()
            results = load_trial_result(delta, interval, trial)
            all_results.append(results)
            pkl.dump(all_results, open(fn, "wb"))
            print ("trial: %s interval: %s nflows: %s perfect measurement? %s fpr: %s fnr: %s"%(trial, interval, results["nflows"], results["perfect"], results["fpr"], results["fnr"]))

def main():
    if len(sys.argv) == 1:
        run_experiment()
        print("now run <measure_accuracy.py plot> to plot results")
    if len(sys.argv) > 1:
        if (sys.argv[1]) == "run":
            run_experiment()
            print("now run <measure_accuracy.py plot> to plot results")
        elif (sys.argv[1] == "plot"):
            filename = "allresults1024.pkl"
            if len(sys.argv) > 2:
                filename = sys.argv[2]
            analyze_trials(filename)
    # 2. plot results.
    # analyze_trials()

if __name__ == '__main__':
    main()

