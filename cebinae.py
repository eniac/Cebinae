import argparse
import json
import multiprocessing
import os
import re
import signal
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
def ns_build():
  cwd = os.getcwd()
  print("cwd: {}".format(cwd))

  os.chdir(cwd+"/ns")
  cmd = "./waf build"
  print(cmd)
  subprocess.call(cmd.split())  

@timeit
def ns_run_instance(config_path, enb_gdb):
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    config_path = (cwd + "/ns/configs/" + config_path)
  print("config_path: {}".format(config_path))

  with open(config_path, 'r') as f:
    config=json.loads(f.read())

  # --cwd changes the working directory (for output files etc) with default being the top of the ns-3 tree
  cmd = "./waf --cwd=\""+cwd+"/ns/"+"\" --run \""+config["instance_type"]+" --config_path="+config_path+" " 

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
  waf_cmd_wrapper(cmd)
  os.chdir(cwd)

def waf_cmd_wrapper(cmd):
  print("PID {0}: {1}".format(os.getppid(), cmd))
  os.system(cmd)

# Perhaps use MPI
def ns_run_batch(config_path, parallel):
  t1 = time.time()
  print("=== ns_run_batch({0}), PID {1} ===".format(config_path, os.getppid()))
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    config_path = (cwd + "/ns/configs/" + config_path)
  print("config_path: {}".format(config_path))
  if not os.path.isfile(config_path):
    print("ERR: not file!")
    exit()

  with open(config_path, 'r') as f:
    config=json.loads(f.read())

  cmds = []
  cmd_base = "./waf --cwd=\""+cwd+"/ns/"+"\" --run \""+config["instance_type"]+" --config_path="+config_path+" "   

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
  if parallel:
    processes = []
    processes_target = []
    for cmd in cmds:
      p = multiprocessing.Process(target=waf_cmd_wrapper, args=(cmd,))
      p.start()
      processes.append(p)
    for p in processes:
      p.join()
  else:
    for cmd in cmds:
      print("======{}======".format(cmd))
      if os.system(cmd) != 0:
        exit()
  os.chdir(cwd)

  t2 = time.time()
  print("ns_run_batch: {0:.2f}s".format(t2-t1))    

@timeit
def ns_run_batches(config_path, parallel):
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    config_path = (cwd + "/ns/configs/" + config_path)
  print("config_path: {}".format(config_path))
  if not os.path.isdir(config_path):
    print("ERR: not dir!")
    exit()
  
  json_files = sorted([fn for fn in os.listdir(config_path) if fn.endswith('.json')])
  print("=== List of config files: {} ===".format(json_files))

  if parallel:
    print("=== Parallel branch ===") 
    print("PPID: {0}, PGID: {1}".format(os.getppid(), os.getpgid(os.getpid())))
    pool = multiprocessing.Pool(int(os.cpu_count()/2)) # Default to os.cpu_count() logical cores
    try:
      processes = []
      for json_file in json_files:
        processes.append(pool.apply_async(ns_run_batch, args=(config_path+"/"+json_file,False,)))
      results = [p.get() for p in processes]
      pool.close()
      pool.join()
    except KeyboardInterrupt:
      print("Captured KeyboardInterrupt")
      pool.terminate()
      exit(1)
  else:
    for json_file in json_files:
      ns_run_batch(config_path+"/"+json_file)    

@timeit
def ns_run_instances(config_path, parallel):
  cwd = os.getcwd()
  if not os.path.isabs(config_path):
    config_path = (cwd + "/ns/configs/" + config_path)
  print("config_path: {}".format(config_path))
  if not os.path.isdir(config_path):
    print("ERR: not dir!")
    exit()
  json_files = sorted([fn for fn in os.listdir(config_path) if fn.endswith('.json')])
  print("=== List of config files: {} ===".format(json_files))

  cmds = []  
  for json_file in json_files:
    with open(config_path+"/"+json_file, 'r') as f:
      config=json.loads(f.read())
      cmd_base = "./waf --cwd=\""+cwd+"/ns/"+"\" --run \""+config["instance_type"]+" --config_path="+config_path+"/"+json_file+" "  
      if len(config["batch_params"]) == 0 or config["batch_size"] == 1:
        params = ""
        for param in config.keys():
          if param != "instance_type" and param != "batch_size" and param != "batch_params":
            params += ("--"+param+"="+str(config[param])+" ")
        params = params[0:-1]
        cmd = (bmd_base+params+"\"")
        cmds.append(cmd)  
      else:
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
 
  if parallel:
    pool = multiprocessing.Pool(int(os.cpu_count()/2))
    pool.map(waf_cmd_wrapper, cmds)
    print("=== Unblocked from pool map ===")
  else:
    for cmd in cmds:
      if os.system(cmd) != 0:
        exit()

@timeit
def ns_clear():
  cwd = os.getcwd()
  tmp_dirs = [
    "/ns/tmp_index"
  ]
  for tmp_dir in tmp_dirs:
    cmd = ("rm -rf "+cwd+tmp_dir)
    print(cmd)
    subprocess.call(cmd.split())

@timeit
def ns_kill():
  cmd = "sudo killall dumbbell_long"
  subprocess.call(cmd.split())

@timeit
def ns_prerequisite():
  # Install packages on a clean Ubuntu 18.04 LTS machine for NS-3 dependencies: https://www.nsnam.org/wiki/Installation
  install_cmds = [
    "sudo apt-get update",
    "sudo apt install python python3 g++ cmake python3-dev pkg-config sqlite3 python3-setuptools git qt5-default gdb valgrind",
    "sudo apt install gir1.2-goocanvas-2.0 python3-gi python3-gi-cairo python3-pygraphviz gir1.2-gtk-3.0 ipython3",
    "sudo apt install openmpi-bin openmpi-common openmpi-doc libopenmpi-dev autoconf cvs bzr unrar",
    "sudp apt install uncrustify doxygen graphviz imagemagick texlive texlive-extra-utils texlive-latex-extra texlive-font-utils dvipng latexmk",
    "sudo apt install python3-sphinx dia gsl-bin libgsl-dev libgslcblas0 sqlite sqlite3 libsqlite3-dev tcpdump",
    "sudo apt install libxml2 libxml2-dev cmake libc6-dev libc6-dev-i386 libclang-dev llvm-dev automake python3-pip",
    "python3 -m pip install --user cxxfilt",
    "sudo apt install libgtk-3-dev libxml2 libxml2-dev libboost-all-dev"
  ]
  for cmd in install_cmds:
    print(cmd)
    subprocess.call(cmd.split())

@timeit
def parse_bigtbl(data_path):
  cwd = os.getcwd()
  if not os.path.isabs(data_path):
    data_path = (cwd+"/"+data_path)
  print("data_path pointing to the root dir of the bigtbl row: {0}".format(data_path))
  if not os.path.isdir(data_path):
    print("ERR: not dir!")
    exit()
  
  batch_config = None
  with open(data_path+"/fifo/config.json", 'r') as f:
    batch_config=json.loads(f.read())

  bottleneck_bw = batch_config["bottleneck_bw"]
  num_cca = batch_config["num_cca"]
  buf_size = batch_config["switch_total_bufsize"]

  ccas = []
  rtts = []
  num_ccas = []
  re_num_unit = re.compile("([0-9\.]+)([a-zA-Z]+)")
  m = re_num_unit.match(batch_config["bottleneck_delay"])
  rtt_unit = m.group(2)
  bottleneck_delay = float(m.group(1))
  for i in range(num_cca):
    ccas.append(batch_config["transport_prot"+str(i)])
    num_ccas.append(batch_config["num_cca"+str(i)])
    m = re_num_unit.match(batch_config["leaf_delay"+str(i)])
    if m.group(2) != rtt_unit:
      print("ERR: unit mismatch")
      exit()
    rtt = 2*(bottleneck_delay+2*float(m.group(1)))
    rtts.append(str(rtt)+rtt_unit)

  tpt_fifo = None
  tpt_fq = None
  tpt_cebinae = None
  gpt_fifo = None
  gpt_fq = None
  gpt_cebinae = None
  tpt_jfi_fifo = None
  tpt_jfi_fq = None
  tpt_jfi_cebinae = None
  gpt_jfi_fifo = None
  gpt_jfi_fq = None
  gpt_jfi_cebinae = None  

  with open(data_path+"/fifo/digest", 'r') as f:
    lines = f.readlines()
    for line in lines:
      if line.startswith("Avg. Throughput [bps]"):
        line = line.split(":")
        tpt_fifo = line[1].strip("\n ")
      elif line.startswith("Avg. Goodput [bps]"):
        line = line.split(":")
        gpt_fifo = line[1].strip("\n ")        
      elif line.startswith("avg_jfi_bottleneck [computed]:"):
        line = line.split(":")
        tpt_jfi_fifo = line[1].strip("\n ")   
      elif line.startswith("avg_jfi_app [computed]:"):
        line = line.split(":")
        gpt_jfi_fifo = line[1].strip("\n ")           

  with open(data_path+"/fq/digest", 'r') as f:
    lines = f.readlines()
    for line in lines:
      if line.startswith("Avg. Throughput [bps]"):
        line = line.split(":")
        tpt_fq = line[1].strip("\n ")
      elif line.startswith("Avg. Goodput [bps]"):
        line = line.split(":")
        gpt_fq = line[1].strip("\n ")
      elif line.startswith("avg_jfi_bottleneck [computed]:"):
        line = line.split(":")
        tpt_jfi_fq = line[1].strip("\n ")   
      elif line.startswith("avg_jfi_app [computed]:"):
        line = line.split(":")
        gpt_jfi_fq = line[1].strip("\n ")        

  with open(data_path+"/cebinae/digest", 'r') as f:
    lines = f.readlines()
    for line in lines:
      if line.startswith("Avg. Throughput [bps]"):
        line = line.split(":")
        tpt_cebinae = line[1].strip("\n ")
      elif line.startswith("Avg. Goodput [bps]"):
        line = line.split(":")
        gpt_cebinae = line[1].strip("\n ") 
      elif line.startswith("avg_jfi_bottleneck [computed]:"):
        line = line.split(":")
        tpt_jfi_cebinae = line[1].strip("\n ")   
      elif line.startswith("avg_jfi_app [computed]:"):
        line = line.split(":")
        gpt_jfi_cebinae = line[1].strip("\n ")                       

  print_str = '''Bottleneck BW: {0}
Buffer size: {16}
RTTs: {1}
CCAs: {2}
# flows per group: {15}
--- Throughput ---
  FIFO: {3}
  FQ: {4}
  Cebinae: {5}
--- Goodput ---
  FIFO: {6}
  FQ: {7}
  Cebinae: {8}
--- JFI (tpt) ---
  FIFO: {9}
  FQ: {10}
  Cebinae: {11}
--- JFI (gpt) ---
  FIFO: {12}
  FQ: {13}
  Cebinae: {14}  
'''.format(bottleneck_bw,
    rtts,
    ccas,
    tpt_fifo,
    tpt_fq,
    tpt_cebinae,
    gpt_fifo,
    gpt_fq,
    gpt_cebinae,
    tpt_jfi_fifo,
    tpt_jfi_fq,
    tpt_jfi_cebinae,
    gpt_jfi_fifo,
    gpt_jfi_fq,
    gpt_jfi_cebinae,
    num_ccas,
    buf_size
  )
  print(print_str)

@timeit
def plot_fig1(data_dir):
  cwd = os.getcwd()
  if not os.path.isabs(data_dir):
    data_dir = (cwd+"/"+data_dir)
  print("data_dir: {}".format(data_dir))
  if not os.path.isdir(data_dir):
    print("ERR: not dir!")
    exit()

  gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "figure1.eps"

set size 1,0.618 
set border 3
set tics nomirror

set nologscale x

set key reverse Left
set key at graph 0.675,1.0
set key font ",16"
set key maxrows 2
set key samplen 2
set key width -5

set xlabel "Time [s]"
set ylabel 'Goodput [MBps]'

set xrange [1:60]
set xtics 0,5,60

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

plot "fifo/app_tpt_1000000.dat" using ($1/1000000) title "FIFO (RTT=20.4ms)" with lines lw 5 dt 3 lc rgb myred, \\
	 "fifo/app_tpt_1000000.dat" using ($2/1000000) title "FIFO (RTT=40ms)" with lines lw 5 dt 3 lc rgb myblue, \\
	 "cebinae/app_tpt_1000000.dat" using ($1/1000000) title "Cebinae (RTT=20.4ms)" with lines lw 5 dt 1 lc rgb myred, \\
	 "cebinae/app_tpt_1000000.dat" using ($2/1000000) title "Cebinae (RTT=40ms)" with lines lw 5 dt 1 lc rgb myblue,
'''

  with open(data_dir+"/plot.gp", "w") as gp_file:
    gp_file.write(gp_str)

  os.chdir(data_dir)
  cmd = "gnuplot plot.gp"
  print(cmd)
  subprocess.call(cmd.split())

@timeit
def plot_time_tpt(data_path, w_total):
  cwd = os.getcwd()
  if not os.path.isabs(data_path):
    data_path = (cwd+"/"+data_path)
  print("data_path: {0}".format(data_path))
  if not os.path.isfile(data_path):
    print("ERR: not data file!")
    exit()
  data_dir = os.path.dirname(data_path)
  print("data_dir: {}".format(data_dir))
  file_name = os.path.basename(data_path)
  print("file_name: {}".format(file_name))

  gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "graph.eps"

set size 1,0.618 
set border 3
set tics nomirror

set nologscale x

set key font ",16"
set key samplen 2
set key maxrows 3

set xlabel "Time [s]"
set ylabel 'Rate [MBps]'

set xrange [1:100]
set xtics 0,5,100

myred = '#A90533'
mypink = '#f89588'
myblue = '#63b2ee'
mygreen = '#76da91'
mypurple = '#9987ce'
myyellow = '#F4B400'
myblack = '#000000'
myviolet = '#8F00FF'
myorange = '#FFA500'
mydarkgreen = '#065535'
'''

  curves = []
  with open(data_path, "r") as f:
    lines = f.readlines()
    num_flows = len(lines[0].split())-1
  
    # Define enough styles
    colors = ['myred', 'mypink', 'myblue', 'mygreen', 'mypurple', 'myyellow', 'myblack', 'myviolet', 'myorange', 'mydarkgreen']
    point_types = [2, 4, 6, 8, 10, 12, 14, 5, 7, 9, 11, 13, 15]
    num_ls = 0
    color_type = 0
    while num_ls <= num_flows:
      for point_type in point_types:
        num_ls += 1
        gp_str += ("set style line {0} lc rgb {1} dt 1 lw 3 pt {2}\n".format(num_ls, colors[color_type], point_type))
      color_type += 1

    gp_str += "plot "
    for i in range(num_flows):
      curves.append(("\""+file_name+"\""+" using ($"+str(i+1)+"/1000000) title \""+str(i)+"\" with lp ls "+str(i+1)+","))
    if w_total:
      curves.append(("\""+file_name+"\""+" using ($"+str(num_flows+1)+"/1000000) title \"agg.\" with lp ls "+str(num_flows+1)+","))
  for i in range(len(curves)-1):
    gp_str += (curves[i]+"\\\n")
  gp_str += curves[-1]

  with open(data_dir+"/plot.gp", "w") as gp_file:
    gp_file.write(gp_str)

  os.chdir(data_dir)
  cmd = "gnuplot plot.gp"
  print(cmd)
  subprocess.call(cmd.split())


if __name__ == '__main__':

  parser = argparse.ArgumentParser()
  subprsr = parser.add_subparsers(dest="cmd")

  ns_subprsr = subprsr.add_parser("ns")
  ns_subsubprsr = ns_subprsr.add_subparsers(dest="ns_cmd")

  ns_configure_prsr = ns_subsubprsr.add_parser("configure")
  ns_configure_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  ns_build_prsr = ns_subsubprsr.add_parser("build")

  ns_validate_prsr = ns_subsubprsr.add_parser("validate")
  ns_validate_prsr.add_argument("-p", "--profile", type=str, required=False, default="default", choices=["default", "debug", "optimized"], help="Build profile")

  ns_subsubprsr.add_parser("kill")

  ns_run_instance_prsr = ns_subsubprsr.add_parser("run_instance")
  ns_run_instance_prsr.add_argument("-c", "--config", type=str, required=True, help="Absolute or relative path (w.r.t. ns/configs) of Json config file")
  ns_run_instance_prsr.add_argument("--gdb", action="store_true", help="Whether to enable gdb")

  ns_run_batch_prsr = ns_subsubprsr.add_parser("run_batch")
  ns_run_batch_prsr.add_argument("-c", "--config", type=str, required=True, help="Absolute or relative path (w.r.t. ns/configs) of Json config file")
  ns_run_batch_prsr.add_argument("--parallel", action="store_true", help="Whether to parallize the execution of the experiment instances within a batch")

  ns_run_batches_prsr = ns_subsubprsr.add_parser("run_batches") # Run all run_batch configs under the specified dir sequentially
  ns_run_batches_prsr.add_argument("-c", "--config_dir", type=str, required=True, help="Absolute or relative path (w.r.t. ns/configs) of the directory containing Json config files")
  ns_run_batches_prsr.add_argument("--parallel", action="store_true", help="Whether to execute with multiprocessing")  

  ns_run_instances_prsr = ns_subsubprsr.add_parser("run_instances") # Run all configs (decompose each batch into instances, if any) under the specified dir sequentially
  ns_run_instances_prsr.add_argument("-c", "--config_dir", type=str, required=True, help="Absolute or relative path (w.r.t. ns/configs) of the directory containing Json config files")
  ns_run_instances_prsr.add_argument("--parallel", action="store_true", help="Whether to execute with multiprocessing")  

  ns_run_clear_prsr = ns_subsubprsr.add_parser("clear")

  ns_run_prerequisite_prsr = ns_subsubprsr.add_parser("prerequisite")

  parse_subprsr = subprsr.add_parser("parse")
  parse_subprsr.add_argument("--target", type=str, required=True, choices=["bigtbl"], help="Parse target")
  parse_subprsr.add_argument("--data_path", type=str, required=True, help="Absolute or relative path (w.r.t. pwd) of data file or directory")  

  plot_subprsr = subprsr.add_parser("plot")
  plot_subprsr.add_argument("--plot_target", type=str, required=True, choices=["fig1", "time_tpt"], help="Plot target")
  plot_subprsr.add_argument("--data_path", type=str, required=True, help="Absolute or relative path (w.r.t. pwd) of plotting data file or directory")
  plot_subprsr.add_argument("--w_total", action="store_true", help="Whether to plot total line used by time_tpt target")

  tofino_subprsr = subprsr.add_parser("tofino")

  args = parser.parse_args()
  if args.cmd == "ns":
    if args.ns_cmd == "validate":
      ns_validate(args.profile)
    if args.ns_cmd == "configure":
      ns_configure(args.profile)
    if args.ns_cmd == "build":
      ns_build()
    elif args.ns_cmd == "run_instance":
      ns_run_instance(args.config, args.gdb)
    elif args.ns_cmd == "run_batch":
      ns_run_batch(args.config, args.parallel)
    elif args.ns_cmd == "run_batches":
      ns_run_batches(args.config_dir, args.parallel)
    elif args.ns_cmd == "run_instances":
      ns_run_instances(args.config_dir, args.parallel)            
    elif args.ns_cmd == "clear":
      ns_clear()
    elif args.ns_cmd == "kill":
      ns_kill()
    elif args.ns_cmd == "prerequisite":
      ns_prerequisite()      
  elif args.cmd == "parse":
    if args.target == "bigtbl":
      parse_bigtbl(args.data_path)
  elif args.cmd == "plot":
    if args.plot_target == "fig1":
      plot_fig1(args.data_path)
    if args.plot_target == "time_tpt":
      plot_time_tpt(args.data_path, args.w_total)
  elif args.cmd == "tofino":
    pass

