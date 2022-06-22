
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

plot "gpt.dat" using ($1):($2/1000000) title "FIFO" with linespoints pt 2 ps 1.5 lw 5 lc rgb myblue,\
     "gpt.dat" using ($1):($3/1000000) title "FQ" with linespoints pt 4 ps 1.5 lw 5 lc rgb mygrey,\
     "gpt.dat" using ($1):($4/1000000) title "Cebinae" with linespoints pt 6 ps 1.5 lw 5 lc rgb myred
