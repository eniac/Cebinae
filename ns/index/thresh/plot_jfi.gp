
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "jfi.eps"

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

jfi_fq = 0.990
jfi_fifo = 0.537

set arrow from 1,jfi_fifo to 100,jfi_fifo lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.2,0.60 "FIFO" front right textcolor rgb mygrey font "Helvetica,16"

set arrow from 1,jfi_fq to 100,jfi_fq lc rgb mygrey lw 5 dt 3 nohead
set label at graph 0.2,0.92 "FQ" front right textcolor rgb mygrey font "Helvetica,16"

plot "jfi.dat" using ($1*100):($2) with linespoints lw 5 lc rgb myred
