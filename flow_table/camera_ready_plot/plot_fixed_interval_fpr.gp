
reset
set term post eps enhanced dashed color font 'Helvetica,22'
set output "fpr_fixed_interval.eps"

set size 0.5,0.5

set tics nomirror
set key at graph 1.0,1.0
set key font ",16"
set border 3
set key samplen 2

set grid

set yrange [0:]

set xlabel "Slot #"
set ylabel 'FPR [10^{-4}]' offset 1

set logscale x 2
#set xrange [512:4097]
#set xtics 500,500,4500

myred = '#A90533'
myblue = '#004785'
mygreen = '#34a905'

# Picked from https://mdigi.tools/color-shades/
myblue_shades = '#e5f3ff'
myred_shades = '#fee6ed'
mygreen_shades = '#edfee6'

plot "fixed_interval_fpr.dat" i 0 using 1:($3*10000):($4*10000) with filledcurve notitle fc rgb myblue_shades,\
     "fixed_interval_fpr.dat" i 0 using 1:($2*10000) w l lw 4 lc rgb myblue title "1 stage",\
     "fixed_interval_fpr.dat" i 1 using 1:($3*10000):($4*10000) with filledcurve notitle fc rgb myred_shades,\
     "fixed_interval_fpr.dat" i 1 using 1:($2*10000) w l lw 4 lc rgb myred title "2 stage",\
     "fixed_interval_fpr.dat" i 2 using 1:($3*10000):($4*10000) with filledcurve notitle fc rgb mygreen_shades,\
     "fixed_interval_fpr.dat" i 2 using 1:($2*10000) w l lw 4 lc rgb mygreen title "4 stage"
