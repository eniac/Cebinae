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
    config_path = (cwd + "/ns/cebinae/configs/" + config_path)
  print("config_path: {}", config_path)

  with open(config_path, 'r') as f:
    config=json.loads(f.read())

  # --cwd changes the working directory (for output files etc) with default being the top of the ns-3 tree
  cmd = "./waf --cwd=\""+cwd+"/ns/cebinae/"+config["instance_type"]+"\" --run \""+config["instance_type"]+" --config_path="+config_path+" " 

  if len(config["batch_params"]) != 0 or config["batch_size"] > 1:
    print("ERR: batch_params: {0}, batch_size: {1}".format(config["batch_params"], config["batch_size"]))
    exit()

  params = ""
  for param in config.keys():
    if param != "instance_type" and param != "batch_size" and param != "batch_params":
      params += ("--"+param+"="+str(config[param])+" ")
  params = params[0:-1]

  cmd += (params+"\"")
  if enb_gdb:
    cmd += " --gdb"

  os.chdir(cwd+"/ns")
  print(cmd)
  os.system(cmd)

@timeit
def ns_run_batch(config_path):
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    config_path = (cwd + "/ns/cebinae/configs/" + config_path)
  print("config_path: {}", config_path)

  with open(config_path, 'r') as f:
    config=json.loads(f.read())

  cmds = []
  cmd_base = "./waf --cwd=\""+cwd+"/ns/cebinae/"+config["instance_type"]+"\" --run \""+config["instance_type"]+" --config_path="+config_path+" "   

  if len(config["batch_params"]) == 0 or config["batch_size"] == 1:
    print("ERR: batch_params: {0}, batch_size: {1}".format(config["batch_params"], config["batch_size"]))
    exit()
  for param in config["batch_params"]:
    if len(config[param]) != config["batch_size"]:
      print("ERR: {0} != {1}")
      exit()

  for instance_id in range(config["batch_size"]):
    params = ""
    for param in config.keys():
      if param != "instance_type" and param != "batch_params" and param != "batch_size":
        if param in config["batch_params"]:
          params += ("--"+param+"="+str(config[param][instance_id])+" ")
        else:
          params += ("--"+param+"="+str(config[param])+" ")
    params = params[0:-1]
    cmd = (cmd_base+params+"\"")
    cmds.append(cmd)

  os.chdir(cwd+"/ns")
  for cmd in cmds:
    print("======{}======".format(cmd))
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
    elif args.ns_cmd == "run_batch":
      ns_run_batch(args.config)
  elif args.cmd == "tofino":
    pass
