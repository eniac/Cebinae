import argparse
import json
import os
import subprocess
import sys
import time

def timeit(func):
  def wrap_func(*args, **kw):
    t1 = time.time()
    result = func(*args, **kw)
    t2 = time.time()
    print("{0}: {1:.2f}s".format(func.__name__, (t2-t1)))
    return result
  return wrap_func 

@timeit
def ns_validate(profile):
  cwd = os.getcwd()
  print("cwd: {}".format(cwd))

  os.chdir(cwd+"/ns")
  configure_cmd = "./waf configure --enable-examples --enable-tests "
  if profile == "optimized":
    configure_cmd += "--build-profile=optimized --out=build/optimized"
  elif profile == "debug":
    configure_cmd += "--build-profile=debug --out=build/debug"
  elif profile == "default":
    configure_cmd += "--out=build/"
  else:
    print("ERR")
    exit()

  cmds = [
    "./waf clean",
    configure_cmd,
    "./waf build",
    "./test.py"
  ]
  for cmd in cmds:
    print(cmd)
    subprocess.call(cmd.split())

@timeit
def ns_configure(profile):
  cwd = os.getcwd()
  print("cwd: {}".format(cwd))

  os.chdir(cwd+"/ns")
  configure_cmd = "./waf configure --enable-examples --enable-tests "
  if profile == "optimized":
    configure_cmd += "--build-profile=optimized --out=build/optimized"
  elif profile == "debug":
    configure_cmd += "--build-profile=debug --out=build/debug"
  elif profile == "default":
    configure_cmd += "--out=build/"
  else:
    print("ERR")
    exit()

  cmds = [
    "./waf clean",
    configure_cmd,
  ]
  for cmd in cmds:
    print(cmd)
    subprocess.call(cmd.split())

@timeit
def ns_run_instance(config_path, enb_gdb):
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    print("ERR: {} not absolute path", config_path)
  else:
    config_path = (cwd + "/ns/cebinae/configs/" + config_path)

  with open(config_path, 'r') as f:
    config=json.loads(f.read())

  # --cwd changes the working directory (for output files etc) with default being the top of the ns-3 tree
  cmd = "./waf --cwd=\""+cwd+"/ns/cebinae/"+config["instance_type"]+"\" --run \""+config["instance_type"]+" " 

  params = ""
  for param in config.keys():
    if param != "instance_type":
      params += ("--"+param+"="+str(config[param])+" ")
  params = params[0:-1]

  cmd += (params+"\"")
  if enb_gdb:
    cmd += " --gdb"

  os.chdir(cwd+"/ns")
  print(cmd)
  os.system(cmd)


if __name__ == '__main__':

  parser = argparse.ArgumentParser()
  subprsr = parser.add_subparsers(dest="cmd")

  ns_subprsr = subprsr.add_parser("ns")
  ns_subsubprsr = ns_subprsr.add_subparsers(dest="ns_cmd")

  ns_configure_prsr = ns_subsubprsr.add_parser("configure")
  ns_configure_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  ns_validate_prsr = ns_subsubprsr.add_parser("validate")
  ns_validate_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  ns_run_instance_prsr = ns_subsubprsr.add_parser("run_instance")
  ns_run_instance_prsr.add_argument("-c", "--config", type=str, required=True, help="Abs path of Json config file")
  ns_run_instance_prsr.add_argument("--gdb", action="store_true", help="Whether to enable gdb")

  ns_run_batch_prsr = ns_subsubprsr.add_parser("run_batch")
  ns_run_batch_prsr.add_argument("-c", "--config", type=str, required=True, help="Abs path of Json config file")

  tofino_subprsr = subprsr.add_parser("tofino")

  args = parser.parse_args()
  if args.cmd == "ns":
    if args.ns_cmd == "validate":
      ns_validate(args.profile)
    if args.ns_cmd == "configure":
      ns_configure(args.profile)
    elif args.ns_cmd == "run_instance":
      ns_run_instance(args.config, args.gdb)
  elif args.cmd == "tofino":
    pass
