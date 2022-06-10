
import sys, os, time
sys.path.append(os.path.dirname(os.path.realpath(__file__))+"/libs")
from mgr import *
m = Manager("main")

BOTTLENECK_PORT = 128
BOTTLENECK_PORT_F_TOP = BOTTLENECK_PORT << 1
BOTTLENECK_PORT_F_BOT = BOTTLENECK_PORT


def main():
    use_cebinae = False
    print (sys.argv)
    if (len(sys.argv) >= 2):
        if (sys.argv[1] == "cebinae"):
            use_cebinae = True
        elif (sys.argv[1] == "baseline"):
            use_cebinae = False
        else:
            print ("unexpected arguments: %s"%(sys.argv))

    commonStart()
    if (use_cebinae):
        print ("CEBINAE ENABLED")
        startWithCebinae()
    else:
        print ("CEBINAE DISABLED")
        startWithoutCebinae()
    m.disconnect()


def commonStart():
    # bring up ports and add forwarding paths
    m.port_up(144, "25G", "NONE") # plum
    m.port_up(155, "25G", "NONE") # peacock
    m.port_up(153, "25G", "NONE") # green
    m.port_up(163, "25G", "NONE") # mustard
    m.port_up(128, "25G", "RS")   # bottleneck link side 1 
    m.port_up(136, "25G", "RS")   # bottleneck link side 2
    # plum --> bottleneck --> peacock; peacock --> plum
    add_path_through_bottleneck(144, 0xec0d9a6de16d, 155, 0xec0d9a7e9182)
    # green --> bottleneck --> mustard; mustard --> green
    add_path_through_bottleneck(153, 0xec0d9a6de0c0, 163, 0xec0d9a6de0c8)


def startWithCebinae():
    # do some cebinae setup and turn it on in the dataplane
    # add entries to table that sets F for rotate packets
    m.addExactEntry("tiRotateF", ["hdr.pktgen.packet_id"], [0], "aiRotateF", {"fval":BOTTLENECK_PORT_F_BOT})
    m.addExactEntry("tiRotateF", ["hdr.pktgen.packet_id"], [1], "aiRotateF", {"fval":BOTTLENECK_PORT_F_TOP})

    m.setDefaultAction("tiToggleCebinae", "aiToggleCebinae", {"isOn":1})

def startWithoutCebinae():
    # turn cebinae off in the data plane 
    m.setDefaultAction("tiToggleCebinae", "aiToggleCebinae", {"isOn":0})

def add_path_through_bottleneck(srcport, srcmac, dstport, dstmac):
    """
    add a path from srcmac@srcport --> dstmac@dstport 
    that goes across the bottleneck link
    """
    # src to bottleneck
    m.addExactEntry("tiForward", 
        ["md.ingress_port", "hdr.ethernet.dst_addr"],
        [srcport, dstmac],
        'aiSetEgress',
        {"egr_port":128}
    )
    # bottleneck to dst
    m.addExactEntry("tiForward", 
        ["md.ingress_port", "hdr.ethernet.dst_addr"],
        [136, dstmac],
        'aiSetEgress',
        {"egr_port":dstport}
    )
    # dst to src
    m.addExactEntry("tiForward", 
        ["md.ingress_port", "hdr.ethernet.dst_addr"],
        [dstport, srcmac],
        'aiSetEgress',
        {"egr_port":srcport}
    )






if __name__ == '__main__':
    main()