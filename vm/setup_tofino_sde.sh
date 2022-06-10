# install tofino sde
# usage: ./setup_tofino_sde.sh <bf-sde-*.tgz>

if [ "$#" -ne 1 ]; then
  echo "usage: ./setup_tofino_sde.sh <bf-sde-*.tgz>"
  exit 1
fi 

echo "dollarsign at: $@"

function abs_path() {
    echo "$(cd "$(dirname "$1")"; pwd)/$(basename "$1")"    
}

SDE_FILE=$(abs_path $1)
SDE_DIR="$(pwd)/$(basename $SDE_FILE .tgz)"
# SDE_DIR="$(pwd)/$SDE_DIR"
SET_SCRIPT=$SDE_DIR/set_sde.bash

echo "installing sde from: $SDE_FILE --> $SDE_DIR"
tar -xzf $SDE_FILE
cd $SDE_DIR
# create install profile
echo "vm_sde_profile:
  global_configure_options: ''
  package_dependencies:
  - thrift
  - grpc
  packages:
  - bf-syslibs:
    - bf_syslibs_configure_options: ''
  - bf-utils:
    - bf_utils_configure_options: ''
  - bf-drivers:
    - bf_drivers_configure_options: ''
    - bf-runtime
    - p4-runtime
    - pi
  - ptf-modules
  tofino_architecture: tofino" > ./p4studio_build/profiles/vm_sde_profile.yaml


# create the set_sde helper
echo "function set_sde() {
    export SDE=$SDE_DIR
    export SDE_INSTALL=$SDE/install
    export PATH=$SDE_INSTALL/bin:$PATH
}
set_sde" > "$SET_SCRIPT"
# do install
./p4studio_build/p4studio_build.py -up vm_sde_profile

# setup hugepages
echo "----setting up hugepages for p4studio----"
echo 'vm.nr_hugepages=128' | sudo tee /etc/sysctl.d/hugepages.conf
sudo mount -t hugetlbfs none /dev/hugepages
sudo sysctl -w vm.nr_hugepages=128

# setup env variables
echo "----adding SDE env variables to bashrc----"
echo ". $SET_SCRIPT" >> ~/.bashrc