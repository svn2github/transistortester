GNUTERM = "wxt"
set terminal epslatex color solid
set grid
set style data lines
set style line 1  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 4
set style line 4  linetype 1 linecolor rgb "red" linewidth 3.000  pointtype 6
set style line 2  linetype 1 linecolor rgb "green" linewidth 3.000 pointtype 4 pointsize 2
set style line 3  linetype 1 linecolor rgb "blue" linewidth 3.000  pointtype 2 pointsize 1
set style line 5  linetype 1 linecolor rgb "green" linewidth 3.000 pointtype 7 pointsize 2
set style line 6  linetype 1 linecolor rgb "blue" linewidth 3.000  pointtype 7 pointsize 2
set style line 7  linetype 1 linecolor rgb "black" linewidth 3.000  pointtype 4 pointsize 4

set xlabel "ADC sample"
set format x "% g"
set format y "% g"
set ylabel "ADC value"
set key inside right top vertical Right noreverse enhanced autotitles nobox
set output "../GNU/W12compare.eps"
set xrange [0 to 250]
plot "../GNU/W12_18nF.dat" u 1 title "18.2nF", "../GNU/W12_20nF.dat" u 1 title "20.3nF"
set output
#    EOF
