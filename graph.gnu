set terminal png
set output "graph.png"

set xrange [0:6]

set yrange [0:3]

set ylabel "y"

set xlabel "x"

plot "./output.txt" using 1:2 with lines title "Interpolation"