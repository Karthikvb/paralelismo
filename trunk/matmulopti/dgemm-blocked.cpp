#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <float.h>
#include <math.h>
#include "bloque.h"
#include <sys/time.h>
const char* dgemm_desc = "Simple blocked dgemm.";

#define min(a,b) (((a)<(b))?(a):(b))
double read_timer2( )
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
/*
  A is M-by-K
  B is K-by-N
  C is M-by-N

  lda is the leading dimension of the matrix (the M of square_dgemm).
*/

void basic_dgemm( int lda, int M, int N, int K,
                  double *A, double *B, double *C )
{
  for( int i = 0; i < M; i++ )
       for( int j = 0; j < N; j++ ) 
       {
            double cij = C[i+j*lda];
            for( int k = 0; k < K; k++ )
                 cij += A[i+k*lda] * B[k+j*lda];
            C[i+j*lda] = cij;
       }
}

void do_block( int lda, double *A, double *B, double *C,
               int i, int j, int k )
{
     static double Mflop_sb=0,Mflop_sf=0;
     double seconds=0;
     static double nbloques=0,nflecos=0;
     int M = min( BLOCK_SIZE, lda-i );
     int N = min( BLOCK_SIZE, lda-j );
     int K = min( BLOCK_SIZE, lda-k );

     basic_dgemm( lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);
}

void square_dgemm( int M, double *A, double *B, double *C )
{
     for( int i = 0; i < M; i += BLOCK_SIZE )
          for( int j = 0; j < M; j += BLOCK_SIZE )
               for( int k = 0; k < M; k += BLOCK_SIZE )
                    do_block( M, A, B, C, i, j, k );
}
