#### Cebinae VM experiments

Contents:

1. Setting up the VM
2. Reproducing flow table performance measurements (Figure 9)
3. Compiling the Cebinae Tofino Prototype and reporting resource utilization (Table 3)

##### Setting up the VM

(Optional) You can reproduce the results describe in this section in a VM with the lucid language compiler (leveraged to translate the higher-level event-driven code to P4-16) and Tofino SDE version 9.5.0 installed. 

**Note for artifact reviewers:** We provide a copy of a pre-built vm for convenience. To use the pre-built VM:

0. Ensure that you have [vagrant](https://www.vagrantup.com/downloads) and [virtualbox](https://www.virtualbox.org) installed.

1. Download the vm image: [google drive link](https://drive.google.com/file/d/1N7WauXIl2SsmGvJ8RixlagqzlqZtAd9w/view?usp=sharing)

2. Place the vm image ``cebinae.box`` into the ``vm_prebuilt`` directory of this repo.

3. Install and start the vm with:

   ```
   vagrant up --provider=virtualbox
   ```

To setup the VM from scratch:

1. Install vagrant and virtualbox. 

2. If you want to build a VM that can compile the P4 code using the makefile we have included, place a copy of bf-sde-9.5.0.tgz in the ``/vm`` directory and run 

   ```vagrant --sde=bf-sde-9.5.0.tgz up --provider=virtualbox``` 

    **note: this has only been tested with 9.5.0!**

3. Alternately, if you don't have access to the bf-sde file (you must have an intel account), you can build the VM without the SDE. This will let you test the flow tables data structure in the Lucid interpreter and compile the Lucid code to P4, but not compile the P4 code to the Tofino. To build the VM without the SDE, run:

   ```vagrant up --provider=virtualbox```

   **NOTE:** building the vm takes 1 - 2 hours.

##### Reproducing flow table performance results

These section describes how to measure and report the false positive and negative rate of the flow table data structure used in Cebinae's egress, using a 700MB sample trace from CAIDA, of a 10 Gb/s core router link.

1. ssh into the vm with ``vagrant ssh`` and go to the /cebinae directory. This directory is a shared pointer to the cebinae repo directory in the host machine (`git pull` to sync to the latest cebaine repository).

```
% vagrant ssh
Welcome to Ubuntu 18.04.4 LTS (GNU/Linux 4.15.0-101-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Fri Jun 10 16:53:14 UTC 2022

  System load:  0.58              Processes:           93
  Usage of /:   2.6% of 61.80GB   Users logged in:     0
  Memory usage: 3%                IP address for eth0: 10.0.2.15
  Swap usage:   0%

 * Super-optimized for small spaces - read how we shrank the memory
   footprint of MicroK8s to make it the smallest full K8s around.

   https://ubuntu.com/blog/microk8s-memory-optimisation

0 packages can be updated.
0 updates are security updates.



This system is built by the Bento project by Chef Software
More information can be found at https://github.com/chef/bento
vagrant@cebinaevm:~$ cd /cebinae/
vagrant@cebinaevm:/cebinae$ ls
cebinae.py  flow_table  ns  prototype_demonstration.md  README.md  tofino_prototype  vm  vm_experiments.md
```

2. Go to the ``flow_table`` directory 

```
vagrant@cebinaevm:/cebinae$ cd flow_table/
vagrant@cebinaevm:/cebinae/flow_table$ ls
allresults1024.pkl  caidapcap_to_json.py  egress.dpt  egress.py  measure_accuracy.py  pcaplibs.py
```

4. (Optional) Run the experiments to re-generate the results file ``allresults1024.pkl``. This will take **around 4 hours**, so if you wish to skip this step, an already generated ``allresults1024.pkl`` is included in the repo. 
The experiment script is hard-coded to use the pcap file ``~/caidaSample.pcap`` -- a 1 minute sample trace of a 10 Gb/s core router link from CAIDA. 
This pcap file is included in the pre-built VM, or can be downloaded here: [google drive link](https://drive.google.com/file/d/1S8xmWM5TRDbeRu-AtdNK7yM2xKVYYylC/view?usp=sharing)
You can modify `measure_accuracy.py` to use other pcaps as you wish. Results are qualitatively similar for all Caida workloads that we have tried.

```
vagrant@cebinaevm:/cebinae$ ./measure_accuracy.py 
trials starting. Results will be written to: allresults1024.pkl
------ starting trial 0 with interval 5 ------
packets: 1733
running command: ./dpt egress.dpt --suppress-final-state
trial: 0 interval: 5 nflows: 586 perfect measurement? True fpr: 0.0 fnr: 0.0
------ starting trial 1 with interval 5 ------
packets: 1497
running command: ./dpt egress.dpt --suppress-final-state
trial: 1 interval: 5 nflows: 536 perfect measurement? True fpr: 0.0 fnr: 0.0
------ starting trial 2 with interval 5 ------
...
```

5. Print out the experiment result to show false positive and false negative rates as interval length varies. 

```
vagrant@cebinaevm:/cebinae/flow_table$ ./measure_accuracy.py plot
interval: 5ms # trials: 100 mean fpr: 0.0 mean fnr: 0.0
interval: 10ms # trials: 100 mean fpr: 6.122409816315987e-05 mean fnr: 0.035
interval: 15ms # trials: 100 mean fpr: 0.00010217819034462492 mean fnr: 0.08333333333333331
interval: 20ms # trials: 100 mean fpr: 6.822385295437388e-05 mean fnr: 0.0825
interval: 25ms # trials: 100 mean fpr: 2.8551416630258384e-05 mean fnr: 0.10516666666666666
interval: 30ms # trials: 100 mean fpr: 5.3876657324846494e-05 mean fnr: 0.14619047619047623
interval: 35ms # trials: 100 mean fpr: 8.02821511018503e-05 mean fnr: 0.18455555555555553
interval: 40ms # trials: 100 mean fpr: 8.184131569662301e-05 mean fnr: 0.25449999999999995
interval: 45ms # trials: 100 mean fpr: 0.0001015941881574508 mean fnr: 0.2868333333333333
interval: 50ms # trials: 100 mean fpr: 0.00012345049084140132 mean fnr: 0.2513928571428572
```

   

##### Compiling the Cebinae Tofino prototype and reporting resource utilization

1. ssh into the vm.

2. Go to the ``tofino_prototype`` directory:

```
(base) jsonch@jsonchs-MBP vm % pwd        
/Users/jsonch/Desktop/cebinae/vm
(base) jsonch@jsonchs-MBP vm % vagrant ssh
Welcome to Ubuntu 18.04.4 LTS (GNU/Linux 4.15.0-101-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Fri Jun 10 16:53:14 UTC 2022

  System load:  0.58              Processes:           93
  Usage of /:   2.6% of 61.80GB   Users logged in:     0
  Memory usage: 3%                IP address for eth0: 10.0.2.15
  Swap usage:   0%

 * Super-optimized for small spaces - read how we shrank the memory
   footprint of MicroK8s to make it the smallest full K8s around.

   https://ubuntu.com/blog/microk8s-memory-optimisation

0 packages can be updated.
0 updates are security updates.



This system is built by the Bento project by Chef Software
More information can be found at https://github.com/chef/bento
vagrant@cebinaevm:~$ cd /cebinae/tofino_prototype
vagrant@cebinaevm:/cebinae/tofino_prototype$ ls
debug.hpp   egress.dpt.p4       ingress.p4  main.cpp  main.py   p4math  pd_helpers_gen.py
egress.dpt  ingress_objects.p4  libs        main.p4   makefile  pd      pd_helpers.hpp
```

4. (Optional) Compile the Lucid egress function to P4

```
# this command compiles egress.dpt (lucid program) into egress.dpt.p4 (p4 control block)
vagrant@cebinaevm:/cebinae/tofino_prototype$ make compile
```

5. Compile the P4 program and control plane program

```
# this command compiles the data and control plane binaries to tofino_prototype/main/
vagrant@cebinaevm:/cebinae/tofino_prototype$ make build
./libs/p4tapp.sh build main.p4
**** compiling main.p4 to main ****
cmd: /home/vagrant/bf-sde-9.5.0/install/bin/bf-p4c --verbose 3 --std p4-16 --target tofino --arch tna -o /cebinae/cebinae_vm/cebinae_tofino/main --bf-rt-schema /cebinae/cebinae_vm/cebinae_tofino/main/bf-rt.json /cebinae/cebinae_vm/cebinae_tofino/main.p4 
...
```

6. Print out Tofino resource utilization statistics

**Pipeline resources:**
```
vagrant@cebinaevm:/cebinae/tofino_prototype$ sed -n 10,26p ./main/pipe/logs/mau.resources.log
| Stage Number | Exact Match Input xbar | Ternary Match Input xbar | Hash Bit | Hash Dist Unit | Gateway | SRAM | Map RAM | TCAM | VLIW Instr | Meter ALU | Stats ALU | Stash | Exact Match Search Bus | Exact Match Result Bus | Tind Result Bus | Action Data Bus Bytes | 8-bit Action Slots | 16-bit Action Slots | 32-bit Action Slots | Logical TableID |
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|      0       |           21           |            0             |   144    |       4        |    3    |  8   |    0    |  0   |     4      |     0     |     0     |   2   |           3            |           4            |        4        |           18          |         0          |          0          |          0          |        8        |
|      1       |           22           |            0             |   142    |       2        |    6    |  17  |    8    |  0   |     6      |     4     |     0     |   3   |           5            |           9            |        6        |           16          |         0          |          0          |          0          |        11       |
|      2       |           31           |            0             |   113    |       2        |    2    |  12  |    2    |  0   |     3      |     1     |     0     |   2   |           3            |           4            |        4        |           26          |         0          |          0          |          0          |        7        |
|      3       |           21           |            16            |    33    |       2        |    2    |  7   |    2    |  4   |     3      |     1     |     0     |   0   |           1            |           1            |        1        |           8           |         0          |          0          |          0          |        5        |
|      4       |           10           |            0             |    20    |       2        |    2    |  4   |    4    |  0   |     2      |     2     |     0     |   0   |           1            |           2            |        2        |           8           |         0          |          0          |          0          |        4        |
|      5       |           0            |            1             |    0     |       0        |    0    |  1   |    0    |  1   |     32     |     0     |     0     |   0   |           0            |           0            |        2        |           4           |         0          |          0          |          0          |        2        |
|      6       |           16           |            16            |    30    |       3        |    0    |  9   |    6    |  9   |     4      |     3     |     0     |   0   |           0            |           0            |        4        |           8           |         0          |          0          |          0          |        4        |
|      7       |           0            |            17            |    0     |       0        |    0    |  2   |    0    |  4   |     32     |     0     |     0     |   0   |           0            |           0            |        2        |           4           |         0          |          0          |          0          |        2        |
|      8       |           18           |            32            |    42    |       3        |    2    |  5   |    4    |  6   |     2      |     2     |     0     |   0   |           1            |           2            |        1        |           4           |         0          |          0          |          0          |        3        |
|      9       |           6            |            0             |    16    |       1        |    1    |  2   |    2    |  0   |     1      |     1     |     0     |   0   |           1            |           1            |        1        |           0           |         0          |          0          |          0          |        2        |
|      10      |           0            |            0             |    0     |       0        |    0    |  0   |    0    |  0   |     1      |     0     |     0     |   0   |           0            |           0            |        1        |           0           |         0          |          0          |          0          |        1        |
|      11      |           0            |            8             |    0     |       0        |    0    |  3   |    2    |  2   |     3      |     1     |     0     |   0   |           0            |           0            |        1        |           0           |         0          |          0          |          0          |        1        |
|              |                        |                          |          |                |         |      |         |      |            |           |           |       |                        |                        |                 |                       |                    |                     |                     |                 |
|    Totals    |          145           |            90            |   540    |       19       |    18   |  70  |    30   |  26  |     93     |     15    |     0     |   7   |           15           |           23           |        29       |           96          |         0          |          0          |          0          |        50       |```
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

vagrant@cebinaevm:/cebinae/tofino_prototype$ sed -n 320,345p ./main/pipe/logs/phv_allocation_summary_3.log
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
|     MAU Group     | Containers Used |   Bits Used    | Bits Used on Ingress | Bits Used on Egress | Bits Allocated | Bits Allocated on Ingress | Bits Allocated on Egress | Available Bits |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
|       B0-15       |   5 ( 31.2 %)   |  35 ( 27.3 %)  |     35 ( 27.3 %)     |     0 (   0  %)     |  83 ( 64.8 %)  |       83 ( 64.8 %)        |       0 (   0  %)        |      128       |
|      B16-31       |   2 ( 12.5 %)   |  12 ( 9.38 %)  |     0 (   0  %)      |    12 ( 9.38 %)     |  12 ( 9.38 %)  |        0 (   0  %)        |       12 ( 9.38 %)       |      128       |
|      B32-47       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      128       |
|      B48-63       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      128       |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
|       H0-15       |   7 ( 43.8 %)   | 105 (  41  %)  |    105 (  41  %)     |     0 (   0  %)     | 105 (  41  %)  |       105 (  41  %)       |       0 (   0  %)        |      256       |
|      H16-31       |   5 ( 31.2 %)   |  66 ( 25.8 %)  |     0 (   0  %)      |    66 ( 25.8 %)     |  66 ( 25.8 %)  |        0 (   0  %)        |       66 ( 25.8 %)       |      256       |
|      H32-47       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      256       |
|      H48-63       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      256       |
|      H64-79       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      256       |
|      H80-95       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      256       |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
|       W0-15       |  16 (  100 %)   | 504 ( 98.4 %)  |    504 ( 98.4 %)     |     0 (   0  %)     | 632 (  123 %)  |       632 (  123 %)       |       0 (   0  %)        |      512       |
|      W16-31       |  10 ( 62.5 %)   | 320 ( 62.5 %)  |     0 (   0  %)      |    320 ( 62.5 %)    | 353 ( 68.9 %)  |        0 (   0  %)        |      353 ( 68.9 %)       |      512       |
|      W32-47       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      512       |
|      W48-63       |   0 (   0  %)   |  0 (   0  %)   |     0 (   0  %)      |     0 (   0  %)     |  0 (   0  %)   |        0 (   0  %)        |       0 (   0  %)        |      512       |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
|   Usage for 8b    |   7 ( 10.9 %)   |  47 ( 9.18 %)  |     35 ( 6.84 %)     |    12 ( 2.34 %)     |  95 ( 18.6 %)  |       83 ( 16.2 %)        |       12 ( 2.34 %)       |      512       |
|   Usage for 16b   |  12 ( 12.5 %)   | 171 ( 11.1 %)  |    105 ( 6.84 %)     |    66 (  4.3 %)     | 171 ( 11.1 %)  |       105 ( 6.84 %)       |       66 (  4.3 %)       |      1536      |
|   Usage for 32b   |  26 ( 40.6 %)   | 824 ( 40.2 %)  |    504 ( 24.6 %)     |    320 ( 15.6 %)    | 985 ( 48.1 %)  |       632 ( 30.9 %)       |      353 ( 17.2 %)       |      2048      |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
| Overall PHV Usage |  45 ( 20.1 %)   | 1042 ( 25.4 %) |    644 ( 15.7 %)     |    398 ( 9.72 %)    | 1251 ( 30.5 %) |       820 (  20  %)       |      431 ( 10.5 %)       |      4096      |
+-------------------+-----------------+----------------+----------------------+---------------------+----------------+---------------------------+--------------------------+----------------+
```
These statistics were used to create Table 3 as follows:
- Stages: (from mau.resources.log) The program uses resources in all stages 0 - 11
- PHV:    (from phv_allocation_summary_3.log) The cell (overall PHV usage, Bits Used) is 1042
- SRAM: (from mau.resources.log) The program uses 70 SRAM blocks. Each block is 16KB each, for a total of 1120KB.
- TCAM: (from mau.resources.log) The program uses 26 TCAM blocks. Each block is 1.28KB, for a total of <34KB.
- VLIWs: (from mau.resources.log) The program uses 93 VLIW instructions.
- Queues: Not shown here. The program configures 2 physical queues per port, on a 32-port switch this is 64 queues.

   
