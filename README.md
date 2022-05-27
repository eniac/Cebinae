# Cebinae

### Description

**Main Contents**

* `cebinae.py`: The global driver script providing uniform entry point to launch a set of experiments and commands.
* `ns/`: ns-3.35 source tree with cebinae module and experiment instances
    * `configs/`: List of json configuration files as input to launch experiments
    * `index/`: Reference experiment output results
    * `cebinae/`: Experiement instances
* `tofino/`: Cebinae's P4-16 implementation and C++ control plane agent running on both Wedge100BF-32X Tofino switch and its hardware simulator (for testing in VM). For more details, refer to `tofino/README.md`.



### Further Questions

Feel free to post issues or contact `leoyu@seas.upenn.edu` if any question arises.
