
//Membench que utiliza gettimeofday para funcionar todas las máquina
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <math.h>

#define SAMPLE    10
#define CACHE_MIN (1024)
#define CACHE_MAX (1024*1024*8)

#define TIME_DIF_TO_NS(s,f) \
    ((f.tv_sec-s.tv_sec)*1000000.0 + (f.tv_usec-s.tv_usec))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
int x[CACHE_MAX];

int main()
{
    int register i, index, stride, limit, temp;
    double sample_us, sample_sec, sec, us;
    double timemax=0,timemin=10000,ns;
    struct timeval start,finish;
    int steps, tsteps, csize;
  
    for (csize = CACHE_MIN; csize <= CACHE_MAX; csize *= 2){
        for (stride = 1; stride <= csize/2; stride *= 2){
	    sec = 0;
	    us = 0.0;
	    limit = csize-stride+1;
	    steps = 0;
	    do {
		gettimeofday(&start,NULL);
		for (i = SAMPLE*stride; i != 0; i--)
		    for (index = 0; index < limit; index += stride)
			x[index]++;
		gettimeofday(&finish,NULL);
		sample_us = TIME_DIF_TO_NS(start,finish);
		sample_sec = sample_us/1000000.0;
		steps++;
		sec += sample_sec;
		us += sample_us;
	    } while (sec < 1.0);
	    tsteps=0;
	    do {
		gettimeofday(&start,NULL);
		for (i = SAMPLE*stride; i != 0; i--)
		    for (index = 0; index < limit; index += stride)
			temp += index;
		gettimeofday(&finish,NULL);
		sample_us = TIME_DIF_TO_NS(start,finish);
		sample_sec = sample_us/1000000.0;
		tsteps++;
		sec -= sample_sec;
		us -= sample_us;
	    } while (tsteps < steps);
            ns=(double) (sec*1e9)/(steps*SAMPLE*stride*((limit-1.0)/stride+1.0));
            if (ns>1) 
            {
		timemax=MAX(ns,timemax);
                timemin=MIN(ns,timemin);  
           } 
	}
    }
    printf("#define BLOCK_SIZE %ld\n/*%lf %lf*/\n ",int(round(timemax/timemin)),timemax,timemin);
    return 0;
}

/////////////////////////////////////////////////////////////////////
// $Log: membench.c,v $
// David Álvarez Oquina
//
//////////////////////////////////////////////////////////////////////
