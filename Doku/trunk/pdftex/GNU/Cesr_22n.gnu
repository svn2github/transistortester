set border 31 front linetype -1 linewidth 1.000
set grid xtics nomxtics ytics nomytics noztics nomztics \
 nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set key inside right top vertical Right noreverse enhanced autotitles nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 0
set style histogram clustered gap 2 title  offset character 0, 0, 0
unset logscale
set logscale x 10
set pointsize 2
set origin 0,0
set style data points
set style function lines
set xzeroaxis linetype -2 linewidth 1.000
set yzeroaxis linetype -2 linewidth 1.000
set ticslevel 0.5
set xtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set xtics autofreq  norangelimit
set ytics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set ytics autofreq  norangelimit
set title "" 
set title  offset character 0, 0, 0 font "" norotate
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set fit noerrorvariables
GNUTERM = "wxt"
set terminal epslatex color solid
set grid
set logscale x
#set logscale y
set pointsize 3
set style data points
set style line 1  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 4
set style line 4  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 6
set style line 2  linetype 1 linecolor rgb "black" linewidth 3.000 pointtype 4 pointsize 2
set style line 3  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 2 pointsize 1
set style line 5  linetype 1 linecolor rgb "green" linewidth 3.000 pointtype 7 pointsize 2
set style line 6  linetype 1 linecolor rgb "blue" linewidth 3.000  pointtype 7 pointsize 2
set style line 7  linetype 1 linecolor rgb "blue" linewidth 3.000  pointtype 4 pointsize 2

set xlabel "Capacity value / F"
set format x "%.0s%c"
set format y "% g"
set xtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set xtics autofreq  norangelimit
set ylabel "ESR / Ohm"
set key inside right top vertical Right noreverse enhanced autotitles nobox
set output "../GNU/Cesr_22n.eps"
#plot "../GNU/Cesr_22n.dat" u 2:22 title "GM328" ls 1, \
#     "../GNU/Cesr_22n.dat" u 2:24 title "fish" ls 3, \
#     "../GNU/Cesr_22n.dat" u 2:18 title "kit" ls 4, "../GNU/Cesr_22n.dat" u 2:20 notitle ls 4 ,\
#    "../GNU/Cesr_22n.dat" u 2:6 title "wei" ls 5, "../GNU/Cesr_22n.dat" u 2:8 notitle ls 5 ,\

plot "../GNU/Cesr_22n.dat" u 2:10 title "Tester" ls 3, "../GNU/Cesr_22n.dat" u 2:12 notitle ls 3 , "../GNU/Cesr_22n.dat" u 2:14 notitle ls 3,\
     "../GNU/Cesr_22n.dat" u 2:16 notitle ls 3,\
     "../GNU/Cesr_22n.dat" u 2:22 notitle ls 3, \
     "../GNU/Cesr_22n.dat" u 2:24 notitle ls 3, \
     "../GNU/Cesr_22n.dat" u 2:18 notitle ls 3, "../GNU/Cesr_22n.dat" u 2:20 notitle ls 3 ,\
     "../GNU/Cesr_22n.dat" u 2:6 notitle ls 3, "../GNU/Cesr_22n.dat" u 2:8 notitle ls 3 ,\
     "../GNU/Cesr_22n.dat" u 2:4 title "LCR100k" ls 2, "../GNU/Cesr_22n.dat" u 2:3 title "LCR10k" ls 7
#pause 10
set output
#    EOF
