#/bin/bash

# merge dat's


./$6/$2 > $2.dat

./$6/$3 > $3.dat

./$6/$4 > $4.dat

./$6/$5 > $5.dat

#plot results
gnuplot -e "set terminal png size 2000,2000;
  set output '$1.png';
  set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5;
  set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5;
  set style line 3 lc rgb '#ffff00' lt 1 lw 2 pt 5 ps 1.5;
  set style line 4 lc rgb '#00fe36' lt 1 lw 2 pt 5 ps 1.5;
  plot '$2.dat'  with linespoints ls 1, \
       '$3.dat'  with linespoints ls 3, \
       '$4.dat'  with linespoints ls 4, \
       '$5.dat'  with linespoints ls 5;"
