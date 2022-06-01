# Cebinae

### Description

Cebinae is a switch infrastructure that mitigates unfairness using distributed local state verifications & reactions, with no changes to the legacy end host CCAs.

### Main Content

* `cebinae.py`: The global driver script providing uniform entry point to launch a set of experiments and commands.
* `ns/`: ns-3.35 source tree with cebinae module and experiment instances
    * `configs/`: List of json configuration files as input to launch experiments
    * `index/`: Reference experiment output results
    * `cebinae/`: Experiement instances
* `tofino/`: Cebinae's P4-16 implementation and C++ control plane agent tested on both Wedge100BF-32X Tofino switch and its hardware simulator (for controlled test cases in VM). For more details, refer to `tofino/README.md`.

### Artifact Evaluation README

Below are the instructions to reproduce the major results in the paper manuscript.
For the ease of running the evaluation process, `cebinae.py` is created as the main utility script.

**Environment Setup**

* Clone/fetch the latest version of the repository: `git clone https://github.com/eniac/Cebinae`.

* For the reproduction of the majority of results, only a canonical Linux machine (Ubuntu 16.04 LTS) is required. Other Linux distributions and OS are also expected to work, preferably Ubuntu 16.04 LTS or Ubuntu 18.04 LTS.

* Validate environment set up.
    * `python cebinae.py ns validate -p optimized` to validate if the environment is well set up, which typically takes around 15 min. Upon failure of compilation or tests, check if the [prerequisite packages](https://www.nsnam.org/wiki/Installation#Ubuntu.2FDebian.2FMint) are installed for the corresponding platform. For Ubuntu 18.04 or 16.04, `python cebinae.py ns prerequisite` auto-installs the set of packages needed.
    * Confirm that [gnuplot](http://www.gnuplot.info/) is installed by typing `gnuplot` in the linux prompt and type `q` to quit its terminal.

* (Optional) A physical Tofino switch (tested end-to-end with `bf-sde-9.2.0`) connecting to 6 servers (TODO: Describe the wiring setup, NIC speed). This is not strictly required as most results in the paper are executed in ns-3.35 (that allows interating various environment conditions, topologies for fair comparison of the alternatives with the same exact background condition). We also provide a VM to with BF-SDE and Tofino hardware model that allows to validate equivalent results without the need of testbed set up.

* TODO: Install VM

Feel free to reach out if any question arises!

**Reproduce Figure 1 Illustrative Example**

* Before launching any experiments, run `python cebinae.py ns configure -p optimized` to configure optimized build profile for faster execution.
* Run the experiment batch: `python cebinae.py ns run_batch -c fig1.json` (takes ~2 min, or < 1min if with `--parallel` flag). The tracing outputs of the experiments will appear under temporary created direcotry `ns/tmp_index/fig1/` by default.
* Plot Figure 1: `python cebinae.py plot --plot_target fig1 --data_path ns/tmp_index/fig1/`. The output plot `figure1.eps` will show up under `ns/tmp_index/fig1/`.
* Expected outputs and plots are also stored under `ns/index/fig1/` for reference. The `*.eps` plot can be displayed by any EPS Viewer (e.g., Mac's built-in reader).

**Reproduce Table 2 TODO**

* `ns/configurs/bigtbl/` stores the configuration of experiments for the batch of experiments (3 instances) for each row, for instance, `ns/configurs/bigtbl/r0.json` corresponds to row 0 in the table.
* Run a single experiment batch, for instance `r0.json`
    * `python cebinae.py ns run_batch -c bigtbl/r0.json` (or `python cebinae.py ns run_batch -c bigtbl/r0.json --parallel` to decompose the batch instances for parallel execution), the results will appear under `ns/tmp_index/bigtbl/r0/`.
    * Read the metrics manually by examining the digest file for each experiment instance or run, for instance, `python cebinae.py parse --target bigtbl --data_path ns/tmp_index/bigtbl0/r0` to print the parsed results automatically at the terminal.
* Alternatively, one could also run `python cebinae.py ns run_instances -c bigtbl --parallel` in single command that will run all experiments under `ns/configs/bigtbl/` and exploits the underlying multi-core architecture if any. However, due to the number of experiment batches/instances and that a single experiment instance may take more than hours, one may further want to split the configuration files into sub-dirs and run separately on different machines.
* The expected results are stored under `ns/index/bigtbl/`, the digest file contains the expected completion time for the corresponding experiment instance.


### Further Questions

Feel free to post issues or contact `leoyu@seas.upenn.edu` if any question arises.




