# install all the dependencies for the lucid compiler and interpreter
echo "----installing Lucid dependencies----"
# install DPT dependencies for ubuntu 18.04
echo "----installing packages from apt ----"
sudo apt-get update -y
sudo apt-get install -y software-properties-common sudo
sudo apt-get update -y
sudo apt-get install -y python3 python3-pip m4 curl make build-essential python2.7 libgmp-dev pkg-config tcpreplay expect
pip3 install dpkt

echo "----initializing opam + ocaml packages ----"
sudo add-apt-repository ppa:avsm/ppa
sudo apt-get update -y
sudo apt-get install -y opam
opam init -a -y --compiler=4.11.1 
# opam switch create 4.11.1
eval $(opam env)
echo "eval 'opam config env'" >> ~/.bashrc
opam install -y \
  integers \
  batteries \
  ounit \
  ansiterminal \
  menhir \
  ppx_deriving \
  ppx_deriving_argparse \
  ppx_string_interpolation \
  zarith \
  visitors \
  fileutils \
  ppx_import \
  core \
  dune \
  ocamlgraph \
  angstrom \
  yojson \
  pyml \
  z3

eval $(opam env)