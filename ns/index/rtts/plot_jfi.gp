
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

plot "jfi.dat" using ($1):($2) title "FIFO" with linespoints pt 2 ps 1.5 lw 5 lc rgb myblue,\
     "jfi.dat" using ($1):($3) title "FQ"  with linespoints pt 4 ps 1.5 lw 5 lc rgb mygrey,\
     "jfi.dat" using ($1):($4) title "Cebinae" with linespoints pt 6 ps 1.5 lw 5 lc rgb myred
