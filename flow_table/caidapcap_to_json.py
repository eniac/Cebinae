#!/usr/bin/env python3
import sys
from pcaplibs import *

# convert a caida pcap file into a trace of Themis_egress events for Lucid

config = {
  "python file": "themis_egress.py",
  "switches": 1,
  "max time": 10000000,
  "random seed": 0,
  "recirculation_ports": [196],
  "events": []
}

def deparse_as_themis_egress_event(pkt):
    if ("ip" in pkt.parsed_hdrs):
        ip = pkt.parsed_hdrs["ip"]
        event_rec = {
        "name": "Themis_egress",
        "args" : [0, ip.src, ip.dst, ip.len],
        "timestamp" : pkt.frame_hdr.tsUs  * 1000
        }
        return event_rec
    else:
        return None

def main():
    if (len(sys.argv) != 4):
        print ("usage: caidapcap_to_json.py <input.pcap> <output.json> <sample duration (ms)>")
        return
    infn = sys.argv[1]
    outfn = sys.argv[2]
    maxtime_ms = int(sys.argv[3])

    config["max time"] = (maxtime_ms * 1000000) + 1 # ms --> ns
    for pkt in PcapReader(infn).read():
        if (pkt.frame_hdr.tsUs > (maxtime_ms * 1000)): # ms --> us
            break
        event = deparse_as_themis_egress_event(parse_ip(parse_eth(pkt)))
        if (event != None):
            config["events"].append(event)

    # add the final event
    config["events"].append({"name": "finish_trial", "args":[], "timestamp":(maxtime_ms * 1000000) + 1})
    # dump to file 
    print ("converted %s samples covering %s ms"%(len(config["events"]), maxtime_ms))
    config_json_str = json.dumps(config, indent=2)
    open(outfn, "w").write(config_json_str)







if __name__ == '__main__':
    main()