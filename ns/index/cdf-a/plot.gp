
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

# "heavy_filter.data" using 1:2 title "Heavy (selective)" with lp dt 3 lw 6 lc rgb myblue

plot "cdf.dat" i 0 u ($1/1000000):2 title "FIFO" with l dt 1 lw 8 lc rgb myblue,     "" i 1 u ($1/1000000):2 title "Cebinae" with l dt 1 lw 8 lc rgb myred

#set key maxrows 3
