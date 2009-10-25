#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <float.h>
#include <math.h>
#include <sys/time.h>
//#include <acml.h> //assumes AMD platform
//#include "f2c.h"
//
//  Your function must have the following signature:
//
extern const char* dgemm_desc;
extern void square_dgemm( int M, double *A, double *B, double *C );

//
//  Helper functions
//

double read_timer( )
{
    static bool initialized = false;
    static struct timeval start;
    struct timeval end;
    if( !initialized )
    {
        gettimeofday( &start, NULL );
        initialized = true;
    }

    gettimeofday( &end, NULL );

    return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

void fill( double *p, int n )
{
    for( int i = 0; i < n; i++ )
        p[i] = 2 * drand48( ) - 1;
}

void absolute_value( double *p, int n )
{
    for( int i = 0; i < n; i++ )
        p[i] = fabs( p[i] );
}

//
//  The benchmarking program
//
int main( int argc, char **argv )
{
    //printf ("Description:\t%s\n\n", dgemm_desc);

    //
    // These sizes should highlight performance dips at multiples of certain
    // powers-of-two
    //
    /*int test_sizes[] = {
        31, 32, 96, 97, 127, 128, 129, 191, 192, 229, 255, 256, 257,
        319, 320, 321, 417, 479, 480, 511, 512, 639, 640, 767, 768, 769, 1000,
    };*/
    int test_sizes[] = {
        30,2*30,3*30,4*30,5*30,6+30,7*30,9*30,10*30
    }; 
    //int test_sizes [] = { 129};
    for( int isize = 1;isize <=100 ; isize++ )
    {
        int n = isize*30;//test_sizes[isize];
	int niter;
        double *A = (double*) malloc( n * n * sizeof(double) );
        double *B = (double*) malloc( n * n * sizeof(double) );
        double *C = (double*) malloc( n * n * sizeof(double) );

        fill( A, n * n );
        fill( B, n * n );
        fill( C, n * n );
        //
        //  measure Mflop/s rate
        //  time a sufficiently long sequence of calls to eliminate noise
        //
        double Mflop_s, seconds = -1.0;
        for( int n_iterations = 1; seconds < 0.1; n_iterations *= 2 ) 
        {
            //
            //  warm-up
            //
            square_dgemm( n, A, B, C );
            
            //
            //  measure time
            //
            seconds = read_timer( );
            for( int i = 0; i < n_iterations; i++ )
                square_dgemm( n, A, B, C );
            seconds = read_timer( ) - seconds;
            
            //
            //  compute Mflop/s rate
            //
            Mflop_s = 2e-6 * n_iterations * n * n * n / seconds;
            niter=n_iterations;
        }
        printf ("Seconds %lf Size: %d Mflop/s: %g \n",seconds/niter, n, Mflop_s);

        free( C );
        free( B );
        free( A );
    }
    
    return 0;
}

