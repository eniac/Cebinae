reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "graph.eps"

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

set size 1,0.618

set style fill pattern
set style histogram clustered

set xlabel "Flow index"
set ylabel "Goodput [Mbps]"
set logscale y

set key at graph 0.8,0.95
set key maxrows 1
set key samplen 3

set boxwidth 1.0

set tics out nomirror
set grid ytics

plot "gpt.dat" i 0 u ($2/1000000):xtic(1) t "FIFO" w histograms lc rgb myblue fs pattern 4,\
     "" i 1 u ($2/1000000):xtic(1) t "Cebinae" w histograms lc rgb myred fs pattern 2
