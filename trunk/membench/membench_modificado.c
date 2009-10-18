//Benchmark que mide el tiempo de acceso a varias posiciones de memoria conscutivas y la realización
//de operaciones aritméticas entre ellas

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <sys/times.h>
#include <sys/types.h>

#define SAMPLE    10
#define CACHE_MIN (1024)
#define CACHE_MAX (1024*1024*8)

#define TIME_DIF_TO_NS(s,f) \
    ((f.tv_sec-s.tv_sec)*1000000000.0 + (f.tv_nsec-s.tv_nsec))
int x[CACHE_MAX+2];

int main()
{
    int register i, index, stride, limit, temp;
    double sample_ns, sample_sec, sec, ns;
    struct timespec start,finish;
    int steps, tsteps, csize;
  
    for (csize = CACHE_MIN; csize <= CACHE_MAX; csize *= 2){
        for (stride = 1; stride <= csize/2; stride *= 2){
	    sec = 0;
	    ns = 0.0;
	    limit = csize-stride+1;
	    steps = 0;
	    do {
		clock_gettime(CLOCK_REALTIME,&start);
		for (i = SAMPLE*stride; i != 0; i--)
		    for (index = 0; index < limit; index += stride)
			x[index]=x[index]*x[index+1]+x[index+2];
		clock_gettime(CLOCK_REALTIME,&finish);
		sample_ns = TIME_DIF_TO_NS(start,finish);
		sample_sec = sample_ns/1000000000.0;
		steps++;
		sec += sample_sec;
		ns += sample_ns;
	    } while (sec < 1.0);
	    tsteps=0;
	    do {
		clock_gettime(CLOCK_REALTIME,&start);
		for (i = SAMPLE*stride; i != 0; i--)
		    for (index = 0; index < limit; index += stride)
			temp += index;
		clock_gettime(CLOCK_REALTIME,&finish);
		sample_ns = TIME_DIF_TO_NS(start,finish);
		sample_sec = sample_ns/1000000000.0;
		tsteps++;
		sec -= sample_sec;
		ns -= sample_ns;
	    } while (tsteps < steps);
	    printf("Size: %7d Stride: %7d read+write: %14.0f ns\n",
                   csize*sizeof(int),
		   stride*sizeof(int), 
		   (double) (ns)/(steps*SAMPLE*stride*((limit-1.0)/stride+1.0)));
	}
	printf ("\n");
    }
    return 0;
}


