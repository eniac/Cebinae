
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "graph.eps"

set size 1,0.618 
set border 3
set tics nomirror

set nologscale x

set key reverse Left
set key at graph 1.0,1.0
set key font ",16"
set key maxrows 1
set key samplen 2
# set key width -1

set xlabel "Time [s]"
set ylabel 'JFI'

set xrange [1:51]
set xtics 0,5,101

set grid

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

plot "fifo/jfi_1000000.dat" using 2 title "FIFO" with lines lw 6 dt 3 lc rgb myblue, \
   "fq/jfi_1000000.dat" using 2 title "FQ" with lines lw 6 dt 1 lc rgb mygrey,\
	 "cebinae/jfi_1000000.dat" using 2 title "Cebinae" with lines lw 6 dt 1 lc rgb myred,
