# Cebinae

### Description

Cebinae is a mechanism that mitigates unfairness using distributed switch-local verifications & reactions, assuming no changes to legacy end host CCAs.

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

1. Clone/fetch the latest version of the repository: `git clone https://github.com/eniac/Cebinae`.

2. For the reproduction of the majority of results, only a canonical Linux machine (Ubuntu 16.04 LTS) is required. Other Linux distributions and OS are also expected to work, preferably Ubuntu 16.04 LTS or Ubuntu 18.04 LTS.

3. `python cebinae.py ns validate -p optimized` to validate if the environment is well set up, which typically takes around 15 min.
    * Upon failure of compilation or tests, check if the [prerequisite packages](https://www.nsnam.org/wiki/Installation#Ubuntu.2FDebian.2FMint) are installed for the corresponding platform. For Ubuntu 18.04 or 16.04, `python cebinae.py ns prerequisite` auto-installs the set of packages needed.

4. `python cebinae.py ns configure -p optimized` to configure optimized build profile before experiment execution.

5. Confirm that [gnuplot](http://www.gnuplot.info/) is installed by typing `gnuplot` in the linux prompt and type `q` to quit its terminal.

**Reproduce Figure 1 Illustrative Example**

* Run the experiment batch: `python cebinae.py ns run_batch -c fig1.json`. The tracing outputs of the experiments will appear under `ns/tmp_index/fig1/` by default.
* Plot Figure 1: `python cebinae.py plot --plot_target fig1 --data_dir ns/tmp_index/fig1/`. The output plot `figure1.eps` will show up under `ns/tmp_index/fig1/`.
* Expected outputs and plots are also stored under `ns/index/fig1/` for reference.


### Further Questions

Feel free to post issues or contact `leoyu@seas.upenn.edu` if any question arises.
