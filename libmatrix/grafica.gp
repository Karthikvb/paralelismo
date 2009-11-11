######################################################################
## $Id: membench.gp,v 1.4 1998/02/24 23:59:20 dmartin Exp $
######################################################################

#set logscale x 2
#set xtics (200,400,600,800,1000)
set xrange [0:1000]
set ylabel "Rendimiento Mflops"
set xlabel "Tamano matriz"
set title "Rendimientos biblioteca booster. Pentium 2Ghz"
set yrange [0:2000]
set term postscript color
plot "< awk '{if ($1 ~ /Int/ && $2 ~ /Naive/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Int naive" with linespoints, \
     "< awk '{if ($1 ~ /Int/ && $2 ~ /NaiveOmp/) print $4,$13}' rendimientos.out" title "Int naive omp" with linespoints, \
     "< awk '{if ($1 ~ /Int/ && $2 ~ /Blocked/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Int blocked" with linespoints, \
     "< awk '{if ($1 ~ /Int/ && $2 ~ /BlockedOmp/) print $4,$13}' rendimientos.out" title "Int blocked omp" with linespoints, \
     "< awk '{if ($1 ~ /Float/ && $2 ~ /Naive/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Float naive" with linespoints, \
     "< awk '{if ($1 ~ /Float/ && $2 ~ /NaiveOmp/) print $4,$13}' rendimientos.out" title "Float naive omp" with linespoints, \
     "< awk '{if ($1 ~ /Float/ && $2 ~ /Blocked/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Float blocked" with linespoints, \
     "< awk '{if ($1 ~ /Float/ && $2 ~ /BlockedOmp/) print $4,$13}' rendimientos.out" title "Float blocked omp" with linespoints, \
     "< awk '{if ($1 ~ /Double/ && $2 ~ /Naive/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Double naive" with linespoints, \
     "< awk '{if ($1 ~ /Double/ && $2 ~ /NaiveOmp/) print $4,$13}' rendimientos.out" title "Double naive omp" with linespoints, \
     "< awk '{if ($1 ~ /Double/ && $2 ~ /Blocked/ && $2 !~/Omp/) print $4,$13}' rendimientos.out" title "Double blocked" with linespoints, \
     "< awk '{if ($1 ~ /Double/ && $2 ~ /BlockedOmp/) print $4,$13}' rendimientos.out" title "Double blocked omp" with linespoints
############################################################## ########
## Fichero para la generación de graficas de rendimientos
######################################################################

