import argparse
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


if __name__ == '__main__':

  parser = argparse.ArgumentParser()
  subprsr = parser.add_subparsers(dest="cmd")

  ns_subprsr = subprsr.add_parser("ns")
  ns_subsubprsr = ns_subprsr.add_subparsers(dest="ns_cmd")

  ns_configure_prsr = ns_subsubprsr.add_parser("configure")
  ns_configure_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  ns_validate_prsr = ns_subsubprsr.add_parser("validate")
  ns_validate_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  tofino_subprsr = subprsr.add_parser("tofino")


  args = parser.parse_args()
  if args.cmd == "ns":
    if args.ns_cmd == "validate":
      ns_validate(args.profile)
    if args.ns_cmd == "configure":
      ns_configure(args.profile)
    elif args.ns_cmd == "run":
      pass
  elif args.cmd == "tofino":
    pass


