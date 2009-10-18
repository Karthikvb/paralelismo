/*
  In case you're wondering, dgemm stands for Double-precision, GEneral
  Matrix-Matrix multiplication.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <float.h>
#include <math.h>

#include <sys/time.h>
const char* dgemm_desc = "Simple blocked dgemm.";

#if !defined(BLOCK_SIZE)
#define BLOCK_SIZE 60
#endif

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
  /*
    To optimize this, think about loop unrolling and software
    pipelining.  Hint:  For the majority of the matmuls, you
    know exactly how many iterations there are (the block size)...
  */
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
     /*
       Remember that you need to deal with the fringes in each
       dimension.

       If the matrix is 7x7 and the blocks are 3x3, you'll have 1x3,
       3x1, and 1x1 fringe blocks.

             xxxoooX
             xxxoooX
             xxxoooX
             oooxxxO
             oooxxxO
             oooxxxO
             XXXOOOX

       You won't get this to go fast until you figure out a `better'
       way to handle the fringe blocks.  The better way will be more
       machine-efficient, but very programmer-inefficient.
     */
     int M = min( BLOCK_SIZE, lda-i );
     int N = min( BLOCK_SIZE, lda-j );
     int K = min( BLOCK_SIZE, lda-k );

     //seconds = read_timer2( );
     basic_dgemm( lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);
     //seconds = read_timer2( )-seconds;
     /*if(M<BLOCK_SIZE||N<BLOCK_SIZE||K<BLOCK_SIZE)
     {  
           Mflop_sf =Mflop_sf+ ((2e-6*M * N * K) / (seconds));           
           nflecos++;
     }
     else
     {
           Mflop_sb =Mflop_sb+ ((2e-6*M * N * K) / (seconds)); 
           nbloques++;
     }       
     if((lda-i)<=BLOCK_SIZE&&(lda-j)<=BLOCK_SIZE&&(lda-k)<=BLOCK_SIZE)
     {
           printf("tamano %d Rendimiento bloques %lf nº b=%lf media=%lf\n",lda,Mflop_sb,nbloques,(Mflop_sb/nbloques));
           printf("tamano %d Rendimiento flecos %lf nº f=%lf media=%lf\n",lda,Mflop_sf,nflecos,(Mflop_sf/nflecos));
     }*/  
}

void square_dgemm( int M, double *A, double *B, double *C )
{
     for( int i = 0; i < M; i += BLOCK_SIZE )
          for( int j = 0; j < M; j += BLOCK_SIZE )
               for( int k = 0; k < M; k += BLOCK_SIZE )
                    do_block( M, A, B, C, i, j, k );
}
