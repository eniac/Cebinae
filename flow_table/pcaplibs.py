import struct, binascii, time, argparse, glob, os, ntpath, mmap, json
from collections import namedtuple

class PktRec(object):
    def __init__(self, frame_hdr, raw_bytes):
        self.frame_hdr = frame_hdr
        self.raw_bytes = raw_bytes
        self.unparsed_bytes = raw_bytes
        self.parsed_hdrs = {}
    def tostring(self):
        return str(self.parsed_hdrs)
    def len(self):
        return len(self.raw_bytes)


# ====================================
# =           Pcap reader.           =
# ====================================
class PcapReader(object):
    # Global pcap header. 
    PcapHdr = namedtuple("PcapHdr", "magic vMaj vMin tz acc snapLen linkHdr")
    PcapHdr_fmt = "<IHHIIII"
    PcapHdr_len = 24
    # Global for pcap 2.4.
    PCAP_MAGIC = 2712847316

    # header definitions. 
    FrameHdr = namedtuple("FrameHdr", "tsUs pktLen snapLen")
    FrameHdr_fmt = "<IIII"
    FrameHdr_len = 16

    def __init__(self, filename):
        self.f = open(filename, "rb")
        self.m = mmap.mmap(self.f.fileno(), 0, access=mmap.ACCESS_READ)
        self.pcapHdr = self.PcapHdr(*struct.unpack(self.PcapHdr_fmt, self.m.read(self.PcapHdr_len)))
        if (self.pcapHdr.magic != self.PCAP_MAGIC):
            print ("invalid pcap.")
            print (self.pcapHdr)
            self.f.close()
            exit()

    def read(self, startatzero = True):
        startTs = None
        # yield (frame header, packet bytes) tuples
        while True:
            hdr = self.m.read(self.FrameHdr_len)
            if len(hdr) < self.FrameHdr_len:
                break
            data = struct.unpack(self.FrameHdr_fmt, hdr)
            f = self.FrameHdr(data[0]*1000000 + data[1], data[2], data[3])
            pkt = self.m.read(f.pktLen)
            if len(pkt) < f.pktLen:
                break
            if (startatzero and startTs == None):
                startTs = f.tsUs
            f = self.FrameHdr(f.tsUs - startTs, f.pktLen, f.snapLen)
            yield PktRec(f, pkt)

    def close(self):
        self.f.close()
# ======  End of Pcap reader.  =======


# ===============================
# =           Parsers           =
# ===============================
eth = namedtuple("eth", "dst src etype")
eth_fmt = "!"+("B"*12)+"H"
eth_len = 14

def parse_eth(pkt, offset=0):
    if pkt.len() >= len(pkt.unparsed_bytes):
        d = pkt.unparsed_bytes[0:6]
        s = pkt.unparsed_bytes[6:12]
        t = struct.unpack("!H", pkt.unparsed_bytes[12:14])[0]
        pkt.parsed_hdrs[eth.__name__] = eth(d, s, t)
        pkt.unparsed_bytes = pkt.unparsed_bytes[14::]
    return pkt

ip = namedtuple("ip", "vihl tos len id fragoff ttl proto csum src dst")
ip_fmt = "!BBHHHBBHII"
ip_len = 20
def parse_ip(pkt):
    if ("eth" not in pkt.parsed_hdrs or pkt.parsed_hdrs["eth"].etype == 2048):
        # parsed_hdrs["ip"] = ip(vihl, ...)
        pkt.parsed_hdrs[ip.__name__] = ip(*struct.unpack(ip_fmt, pkt.unparsed_bytes[0:(ip_len)]))
        pkt.unparsed_bytes = pkt.unparsed_bytes[20::]
    return pkt


# ======  End of Parsers  =======