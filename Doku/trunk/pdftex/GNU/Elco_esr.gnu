#!/usr/bin/gnuplot -persist
unset clip points
set clip one
unset clip two
set bar 1.000000 front
set border 31 front linetype -1 linewidth 1.000
set xdata
set ydata
set zdata
set boxwidth
set style fill  empty border
set style rectangle back fc lt -3 fillstyle   solid 1.00 border lt -1
set style circle radius graph 0.02, first 0, 0 
set dummy x,y
set format x "% g"
set format y "% g"
set key title ""
set key inside right top vertical Right noreverse enhanced autotitles nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 0
unset label
unset arrow
set style increment default
unset style line
unset style arrow
set style histogram clustered gap 2 title  offset character 0, 0, 0
unset logscale
set offsets 0, 0, 0, 0
set pointsize 1
set pointintervalbox 1
set encoding default
set samples 100, 100
unset contour
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels auto 5
set cntrparam points 5
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
set xzeroaxis linetype -2 linewidth 1.000
set yzeroaxis linetype -2 linewidth 1.000
set zzeroaxis linetype -2 linewidth 1.000
set ticslevel 0.5
set mxtics default
set mytics default
set mztics default
set xtics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set xtics autofreq  norangelimit
set ytics border in scale 1,0.5 mirror norotate  offset character 0, 0, 0
set ytics autofreq  norangelimit
set title "" 
set title  offset character 0, 0, 0 font "" norotate
set xlabel "" 
set xlabel  offset character 0, 0, 0 font "" textcolor lt -1 norotate
set ylabel "" 
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by -270
set zero 1e-08
set lmargin  -1
set bmargin  -1
set rmargin  -1
set tmargin  -1
set locale "de_DE.UTF-8"
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front bdefault
set loadpath 
set fontpath 
set fit noerrorvariables
set terminal epslatex color solid
set style line 1  linetype 1 linecolor rgb "green" linewidth 3.000  pointtype 4
set style line 2  linetype 1 linecolor rgb "green" linewidth 3.000 pointtype 4 pointsize 2
set style line 3  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 2 pointsize 2
set style line 4  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 6 pointsize 1.5
set style line 5  linetype 1 linecolor rgb "green" linewidth 3.000 pointtype 1 pointsize 1.5
set style line 6  linetype 1 linecolor rgb "blue" linewidth 3.000  pointtype 7 pointsize 1
set style line 7  linetype 1 linecolor rgb "black" linewidth 3.000  pointtype 4 pointsize 1.2
set grid
set logscale y
set yrange [ 0.01 : 100 ] 
set xrange [ 0 : 18 ]
#set xtics 1,1,14
set xtics rotate
set xtics ("0.47u/100V" 1 0,"1u/100V" 2 0,"1u/50V" 3 0,"2.2u/100V" 4 0,"2.2u/50V" 5 0,"3.3u/100V" 6 0,"4.7u/63V" 7 0,"4.7u/50V" 8 0,"10u/50V" 9 0,"22u/10V" 10 0,"22u/63V" 11 0,"33u/63V" 12 0,"47u/63V" 13 0,"100u/63V" 14 0,"220u/63V" 15 0,"470u/35V" 16 0,"500u/3V" 17 0)
#set ytics 0.1,5,50
GNUTERM = "wxt"
set ylabel "ESR / Ohm"
#set y2range [ 0.01 : 100 ] 
#set y2label "Vloss / \%"
#set title "ESR values for different capacitors"
set output "../GNU/Elco_esr.eps"
plot "Elco_esr.dat" u 1:4 title "LCR-100Hz" ls 1 with points,"Elco_esr.dat" u 1:8 title "LCR-1kHz" ls 4 with points, "Elco_esr.dat" u 1:10 title "LCR-10kHz" ls 3 with points, "Elco_esr.dat" u 1:12 title "LCR-100kHz" ls 5 with points, "Elco_esr.dat" u 1:17 title "TTester" ls 7 with points
# "Elco_esr.dat" u 1:16 title "Vloss" ls 6 with points
pause 10
#    EOF
