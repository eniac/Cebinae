
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

plot "fifo/app_tpt_1000000.dat" using ($1/1000000) title "FIFO (RTT=20.4ms)" with lines lw 5 dt 3 lc rgb myred, \
	 "fifo/app_tpt_1000000.dat" using ($2/1000000) title "FIFO (RTT=40ms)" with lines lw 5 dt 3 lc rgb myblue, \
	 "cebinae/app_tpt_1000000.dat" using ($1/1000000) title "Cebinae (RTT=20.4ms)" with lines lw 5 dt 1 lc rgb myred, \
	 "cebinae/app_tpt_1000000.dat" using ($2/1000000) title "Cebinae (RTT=40ms)" with lines lw 5 dt 1 lc rgb myblue,
