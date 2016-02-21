#!/bin/sh
cat keylogger.log | grep "type:key" | sed -e 's/code\://g' | awk '{print $3}' | sort | uniq -c| sort -n -k1 -r | awk '{printf("%d %d\n", $2, $1);}' > typekey.log 
cp typekey.log typekey_tmp.log
sh ./keycode.sh typekey_tmp.log
gnuplot visualize2png.plt
rm typekey_tmp.log
