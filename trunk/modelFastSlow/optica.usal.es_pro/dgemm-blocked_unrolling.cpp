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
#define BLOCK_SIZE 30
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
            double register temp=0; 
            double register temp2=0;
            double register temp3=0;
            double register temp4=0;
            double register temp5=0;
            double register temp6=0;
            double register a0=0; 
            double register a1=0;
            double register a2=0;
            double register a3=0;
            double register a4=0;
            double register a5=0;
            double register b0=0; 
            double register b1=0;
            double register b2=0;
            double register b3=0;
            double register b4=0;
            double register b5=0;
            int k=0;
            for( k = 0; k < K-5; k=k+6 )
            {
                 a0=A[i+k*lda];
                 a1=A[i+(k+1)*lda];
                 a2=A[i+(k+2)*lda];
                 a3=A[i+(k+3)*lda];
                 a4=A[i+(k+4)*lda];
                 a5=A[i+(k+5)*lda];
                 b0=B[k+j*lda];
                 b1=B[k+j*lda+1];
                 b2=B[k+j*lda+2];
                 b3=B[k+j*lda+3];
                 b4=B[k+j*lda+4];
                 b5=B[k+j*lda+5];
                          
                 temp=a0 * b0;
                 temp2=a1 * b1;
                 temp3=a2 * b2;
                 temp4=a3 * b3;
                 temp5=a4 * b4;
                 temp6=a5 * b5;  
                 cij +=temp+temp2+temp3+temp4+temp5+temp6;
            }
            for( int h=k;h < K; h++ )
                 cij += A[i+h*lda] * B[h+j*lda];
            C[i+j*lda] = cij;
       }
}

void do_block( int lda, double *A, double *B, double *C,
               int i, int j, int k )
{

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

     basic_dgemm( lda, M, N, K, A + i + k*lda, B + k + j*lda, C + i + j*lda);

}

void square_dgemm( int M, double *A, double *B, double *C )
{
     for( int i = 0; i < M; i += BLOCK_SIZE )
          for( int j = 0; j < M; j += BLOCK_SIZE )
               for( int k = 0; k < M; k += BLOCK_SIZE )
                    do_block( M, A, B, C, i, j, k );
}
