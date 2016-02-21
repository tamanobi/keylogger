set boxwidth 0.5 relative
set style fill solid border lc rgb "black"
plot "typekey_tmp.log" using 0:2:xtic(1) with boxes lw 1 lc rgb "light-green" notitle

