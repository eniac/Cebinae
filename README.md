# Cebinae

### Description

Cebinae is a switch infrastructure that mitigates unfairness using distributed local state verifications & reactions, with no changes to the legacy end host CCAs.

### Main Content

* `cebinae.py`: The global utility script to drive a set of experiments and commands.
* `ns/`: ns-3.35 source tree with cebinae module and experiment instances
    * `configs/`: List of json configuration files as input to launch experiments
    * `index/`: Reference experiment output results
    * `cebinae/`: Experiement instances
* `tofino/`: Cebinae's P4-16 implementation and C++ control plane agent tested on both Wedge100BF-32X Tofino switch and its hardware simulator (for controlled test cases in VM). For more details, refer to `tofino/README.md`.

### Artifact Evaluation README

Below are the instructions to reproduce the major results in the paper manuscript.
For the ease of running the evaluation process, `cebinae.py` is created as the main entry point to experiement launches and analysis/plotting scripts to reproduce the results/graphs in the paper.

**Environment Setup**

* Clone/fetch the latest version of the repository: `git clone https://github.com/eniac/Cebinae`.

* For the reproduction of the majority of results, only a canonical Linux machine (e.g., Ubuntu 16.04 or 18.04 LTS) is required. Other Linux distributions and OS are also expected to work, preferably Ubuntu 16.04 LTS or Ubuntu 18.04 LTS.

* Validate environment set up.
    * `python cebinae.py ns validate -p optimized` to validate if the environment is well set up, which typically takes around 15 min. Upon failure of compilation or tests, check if the [prerequisite packages](https://www.nsnam.org/wiki/Installation#Ubuntu.2FDebian.2FMint) are installed for the corresponding platform, for instance, gcc >= 7.0.0. For Ubuntu 18.04, `python cebinae.py ns prerequisite` auto-installs the set of packages needed.
    * Confirm that [gnuplot](http://www.gnuplot.info/) is installed by typing `gnuplot` in the linux prompt and type `q` to quit its terminal.

* (Optional) A physical Tofino switch (tested end-to-end with `bf-sde-9.5.0`) connecting to a testbed of 6 servers (TODO: Describe the wiring setup, NIC speed).
    * This is not strictly required as most results in the paper are executed in ns-3.35 (that allows interating various environment conditions, and prevent randomness for fair comparative studies versus the alternatives with the same exact background condition). Meanwhile, we provide the VM instance (see next bullet point) to allow reproducing results on resource usage and top flow detection accuracy without the need to install the corresponding tofino SDE.

* We provide a VM with `bf-sde-9.5.0` for artifact evaluation process to validate the HW results in the accepted paper manuscript without the need of physical testbed set up.
    * TODO: VM set up scripts and the link to VM instance

Feel free to reach out if any question arises!

**Reproduce Figure 1 Illustrative Example**

* Before launching any experiments, run `python cebinae.py ns configure -p optimized` and `python cebinae.py ns build` to configure and build with optimized build profile for faster execution.
* Run the experiment batch: `python cebinae.py ns run_batch -c fig1.json` (takes ~2 min, or ~1min if with `--parallel` flag). The tracing outputs of the experiments will appear under temporary created direcotry `ns/tmp_index/fig1/` by default.
* Plot Figure 1: `python cebinae.py plot --plot_target fig1 --data_path ns/tmp_index/fig1/`. The output plot `figure1.eps` will show up under `ns/tmp_index/fig1/`.
* Expected outputs and plots are also stored under `ns/index/fig1/` for reference. The `*.eps` plot can be displayed by any EPS Viewer (e.g., Mac's built-in reader).

**Reproduce Table 2 TODO**

* `ns/configurs/bigtbl/` stores the configuration of experiments for the batch (3 instances) of experiments for each row, for instance, `ns/configurs/bigtbl/r0.json` corresponds to row 0 in the table.
* Run the experiment batches for each row, for instance `r0.json`:
    * `python cebinae.py ns run_batch -c bigtbl/r0.json` (or `python cebinae.py ns run_batch -c bigtbl/r0.json --parallel` to decompose the batch instances for parallel execution), the results will appear under `ns/tmp_index/bigtbl/r0/`.
    * Run `python cebinae.py parse --target bigtbl --data_path ns/tmp_index/bigtbl0/r0` to print the corresponding parsed results from digest files of each experiment instance to the terminal.
* Alternatively, one could also run `python cebinae.py ns run_instances -c bigtbl --parallel` in single command that will run all experiment configs under the specific directory `ns/configs/bigtbl/` and exploits the underlying multi-core architecture if any. Due to the number of experiment batches/instances and that a single experiment instance may take more than hours (for Gbps experiments in particular), one may further want to split the configuration files into sub-dirs and run separately on different machines. Meanwhile, if any experiment instance fails (due to occasional file reads/writes with multi-processing), one could always return to the previous `run_batch` command for re-execution.
* We understand that re-running all experiments may be computationally expensive. Therefore, all reference results and the parsed row print are stored under the corresponding row subdirectory of `ns/index/bigtbl/`, the digest file contains the expected completion time (on Intel(R) Xeon(R) Silver 4110 CPU @ 2.10GHz) for the corresponding experiment instance.


### Further Questions

Feel free to post issues or contact `leoyu@seas.upenn.edu` if any question arises!
