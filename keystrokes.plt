set xdata time
set timefmt "%Y-%m-%d %H:%M"
set xtics format "%H"
set xtics 60*60

set grid
set style fill solid
set xlabel "Timeline."
set ylabel "The number of keystrokes."

set terminal png
set output "keystrokes.png"

plot "<cat keylogger.log | ruby keystroke.rb" using 2:1:1 with i lc rgb "royalblue" notitle

