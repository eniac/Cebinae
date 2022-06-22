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

def print_cmd(cmd):
  print("$ {}".format(cmd))

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
    print_cmd(cmd)
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
    print_cmd(cmd)
    subprocess.call(cmd.split())

@timeit
def ns_build():
  cwd = os.getcwd()
  print("cwd: {}".format(cwd))

  os.chdir(cwd+"/ns")
  cmd = "./waf build"
  print_cmd(cmd)
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
    print_cmd(cmd)
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
    print_cmd(cmd)
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
  print_cmd(cmd)
  subprocess.call(cmd.split())

@timeit
def plot_fig7(data_dir):
  cwd = os.getcwd()
  if not os.path.isabs(data_dir):
    data_dir = (cwd+"/"+data_dir)
  print("data_dir: {}".format(data_dir))
  if not os.path.isdir(data_dir):
    print("ERR: not dir!")
    exit()

  gpt_str = ""

  # Parse gpt data
  with open(data_dir+"/fifo/digest", "r") as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
      if "=== avg_tpt_app[*] ===" in line:
        i += 1
        while "Avg. Goodput [bps]" not in lines[i]:
          line = lines[i].strip()
          gpt_str += (line+"\n")
          i += 1
        break
  gpt_str += "\n\n"
  with open(data_dir+"/cebinae/digest", "r") as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
      if "=== avg_tpt_app[*] ===" in line:
        i += 1
        while "Avg. Goodput [bps]" not in lines[i]:
          line = lines[i].strip()
          gpt_str += (line+"\n")
          i += 1
        break    
  with open(data_dir+"/gpt.dat", "w") as f:
    f.write(gpt_str)

  gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fig7.eps"

myred = '#A90533'
myblue = '#004785'

set size 1,0.618

set style fill pattern
set style histogram clustered

set xlabel "Flow index"
set ylabel "Goodput [Mbps]"
set logscale y

set key at graph 0.8,0.95
set key maxrows 1
set key samplen 3
set key width -5

set boxwidth 1.0

set tics out nomirror
set grid ytics

plot "gpt.dat" i 0 u ($2/1000000):xtic(1) t "FIFO+TailDrop" w histograms lc rgb myblue fs pattern 4,\\
     "" i 1 u ($2/1000000):xtic(1) t "Cebinae" w histograms lc rgb myred fs pattern 2
'''

  with open(data_dir+"/plot.gp", "w") as gp_file:
    gp_file.write(gp_str)

  os.chdir(data_dir)
  cmd = "gnuplot plot.gp"
  print_cmd(cmd)
  subprocess.call(cmd.split())

@timeit
def plot_fig8(data_dir):
  cwd = os.getcwd()
  if not os.path.isabs(data_dir):
    data_dir = (cwd+"/"+data_dir)
  print("data_dir: {}".format(data_dir))
  if not os.path.isdir(data_dir):
    print("ERR: not dir!")
    exit()

  gpt_str = ""
  jfi_str = ""

  fifo_gpt = ""
  fifo_jfi = ""
  fq_gpt = ""
  fq_jfi = ""
  with open(data_dir+"/fifo/digest", "r") as f:
    lines = f.readlines()
    for line in lines:
      if "Avg. Goodput [bps]" in line:
        fifo_gpt = line.split(":")[1].strip()
      if "avg_jfi_app [computed]" in line:
        fifo_jfi = line.split(":")[1].strip()
  with open(data_dir+"/fq/digest", "r") as f:
    lines = f.readlines()
    for line in lines:
      if "Avg. Goodput [bps]" in line:
        fq_gpt = line.split(":")[1].strip()
      if "avg_jfi_app [computed]" in line:
        fq_jfi = line.split(":")[1].strip()

  thresholds = [0.01, 0.1, 0.2, 0.4, 0.8, 1.0]
  suffix = ["001", "010", "020", "040", "080", "100"]
  for i in range(len(thresholds)):
    with open(data_dir+"/cebinae-"+suffix[i]+"/digest", "r") as f:
      lines = f.readlines()
      for line in lines:
        if "Avg. Goodput [bps]" in line:
          gpt_str += ("{0} {1}\n".format(thresholds[i], line.split(":")[1].strip()))
        if "avg_jfi_app [computed]" in line:
          jfi_str += ("{0} {1}\n".format(thresholds[i], line.split(":")[1].strip()))

  with open(data_dir+"/gpt.dat", "w") as f:
    f.write(gpt_str)
  with open(data_dir+"/jfi.dat", "w") as f:
    f.write(jfi_str)    

  gpt_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fig8b.eps"

set logscale x
set size 0.5,0.5

set tics nomirror
#set key top right reverse Left
#set key font ",16"
unset key
set border 3

set xlabel "Thresholds [%]"
set ylabel 'Goodput [MBps]'

set logscale x
set xrange [1:100]
set ytics 0,20,101
set yrange [0:101]

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

set grid

gpt_fq = {0}
gpt_fifo = {1}

set arrow from 1,gpt_fifo to 100,gpt_fifo lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.97,0.98 "FIFO" front right textcolor rgb mygrey font "Helvetica,16"

set arrow from 1,gpt_fq to 100,gpt_fq lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.91,0.87 "FQ" front right textcolor rgb mygrey font "Helvetica,16"

plot "gpt.dat" using ($1*100):($2/1000000) with linespoints lw 5 lc rgb myred
'''.format(fq_gpt, fifo_gpt)

  jfi_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fig8a.eps"

set logscale x
set size 0.5,0.5

set tics nomirror
#set key top right reverse Left
#set key font ",16"
unset key
set border 3

set grid

set xlabel "Thresholds [%]"
set ylabel 'JFI'

set logscale x
set xrange [1:100]
set ytics 0,0.2,1.0
set yrange [0:1]

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

#set format y '%.1f'

jfi_fq = {0}
jfi_fifo = {1}

set arrow from 1,jfi_fifo to 100,jfi_fifo lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.2,0.83 "FIFO" front right textcolor rgb mygrey font "Helvetica,16"

set arrow from 1,jfi_fq to 100,jfi_fq lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.2,0.95 "FQ" front right textcolor rgb mygrey font "Helvetica,16"

plot "jfi.dat" using ($1*100):($2) with linespoints lw 5 lc rgb myred
'''.format(fq_jfi, fifo_jfi)

  with open(data_dir+"/plot_gpt.gp", "w") as gp_file:
    gp_file.write(gpt_gp_str)
  with open(data_dir+"/plot_jfi.gp", "w") as gp_file:
    gp_file.write(jfi_gp_str)

  os.chdir(data_dir)
  cmds = [
    "gnuplot plot_gpt.gp",
    "gnuplot plot_jfi.gp"
  ]
  for cmd in cmds:
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
  print_cmd(cmd)
  subprocess.call(cmd.split())

@timeit
def plot_gpt_cdf(data_path, w_fq=False):
  cwd = os.getcwd()
  if not os.path.isabs(data_path):
    data_path = (cwd+"/"+data_path)
  print("data_path: {0}".format(data_path))
  if not os.path.isdir(data_path):
    print("ERR: not dir!")
    exit()

  fifo_gpts = []
  with open(data_path+"/fifo/digest", "r") as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
      if "=== avg_tpt_app[*] ===" in line:
        i += 1
        while "Avg. Goodput [bps]" not in lines[i]:
          gpt = lines[i].split()[1].strip()
          fifo_gpts.append(float(gpt))
          i += 1
        break
  fifo_gpts = sorted(fifo_gpts)
  num_flows = len(fifo_gpts)
  fifo_cdf_str = (str(fifo_gpts[0])+" 0.0\n")
  for num_flow in range(num_flows):
    fifo_cdf_str += (str(fifo_gpts[num_flow])+" "+str((num_flow+1)/num_flows)+"\n")

  cebinae_gpts = []
  with open(data_path+"/cebinae/digest", "r") as f:
    lines = f.readlines()
    for i, line in enumerate(lines):
      if "=== avg_tpt_app[*] ===" in line:
        i += 1
        while "Avg. Goodput [bps]" not in lines[i]:
          gpt = lines[i].split()[1].strip()
          cebinae_gpts.append(float(gpt))
          i += 1
        break
  cebinae_gpts = sorted(cebinae_gpts)
  num_flows = len(cebinae_gpts)
  cebinae_cdf_str = (str(cebinae_gpts[0])+" 0.0\n")
  for num_flow in range(num_flows):
    cebinae_cdf_str += (str(cebinae_gpts[num_flow])+" "+str((num_flow+1)/num_flows)+"\n")

  with open(data_path+"/cdf.dat", "w") as f:
    f.write(fifo_cdf_str)
    f.write("\n\n")
    f.write(cebinae_cdf_str)

  gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "graph.eps"

set xlabel "Goodput [Mbps]"
set ylabel "CDF" offset 1
set size 1,0.618 
set tics nomirror

set logscale x 2
unset logscale x
set nologscale x
set nologscale y

set size 0.5,0.5

set yrange [0:1]

set key samplen 2
set border 3
set key font ",16"
set key at graph 1.0,0.45

myred = '#A90533'
myblue = '#004785'
mygray = 'grey70'
mygreen = '#0F9D58'
myyellow = '#F4B400'
set format y '%.1f'

set grid

plot "cdf.dat" i 0 u ($1/1000000):2 title "FIFO" with l dt 1 lw 8 lc rgb myblue,\
     "" i 1 u ($1/1000000):2 title "Cebinae" with l dt 1 lw 8 lc rgb myred
'''

  with open(data_path+"/plot.gp", "w") as f:
    f.write(gp_str)
  
  os.chdir(data_path)
  cmd = "gnuplot plot.gp"
  print_cmd(cmd)
  subprocess.call(cmd.split())

@timeit
def plot_rtts(data_path, w_fq):
  cwd = os.getcwd()
  if not os.path.isabs(data_path):
    data_path = (cwd+"/"+data_path)
  print("data_path: {0}".format(data_path))
  if not os.path.isdir(data_path):
    print("ERR: not dir!")
    exit()
  
  num_pairs = None
  batch_config = None
  with open(data_path+"/fifo-0/config.json", "r") as f:
    batch_config=json.loads(f.read())
  if w_fq:
    num_pairs = int(batch_config['batch_size']/3)
  else:
    num_pairs = int(batch_config['batch_size']/2)

  rtts_base = []
  rtts_vary = []
  jfis_fifo = []
  jfis_cb = []
  jfis_fq = []  
  gpts_fifo = []
  gpts_cb = []  
  gpts_fq = []    
  for i in range(num_pairs):
    gpt_fifo = None
    gpt_cb = None
    jfi_fifo = None
    jfi_cb = None
    x_rtt = None

    with open(data_path+"/fifo-"+str(i)+"/digest", "r") as f:
      lines = f.readlines()
      for line in lines:
        if line.startswith("Avg. Goodput [bps]"):
          line = line.split(":")
          gpt_fifo = line[1].strip("\n ")
        elif line.startswith("avg_jfi_app [computed]:"):
          line = line.split(":")
          jfi_fifo = line[1].strip("\n ")   
    with open(data_path+"/cebinae-"+str(i)+"/digest", "r") as f:
      lines = f.readlines()
      for line in lines:
        if line.startswith("Avg. Goodput [bps]"):
          line = line.split(":")
          gpt_cb = line[1].strip("\n ")
        elif line.startswith("avg_jfi_app [computed]:"):
          line = line.split(":")
          jfi_cb = line[1].strip("\n ")   
    with open(data_path+"/fq-"+str(i)+"/digest", "r") as f:
      lines = f.readlines()
      for line in lines:
        if line.startswith("Avg. Goodput [bps]"):
          line = line.split(":")
          gpt_fq = line[1].strip("\n ")
        elif line.startswith("avg_jfi_app [computed]:"):
          line = line.split(":")
          jfi_fq = line[1].strip("\n ")   

    re_num_unit = re.compile("([0-9\.]+)([a-zA-Z]+)")
    m = re_num_unit.match(batch_config["bottleneck_delay"])
    rtt_unit = m.group(2)
    bottleneck_delay = float(m.group(1))   
    num_cca = batch_config["num_cca"]
    if num_cca != 2:
      print("num_cca != 2")
      exit()

    # 0 is always the base
    m = re_num_unit.match(batch_config["leaf_delay0"])
    if m.group(2) != rtt_unit:
      print("ERR: unit mismatch")
      exit()
    rtt = 2*(bottleneck_delay+2*float(m.group(1)))
    rtts_base.append(str(rtt)+rtt_unit)
    m = re_num_unit.match(batch_config["leaf_delay1"][i])
    if m.group(2) != rtt_unit:
      print("ERR: unit mismatch")
      exit()
    rtt = 2*(bottleneck_delay+2*float(m.group(1)))
    rtts_vary.append(str(rtt))
    # rtts_vary.append(str(rtt)+rtt_unit)

    jfis_fifo.append(jfi_fifo)
    jfis_cb.append(jfi_cb)
    jfis_fq.append(jfi_fq)
    gpts_fifo.append(gpt_fifo)
    gpts_cb.append(gpt_cb)
    gpts_fq.append(gpt_fq)

  print(rtts_base)
  print(rtts_vary)
  print(jfis_fifo)
  print(jfis_cb)
  print(jfis_fq)
  print(gpts_fifo)
  print(gpts_cb)
  print(gpts_fq)

  with open(data_path+"/jfi.dat", "w") as f:
    for i in range(len(jfis_fifo)):
      if w_fq:
        f.write(rtts_vary[i]+" "+str(jfis_fifo[i])+" "+str(jfis_fq[i])+" "+str(jfis_cb[i])+"\n")
      else:
        f.write(rtts_vary[i]+" "+str(jfis_fifo[i])+" "+str(jfis_cb[i])+"\n")
  with open(data_path+"/gpt.dat", "w") as f:
    for i in range(len(jfis_fifo)):
      if w_fq:
        f.write(rtts_vary[i]+" "+str(gpts_fifo[i])+" "+str(gpts_fq[i])+" "+str(gpts_cb[i])+"\n")
      else:
        f.write(rtts_vary[i]+" "+str(gpts_fifo[i])+" "+str(gpts_cb[i])+"\n")

  gpt_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "rtts-b.eps"

set logscale x
set size 0.5,0.5

set tics nomirror
set key at graph 1.0,0.5
set key font ",16"
set border 3

set xlabel "RTT [ms]"
set ylabel 'Goodput [MBps]'

set logscale x 2
set ytics 0,100,401
set yrange [0:401]

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

set grid

plot "gpt.dat" using ($1):($2/1000000) title "FIFO" with linespoints pt 2 ps 1.5 lw 5 lc rgb myblue,\\
     "gpt.dat" using ($1):($3/1000000) title "FQ" with linespoints pt 4 ps 1.5 lw 5 lc rgb mygrey,\\
     "gpt.dat" using ($1):($4/1000000) title "Cebinae" with linespoints pt 6 ps 1.5 lw 5 lc rgb myred
'''

  jfi_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "rtts-a.eps"

set logscale x
set size 0.5,0.5

set tics nomirror
set key at graph 1.0,0.5
set key font ",16"
set border 3

set grid

set xlabel "RTT [ms]"
set ylabel 'JFI'

set logscale x 2
#set xrange [1:100]
set ytics 0,0.2,1.0
set yrange [0:1]

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

#set format y '%.1f'

plot "jfi.dat" using ($1):($2) title "FIFO" with linespoints pt 2 ps 1.5 lw 5 lc rgb myblue,\\
     "jfi.dat" using ($1):($3) title "FQ"  with linespoints pt 4 ps 1.5 lw 5 lc rgb mygrey,\\
     "jfi.dat" using ($1):($4) title "Cebinae" with linespoints pt 6 ps 1.5 lw 5 lc rgb myred
'''

  with open(data_path+"/plot_gpt.gp", "w") as gp_file:
    gp_file.write(gpt_gp_str)
  with open(data_path+"/plot_jfi.gp", "w") as gp_file:
    gp_file.write(jfi_gp_str)

  cmd = "cat "+data_path+"/jfi.dat"
  print_cmd(cmd)
  subprocess.call(cmd.split())
  cmd = "cat "+data_path+"/gpt.dat"
  print_cmd(cmd)
  subprocess.call(cmd.split())  

  os.chdir(data_path)
  cmds = [
    "gnuplot plot_gpt.gp",
    "gnuplot plot_jfi.gp"
  ]
  for cmd in cmds:
    subprocess.call(cmd.split())

def get_loc(target):

  if target == "p4":
    # find . -name *.p4 | xargs wc -l
    cmd_files = "find . -name *.p4"
    cmd_count = "xargs wc -l"

    p1 = subprocess.Popen(cmd_files.split(), stdout=subprocess.PIPE)
    p2 = subprocess.Popen(cmd_count.split(), stdin=p1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p1.stdout.close()  # Necessary for p1 to receive a SIGPIPE if p2 exits
    stdout, stderr = p2.communicate()

    total_loc = stdout.split()[-2]
    print("{0} loc: {1}".format(target, total_loc))
  elif target == "cp":
    cmd_files = 'find tofino_prototype/ -type f \( -name "*.hpp" -o -name "*.cpp" -o -name "*.c" -o -name "*.h" \)'
    cmd_count = "xargs wc -l"

    p1 = subprocess.Popen(cmd_files, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p2 = subprocess.Popen(cmd_count.split(), stdin=p1.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p1.stdout.close()
    stdout, stderr = p2.communicate()
    print(stdout)
  elif target == "ns":
    files = ["ns/src/traffic-control/model/cebinae-queue-disc.cc", "ns/src/traffic-control/model/cebinae-queue-disc.h", ]
    cmd_count = "wc -l"
    for file in files:
      cmd = cmd_count + " " + file
      p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
      stdout, stderr = p.communicate()
      print(stdout.strip())

import statistics
import numpy as np
import scipy.stats
def mean_confidence_interval(data, confidence=0.9):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n-1)
    return m, m-h, m+h
def plot_top_detection(data_path="flow_table/camera_ready_plot"):

  stage2interval2fnrfpr_slot2048_dict = None
  stage2slotnum2fnrfpr_interval100ms_dict = None

  with open(data_path+'/slot2048.json', 'r') as f:
    stage2interval2fnrfpr_slot2048_dict = json.loads(f.read())

  with open(data_path+'/interval100ms.json', 'r') as f:
    stage2slotnum2fnrfpr_interval100ms_dict = json.loads(f.read())

  stages = [1, 2, 4]  
  intervals = [str(i) for i in range(10,101,10)]
  with open(data_path+"/fixed_slot_fpr.dat", "w") as f:
    for stage in stages:
      interval2fnrfpr = stage2interval2fnrfpr_slot2048_dict[str(stage)]
      for interval in intervals:
        # mean_val = statistics.mean(interval2fnrfpr[interval]["fpr"])
        # std_val = statistics.stdev(interval2fnrfpr[interval]["fpr"])
        mean_val, lo_val, hi_val = mean_confidence_interval(interval2fnrfpr[interval]["fpr"])
        f.write(str(interval)+" "+str(mean_val)+" "+str(lo_val)+" "+str(hi_val)+"\n")
      f.write("\n\n")

  with open(data_path+"/fixed_slot_fnr.dat", "w") as f:
    for stage in stages:
      interval2fnrfpr = stage2interval2fnrfpr_slot2048_dict[str(stage)]
      for interval in intervals:
        # mean_val = statistics.mean(interval2fnrfpr[interval]["fnr"])
        # std_val = statistics.stdev(interval2fnrfpr[interval]["fnr"])
        mean_val, lo_val, hi_val = mean_confidence_interval(interval2fnrfpr[interval]["fnr"])
        # f.write(str(interval)+" "+str(mean_val)+" "+str(std_val)+"\n")
        f.write(str(interval)+" "+str(mean_val)+" "+str(lo_val)+" "+str(hi_val)+"\n")
      f.write("\n\n")

  slots = [512, 1024, 2048, 4096]
  with open(data_path+"/fixed_interval_fpr.dat", "w") as f:
    for stage in stages:
      slotnum2fnrfpr = stage2slotnum2fnrfpr_interval100ms_dict[str(stage)]
      for slot in slots:
        mean_val = statistics.mean(slotnum2fnrfpr[str(slot)]["fpr"])
        std_val = statistics.stdev(slotnum2fnrfpr[str(slot)]["fpr"])
        f.write(str(slot)+" "+str(mean_val)+" "+str(std_val)+"\n")
      f.write("\n\n")        

  with open(data_path+"/fixed_interval_fnr.dat", "w") as f:
    for stage in stages:
      slotnum2fnrfpr = stage2slotnum2fnrfpr_interval100ms_dict[str(stage)]
      for slot in slots:
        mean_val = statistics.mean(slotnum2fnrfpr[str(slot)]["fnr"])
        std_val = statistics.stdev(slotnum2fnrfpr[str(slot)]["fnr"])
        f.write(str(slot)+" "+str(mean_val)+" "+str(std_val)+"\n")
      f.write("\n\n")
  
  fixed_slot_fpr_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fpr_fixed_slot.eps"

set size 0.5,0.5

set tics nomirror
set key at graph 1.0,1.0
set key font ",16"
set border 3
set key samplen 2

set grid

set xlabel "Round interval [ms]"
set ylabel 'FPR [10^{-4}]' offset 1

set xrange [0:101]
set xtics 0,20,102

myred = '#A90533'
myblue = '#004785'
mygreen = '#34a905'

# Picked from https://mdigi.tools/color-shades/
myblue_shades = '#e5f3ff'
myred_shades = '#fee6ed'
mygreen_shades = '#edfee6'

plot "fixed_slot_fpr.dat" i 0 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb myblue_shades, \\
     '' i 0 using 1:($2*10000) w l lw 4 lc rgb myblue title "1 stage",\\
     "fixed_slot_fpr.dat" i 1 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb myred_shades, \\
     '' i 1 using 1:($2*10000) w l lw 4 lc rgb myred title "2 stage",\\
     "fixed_slot_fpr.dat" i 2 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb mygreen_shades, \\
     '' i 2 using 1:($2*10000) w l lw 4 lc rgb mygreen title "4 stage",\\
'''

  fixed_slot_fnr_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fnr_fixed_slot.eps"

set size 0.5,0.5

set tics nomirror
set key at graph 1.0,1.0
set key font ",16"
set border 3
set key samplen 2

set grid

set xlabel "Round interval [ms]"
set ylabel 'FNR' offset 1

set xrange [0:101]
set xtics 0,20,102

myred = '#A90533'
myblue = '#004785'
mygreen = '#34a905'

# Picked from https://mdigi.tools/color-shades/
myblue_shades = '#e5f3ff'
myred_shades = '#fee6ed'
mygreen_shades = '#edfee6'

plot "fixed_slot_fnr.dat" i 0 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb myblue_shades, \\
     '' i 0 using 1:($2) w l lw 4 lc rgb myblue title "1 stage",\\
     "fixed_slot_fpr.dat" i 1 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb myred_shades, \\
     '' i 1 using 1:($2) w l lw 4 lc rgb myred title "2 stage",\\
     "fixed_slot_fpr.dat" i 2 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb mygreen_shades, \\
     '' i 2 using 1:($2) w l lw 4 lc rgb mygreen title "4 stage",\\
'''

  fixed_interval_fpr_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fpr_fixed_interval.eps"

set size 0.5,0.5

set tics nomirror
set key at graph 1.0,1.0
set key font ",16"
set border 3
set key samplen 2

set grid

set xlabel "Slot #"
set ylabel 'FPR [10^{-4}]' offset 1

set xrange [0:101]
set xtics 0,20,102

myred = '#A90533'
myblue = '#004785'
mygreen = '#34a905'

# Picked from https://mdigi.tools/color-shades/
myblue_shades = '#e5f3ff'
myred_shades = '#fee6ed'
mygreen_shades = '#edfee6'

plot "fixed_interval_fpr.dat" i 0 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb myblue_shades, \\
     '' i 0 using 1:($2*10000) w l lw 4 lc rgb myblue title "1 stage",\\
     "fixed_slot_fpr.dat" i 1 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb myred_shades, \\
     '' i 1 using 1:($2*10000) w l lw 4 lc rgb myred title "2 stage",\\
     "fixed_slot_fpr.dat" i 2 using 1:($2+$3)*10000:($2-$3)*10000 with filledcurve notitle fc rgb mygreen_shades, \\
     '' i 2 using 1:($2*10000) w l lw 4 lc rgb mygreen title "4 stage",\\
'''
  fixed_interval_fnr_gp_str = '''
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fnr_fixed_interval.eps"

set size 0.5,0.5

set tics nomirror
set key at graph 1.0,1.0
set key font ",16"
set border 3
set key samplen 2

set grid

set xlabel "Slot #"
set ylabel 'FNR' offset 1

set xrange [0:101]
set xtics 0,20,102

myred = '#A90533'
myblue = '#004785'
mygreen = '#34a905'

# Picked from https://mdigi.tools/color-shades/
myblue_shades = '#e5f3ff'
myred_shades = '#fee6ed'
mygreen_shades = '#edfee6'

plot "fixed_interval_fnr.dat" i 0 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb myblue_shades, \\
     '' i 0 using 1:($2) w l lw 4 lc rgb myblue title "1 stage",\\
     "fixed_slot_fpr.dat" i 1 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb myred_shades, \\
     '' i 1 using 1:($2) w l lw 4 lc rgb myred title "2 stage",\\
     "fixed_slot_fpr.dat" i 2 using 1:($2+$3):($2-$3) with filledcurve notitle fc rgb mygreen_shades, \\
     '' i 2 using 1:($2) w l lw 4 lc rgb mygreen title "4 stage",\\
'''

  with open(data_path+"/plot_fixed_slot_fpr.gp", "w") as gp_file:
    gp_file.write(fixed_slot_fpr_gp_str)  
  with open(data_path+"/plot_fixed_slot_fnr.gp", "w") as gp_file:
    gp_file.write(fixed_slot_fnr_gp_str)  
  with open(data_path+"/plot_fixed_interval_fpr.gp", "w") as gp_file:
    gp_file.write(fixed_interval_fpr_gp_str)  
  with open(data_path+"/plot_fixed_interval_fnr.gp", "w") as gp_file:
    gp_file.write(fixed_interval_fnr_gp_str)          


  os.chdir(data_path)
  cmds = [
    "gnuplot plot_fixed_slot_fpr.gp",
    "gnuplot plot_fixed_slot_fnr.gp",
    "gnuplot plot_fixed_interval_fpr.gp",
    "gnuplot plot_fixed_interval_fnr.gp",    
  ]
  for cmd in cmds:
    subprocess.call(cmd.split())

if __name__ == '__main__':

  parser = argparse.ArgumentParser()
  subprsr = parser.add_subparsers(dest="cmd")

  loc_subprsr = subprsr.add_parser("loc")
  loc_subprsr.add_argument("-t", "--target", required=True, choices=["p4", "cp", "ns"], type=str, help="Traget set of files")

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
  plot_subprsr.add_argument("--plot_target", type=str, required=True, choices=["fig1", "fig7", "fig8", "time_tpt", "gpt_cdf", "rtts", "top_detection"], help="Plot target")
  plot_subprsr.add_argument("--data_path", type=str, required=True, help="Absolute or relative path (w.r.t. pwd) of plotting data file or directory")
  plot_subprsr.add_argument("--w_total", action="store_true", help="Whether to plot total line used by time_tpt target")
  plot_subprsr.add_argument("--w_fq", action="store_true", help="Whether to plot fq line used by gpt_cdf target")  

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
  elif args.cmd == "loc":
    get_loc(args.target)
  elif args.cmd == "parse":
    if args.target == "bigtbl":
      parse_bigtbl(args.data_path)
  elif args.cmd == "plot":
    if args.plot_target == "fig1":
      plot_fig1(args.data_path)
    if args.plot_target == "fig7":
      plot_fig7(args.data_path)  
    if args.plot_target == "fig8":
      plot_fig8(args.data_path)            
    if args.plot_target == "time_tpt":
      plot_time_tpt(args.data_path, args.w_total)
    if args.plot_target == "gpt_cdf":
      plot_gpt_cdf(args.data_path, args.w_fq)
    if args.plot_target == "rtts":
      plot_rtts(args.data_path, args.w_fq)   
    if args.plot_target == "top_detection":
      plot_top_detection()        
  elif args.cmd == "tofino":
    pass

