
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "graph.eps"

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'
mygreen = '#34a905'

set size 1,0.618

set style fill pattern
set style histogram clustered

set xlabel "Flow index"
set ylabel "Goodput [Mbps]" offset 1
# set logscale y 10

set key at graph 0.9,0.95
set key maxrows 1
set key samplen 3

set tics out nomirror
set grid ytics

#unset xtics

plot "gpts.dat" i 0 u ($2):xtic(1) t "Ideal" w histograms lw 2 lc rgb mygreen fs pattern 4,\
     "" i 1 u ($2):xtic(1) t "FIFO" w histograms lw 2 lc rgb myblue fs pattern 5,\
     "" i 2 u ($2):xtic(1) t "Cebinae" w histograms lw 2 lc rgb myred fs pattern 2,\
