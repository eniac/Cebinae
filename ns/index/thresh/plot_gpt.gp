
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "gpt.eps"

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

gpt_fq = 83043490.909/1000000
gpt_fifo = 95305774.545/1000000

set arrow from 1,gpt_fifo to 100,gpt_fifo lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.97,0.87 "FIFO" front right textcolor rgb mygrey font "Helvetica,16"

set arrow from 1,gpt_fq to 100,gpt_fq lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.91,0.77 "FQ" front right textcolor rgb mygrey font "Helvetica,16"

plot "gpt.dat" using ($1*100):($2/1000000) with linespoints lw 5 lc rgb myred
