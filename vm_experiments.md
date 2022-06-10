#### Cebinae VM experiments

Contents:

1. Setting up the VM
2. Reproducing flow table performance measurements
3. Compiling the Cebinae Tofino Prototype and reporting resource utilization

##### Setting up the VM

(optional) You can reproduce the results describe in this section in a VM with the lucid language and the Tofino SDE version 9.5.0 installed. 

*Note for artifact reviewers: We provide the artifact reviewers a copy of this VM for convenience. However, we cannot publically share the VM as we are not allowed to redistribute the Tofino SDE. Below we provide instructions for building the vm from scratch, given a copy of the tofino sde tarball (bf-sde-9.5.0.tgz).*

To setup a vm ready to compile cebinae and reproduce the flow table accuracy experiment:

1. install vagrant and virtualbox 

2. place a copy of bf-sde-9.5.0.tgz in this directory **note: this has only been tested with 9.5.0!**
3. build the vm with: ``vagrant up --provider=virtualbox``
   - **NOTE:** this will take several hours to complete, because it sets up both Lucid dependencies and the tofino sde.

##### Reproducing flow table performance results

These section describes how to measure and report the false positive and negative rate of the flow table data structure used in Cebinae's egress, using a 700MB sample trace from CAIDA, of a 10 Gb/s core router link.

1. ssh into the vm

   ```vagrant ssh```

2. pull the cebinae repo 

   **TODO**

3. go to the ``detection_accuracy`` directory 

   **TODO**

4. (optional) run the experiments to re-generate the results file ``allresults1024.pkl``. This will take **several hours**, so if you wish to skip this step, an already generated ``allresults1024.pkl`` is included in the repo.

   ```
   vagrant@cebinaevm:/cebinae/cebinae_vm/detection_accuracy$ ./measure_accuracy.py 
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

5. print out the experiment result to show false positive and false negative rates as interval length varies. 

   ```
   $ ./measure_accuracy.py plot
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

   

   LEFT OFF HERE. Finish running the experiment, then copy / paste the compilation instructions

   

   ##### Compiling the Cebinae Tofino prototype and reporting resource utilization

   1. ssh into the vm

      ```vagrant ssh```

   2. pull the cebinae repo 

      **TODO**

   3. go to the ``cebinae_tofino`` directory

      **TODO**

   4. (optional) compile the Lucid egress function to P4

      **TODO**

   5. compile the P4 program and control plane program

      ```
      ... cebinae_tofino$ make build
      ./libs/p4tapp.sh build main.p4
      **** compiling main.p4 to main ****
      cmd: /home/vagrant/bf-sde-9.5.0/install/bin/bf-p4c --verbose 3 --std p4-16 --target tofino --arch tna -o /cebinae/cebinae_vm/cebinae_tofino/main --bf-rt-schema /cebinae/cebinae_vm/cebinae_tofino/main/bf-rt.json /cebinae/cebinae_vm/cebinae_tofino/main.p4 
      ...
      ```

      print out Tofino resource utilization statistics

      ```
      ... cebinae_tofino$ sed -n 29,46p ./main/pipe/logs/mau.resources.log
      --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      | Stage Number | Exact Match Input xbar | Ternary Match Input xbar | Hash Bit | Hash Dist Unit | Gateway |  SRAM  | Map RAM |  TCAM  | VLIW Instr | Meter ALU | Stats ALU | Stash  | Exact Match Search Bus | Exact Match Result Bus | Tind Result Bus | Action Data Bus Bytes | 8-bit Action Slots | 16-bit Action Slots | 32-bit Action Slots | Logical TableID |
      --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      |      0       |         16.41%         |          0.00%           |  34.62%  |     66.67%     |  18.75% | 10.00% |  0.00%  | 0.00%  |   12.50%   |   0.00%   |   0.00%   | 12.50% |         18.75%         |         25.00%         |      25.00%     |         14.06%        |       0.00%        |        0.00%        |        0.00%        |      50.00%     |
      |      1       |         17.19%         |          0.00%           |  34.13%  |     33.33%     |  37.50% | 21.25% |  16.67% | 0.00%  |   18.75%   |  100.00%  |   0.00%   | 18.75% |         31.25%         |         56.25%         |      37.50%     |         12.50%        |       0.00%        |        0.00%        |        0.00%        |      68.75%     |
      |      2       |         24.22%         |          0.00%           |  27.16%  |     33.33%     |  12.50% | 15.00% |  4.17%  | 0.00%  |   9.38%    |   25.00%  |   0.00%   | 12.50% |         18.75%         |         25.00%         |      25.00%     |         20.31%        |       0.00%        |        0.00%        |        0.00%        |      43.75%     |
      |      3       |         16.41%         |          24.24%          |  7.93%   |     33.33%     |  12.50% | 8.75%  |  4.17%  | 16.67% |   9.38%    |   25.00%  |   0.00%   | 0.00%  |         6.25%          |         6.25%          |      6.25%      |         6.25%         |       0.00%        |        0.00%        |        0.00%        |      31.25%     |
      |      4       |         7.81%          |          0.00%           |  4.81%   |     33.33%     |  12.50% | 5.00%  |  8.33%  | 0.00%  |   6.25%    |   50.00%  |   0.00%   | 0.00%  |         6.25%          |         12.50%         |      12.50%     |         6.25%         |       0.00%        |        0.00%        |        0.00%        |      25.00%     |
      |      5       |         0.00%          |          1.52%           |  0.00%   |     0.00%      |  0.00%  | 1.25%  |  0.00%  | 4.17%  |  100.00%   |   0.00%   |   0.00%   | 0.00%  |         0.00%          |         0.00%          |      12.50%     |         3.12%         |       0.00%        |        0.00%        |        0.00%        |      12.50%     |
      |      6       |         12.50%         |          24.24%          |  7.21%   |     50.00%     |  0.00%  | 11.25% |  12.50% | 37.50% |   12.50%   |   75.00%  |   0.00%   | 0.00%  |         0.00%          |         0.00%          |      25.00%     |         6.25%         |       0.00%        |        0.00%        |        0.00%        |      25.00%     |
      |      7       |         0.00%          |          25.76%          |  0.00%   |     0.00%      |  0.00%  | 2.50%  |  0.00%  | 16.67% |  100.00%   |   0.00%   |   0.00%   | 0.00%  |         0.00%          |         0.00%          |      12.50%     |         3.12%         |       0.00%        |        0.00%        |        0.00%        |      12.50%     |
      |      8       |         14.06%         |          48.48%          |  10.10%  |     50.00%     |  12.50% | 6.25%  |  8.33%  | 25.00% |   6.25%    |   50.00%  |   0.00%   | 0.00%  |         6.25%          |         12.50%         |      6.25%      |         3.12%         |       0.00%        |        0.00%        |        0.00%        |      18.75%     |
      |      9       |         4.69%          |          0.00%           |  3.85%   |     16.67%     |  6.25%  | 2.50%  |  4.17%  | 0.00%  |   3.12%    |   25.00%  |   0.00%   | 0.00%  |         6.25%          |         6.25%          |      6.25%      |         0.00%         |       0.00%        |        0.00%        |        0.00%        |      12.50%     |
      |      10      |         0.00%          |          0.00%           |  0.00%   |     0.00%      |  0.00%  | 0.00%  |  0.00%  | 0.00%  |   3.12%    |   0.00%   |   0.00%   | 0.00%  |         0.00%          |         0.00%          |      6.25%      |         0.00%         |       0.00%        |        0.00%        |        0.00%        |      6.25%      |
      |      11      |         0.00%          |          12.12%          |  0.00%   |     0.00%      |  0.00%  | 3.75%  |  4.17%  | 8.33%  |   9.38%    |   25.00%  |   0.00%   | 0.00%  |         0.00%          |         0.00%          |      6.25%      |         0.00%         |       0.00%        |        0.00%        |        0.00%        |      6.25%      |
      |              |                        |                          |          |                |         |        |         |        |            |           |           |        |                        |                        |                 |                       |                    |                     |                     |                 |
      |   Average    |         9.44%          |          11.36%          |  10.82%  |     26.39%     |  9.38%  | 7.29%  |  5.21%  | 9.03%  |   24.22%   |   31.25%  |   0.00%   | 3.65%  |         7.81%          |         11.98%         |      15.10%     |         6.25%         |       0.00%        |        0.00%        |        0.00%        |      26.04%     |
      --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      ```

      

   