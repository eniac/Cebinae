reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fp.eps"

set size 0.5,0.5

set tics nomirror
#set key top right reverse Left
#set key font ",16"
unset key
set border 3

set xlabel "Round interval [ms]"
set ylabel 'FP [10^{-4}]' offset 1

set xrange [0:51]
set xtics 0,10,50
set grid

myred = '#A90533'
myblue = '#004785'
mygrey = 'grey70'

plot "result.dat" using 1:($2*10000) with linespoints lw 5 lc rgb myred
