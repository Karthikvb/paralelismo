######################################################################
## $Id: membench.gp,v 1.4 1998/02/24 23:59:20 dmartin Exp $
######################################################################

set logscale x 2
set xtics (4,16,64,256,"1K" 1024,"4K" 4096,"16K" 16384,"64K" 65536,"256K" 262144,"1M" 1048576,"4M" 4194304,"16M" 16777216 )
set ylabel "Time (nsec)"
set xlabel "Stride (bytes)"
set title ""
set yrange [0:200]
set term postscript color
plot "< awk '{if ($2 == 4096) print $4,$6}' membench_modificado.out" title "4KB" with linespoints, \
     "< awk '{if ($2 == 8192) print $4,$6}' membench_modificado.out" title "8KB" with linespoints, \
     "< awk '{if ($2 == 16384) print $4,$6}' membench_modificado.out" title "16KB" with linespoints, \
     "< awk '{if ($2 == 32768) print $4,$6}' membench_modificado.out" title "32KB" with linespoints, \
     "< awk '{if ($2 == 65536) print $4,$6}' membench_modificado.out" title "64KB" with linespoints, \
     "< awk '{if ($2 == 131072) print $4,$6}' membench_modificado.out" title "128KB" with linespoints, \
     "< awk '{if ($2 == 262144) print $4,$6}' membench_modificado.out" title "256KB" with linespoints, \
     "< awk '{if ($2 == 524288) print $4,$6}' membench_modificado.out" title "512KB" with linespoints, \
     "< awk '{if ($2 == 1048576) print $4,$6}' membench_modificado.out" title "1MB" with linespoints, \
     "< awk '{if ($2 == 2097152) print $4,$6}' membench_modificado.out" title "2MB" with linespoints, \
     "< awk '{if ($2 == 4194304) print $4,$6}' membench_modificado.out" title "4MB" with linespoints, \
     "< awk '{if ($2 == 8388608) print $4,$6}' membench_modificado.out" title "8MB" with linespoints, \
     "< awk '{if ($2 == 16777216) print $4,$6}' membench_modificado.out" title "16MB" with linespoints , \
     "< awk '{if ($2 == 33554432) print $4,$6}' membench_modificado.out" title "32MB" with linespoints
######################################################################
## $Log: membench.gp,v $
## Revision 1.4  1998/02/24 23:59:20  dmartin
## color postscript
##
## Revision 1.3  1998/02/05 22:07:39  dmartin
## generate full-page ps instead of little eps
##
## Revision 1.2  1998/02/05 21:44:24  dmartin
## added plot labels
##
## Revision 1.1  1998/01/19 00:47:39  dmartin
## Initial revision
##
######################################################################

