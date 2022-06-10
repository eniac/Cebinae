#### Physical testbed demonstration

To run cebinae on a physical tofino, first compile it on the tofino where it will run, with ``make build``.

After it is built, you can run  ``make hw_cebinae`` to start the data plane, control plane, and the python script ``main.py`` that installs forwarding rules and brings up ports. The rest of this document describes how to run a simple experiment with cebinae on a hardware testbed with a Tofino connected to 4 servers.

##### Hardware testbed demonstration

As a simple demonstration of the prototype, connect 4 servers to ports on pipeline #1 of the tofino, and a cable from port 128 to 136. We csall the 4 servers *(1) plum*, *(2) peacock*, *(3) green*, *(4) mustard*. We will run a simple experiment where an aggressive flow from green to mustard uses more bandwidth than a parallel flow from plum to peacock that uses the same bottleneck link. Then we will enable cebinae and see that it increases fairness.

Run the following commands on the tofino and the servers to carry out the experiment. Note: before running the experiment, make sure that the arp tables of all servers are configured appropriately -- this data plane does not forward arp packets. Also, adjust ``main.py`` to bring up the ports on the tofino connected to your servers and install forwarding rules to implement the following routes: 
```
plum --> bottleneck port (dpid 128) --> peacock;
peacock --> plum;
green --> bottleneck port (dpid 128) --> mustard;
mustard --> green;
```

###### Trial without cebinae
**on the Tofino**
*start the dataplane without running cebinae*

```
$ make hw_baseline
sudo killall bf_switchd
./libs/p4tapp.sh hw main.p4 baseline
... (output elided)
[PY_MGR] CEBINAE DISABLED
[PY_MGR] setting default action: tiToggleCebinae --> aiToggleCebinae({'isOn': 0})
[PY_MGR] mgr.py disconnect complete.
[SWITCHD_MGR] Launched pktgen for pipe 1
**** switchd running -- press ctrl+c to terminate. ****
```
**on servers 2 and 4 (peacock and mustard)**
*start iperf3*
```
$ iperf3 -s 
-----------------------------------------------------------
Server listening on 5201
-----------------------------------------------------------
```

**on server 1 (plum)**
*start a 60 second iperf with 16 threads*
```
iperf3 -c 10.1.1.5 -P 16 -t 60
```
**on server 3(green)**
*start a 20 second iperf with 1 thread*
```
$ iperf3 -c 10.1.1.3 -t 20
...
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Retr
[  4]   0.00-20.00  sec  9.00 GBytes  3.87 Gbits/sec  59924             sender
[  4]   0.00-20.00  sec  9.00 GBytes  3.87 Gbits/sec                  receiver

iperf Done.

```
The 20 second iperf will generally only get <4 Gb/s of bandwidth.

###### Trial with cebinae
Now, repeat the above steps, except on the Tofino, start the dataplane with cebinae enabled: 

**on tofino**
```
$ make hw_cebinae
sudo killall bf_switchd
./libs/p4tapp.sh hw main.p4 cebinae
... # output elided
[PY_MGR] CEBINAE ENABLED
[PY_MGR] adding exact entry: tiRotateF[['hdr.pktgen.packet_id']==[0]] --> aiRotateF({'fval': 128})
[PY_MGR] adding exact entry: tiRotateF[['hdr.pktgen.packet_id']==[1]] --> aiRotateF({'fval': 256})
[PY_MGR] setting default action: tiToggleCebinae --> aiToggleCebinae({'isOn': 1})
[PY_MGR] mgr.py disconnect complete.
[SWITCHD_MGR] Launched pktgen for pipe 1
**** switchd running -- press ctrl+c to terminate. ****
```

**on servers 2 and 4 (peacock and mustard)**
*start iperf3*
```
$ iperf3 -s 
-----------------------------------------------------------
Server listening on 5201
-----------------------------------------------------------
```

**on server 1 (plum)**
*start a 60 second iperf with 16 threads*
```
iperf3 -c 10.1.1.5 -P 16 -t 60
```
**on server 3(green)**
*start a 20 second iperf with 1 thread*
```
$ iperf3 -c 10.1.1.3 -t 20
jsonch@plum:~$ iperf3 -c 10.1.1.3 -t 20   
- - - - - - - - - - - - - - - - - - - - - - - - -
[ ID] Interval           Transfer     Bandwidth       Retr
[  4]   0.00-20.00  sec  15.2 GBytes  6.52 Gbits/sec  25262             sender
[  4]   0.00-20.00  sec  15.2 GBytes  6.52 Gbits/sec                  receiver```

```
Throughput will vary, but in general should be 5-7 Gb/s instead of <4 Gb/s. If you repeat the experiment with tcp reno on green, it will be around 2 Gb/s without cebinae instead of 4 Gb/s.