#include "matrix_booster.hpp"
#include <stdio.h>
#define min(a,b) (((a)<(b))?(a):(b))
double read_timer( bool initial)
{
    static struct timeval start;
    struct timeval end;
    if( !initial )
    {
        gettimeofday( &start, NULL );
        return 0;
    }
    else
    {
        gettimeofday( &end, NULL );
        return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
    }
}
void start_clock()
{
    read_timer(false);  
}
double end_clock()
{
    return read_timer(true);  
}

int naive_multiplymatrix(int * A,int * B, int* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive\n");
        return 1;
  }  
  for( int i = 0; i < nfilasa; i++ )
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            int cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  return 0;
}


int naive_multiplymatrix_openmp( int *A,int *B, int * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive omp\n");
        return 1;
  }  
  #pragma omp parallel
  {
   #pragma omp for
   for( int i = 0; i < nfilasa; i++ )
       #pragma omp parallel for 
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            int cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij +=  A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  }
}
void basic_dgemm( int nfilasa,int ncolumnasa,int ncolumnasb,int M, int N, int K,
                  int *A, int *B, int *C )
{
  for( int i = 0; i < M; i++ )
       for( int j = 0; j < N; j++ ) 
       {
            int cij = C[i*ncolumnasb+j];
            for( int k = 0; k < K; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
}

void do_block( int nfilasa, int ncolumnasb,int ncolumnasa, int *A, int *B, int *C,
               int i, int j, int k )
{
/*Calculamos las submatrices que componen los bloques para hacer los subproductos*/
     int M = min( BLOCK_SIZE, nfilasa-i );
     int N = min( BLOCK_SIZE, ncolumnasb-j );
     int K = min( BLOCK_SIZE, ncolumnasa-k );

     basic_dgemm( nfilasa,ncolumnasa,ncolumnasb, M, N, K, A + i*ncolumnasa + k, B + k*ncolumnasb + j, C + i*ncolumnasb + j);
}
int blocked_multiplymatrix(int * A,int* B, int  * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked\n");
        return 1;
  }      
  for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
          for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
               for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                    do_block( nfilasa,ncolumnasb,ncolumnasa, A, B, C, i, j, k );
}
int blocked_multiplymatrix_openmp(int * A,int * B, int * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked omp\n");
        return 1;
  }  
  #pragma omp parallel
        {
        #pragma omp for
             for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
             #pragma omp parallel for
                  for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
                  #pragma omp parallel for
                       for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                            do_block( nfilasa,ncolumnasb, ncolumnasa, A, B, C, i, j, k );
        }
}

int naive_multiplymatrix(float * A,float * B, float* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive\n");
        return 1;
  }  
  for( int i = 0; i < nfilasa; i++ )
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            float cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  return 0;
}


int naive_multiplymatrix_openmp( float*A,float *B, float * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive omp\n");
        return 1;
  }  
  #pragma omp parallel
  {
   #pragma omp for
   for( int i = 0; i < nfilasa; i++ )
       #pragma omp parallel for 
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            float cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij +=  A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  }
}
void basic_dgemm( int nfilasa,int ncolumnasa,int ncolumnasb,int M, int N, int K,
                  float *A, float *B, float *C )
{
  for( int i = 0; i < M; i++ )
       for( int j = 0; j < N; j++ ) 
       {
            float cij = C[i*ncolumnasb+j];
            for( int k = 0; k < K; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
}

void do_block( int nfilasa, int ncolumnasb,int ncolumnasa, float *A, float *B, float *C,
               int i, int j, int k )
{
/*Calculamos las submatrices que componen los bloques para hacer los subproductos*/
     int M = min( BLOCK_SIZE, nfilasa-i );
     int N = min( BLOCK_SIZE, ncolumnasb-j );
     int K = min( BLOCK_SIZE, ncolumnasa-k );

     basic_dgemm( nfilasa,ncolumnasa,ncolumnasb, M, N, K, A + i*ncolumnasa + k, B + k*ncolumnasb + j, C + i*ncolumnasb + j);
}
int blocked_multiplymatrix(float * A,float* B, float  * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked\n");
        return 1;
  }      
  for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
          for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
               for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                    do_block( nfilasa,ncolumnasb,ncolumnasa, A, B, C, i, j, k );
}
int blocked_multiplymatrix_openmp(float * A,float * B, float * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked omp\n");
        return 1;
  }  
  #pragma omp parallel
        {
        #pragma omp for
             for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
             #pragma omp parallel for
                  for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
                  #pragma omp parallel for
                       for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                            do_block( nfilasa,ncolumnasb, ncolumnasa, A, B, C, i, j, k );
        }
}

int naive_multiplymatrix(double * A,double * B, double* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive\n");
        return 1;
  }  
  for( int i = 0; i < nfilasa; i++ )
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            float cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  return 0;
}


int naive_multiplymatrix_openmp( double*A,double *B, double * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive omp\n");
        return 1;
  }  
  #pragma omp parallel
  {
   #pragma omp for
   for( int i = 0; i < nfilasa; i++ )
       #pragma omp parallel for 
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            float cij = C[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij +=  A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
  }
}
void basic_dgemm( int nfilasa,int ncolumnasa,int ncolumnasb,int M, int N, int K,
                  double *A, double *B, double *C )
{
  for( int i = 0; i < M; i++ )
       for( int j = 0; j < N; j++ ) 
       {
            double cij = C[i*ncolumnasb+j];
            for( int k = 0; k < K; k++ )
                 cij += A[i*ncolumnasa+k] * B[k*ncolumnasb+j];
            C[i*ncolumnasb+j] = cij;
       }
}

void do_block( int nfilasa, int ncolumnasb,int ncolumnasa, double *A, double *B, double *C,
               int i, int j, int k )
{
/*Calculamos las submatrices que componen los bloques para hacer los subproductos*/
     int M = min( BLOCK_SIZE, nfilasa-i );
     int N = min( BLOCK_SIZE, ncolumnasb-j );
     int K = min( BLOCK_SIZE, ncolumnasa-k );

     basic_dgemm( nfilasa,ncolumnasa,ncolumnasb, M, N, K, A + i*ncolumnasa + k, B + k*ncolumnasb + j, C + i*ncolumnasb + j);
}
int blocked_multiplymatrix(double * A,double* B, double  * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked\n");
        return 1;
  }      
  for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
          for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
               for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                    do_block( nfilasa,ncolumnasb,ncolumnasa, A, B, C, i, j, k );
}
int blocked_multiplymatrix_openmp(double * A,double * B, double * C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc)
{
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked omp\n");
        return 1;
  }  
  #pragma omp parallel
        {
        #pragma omp for
             for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
             #pragma omp parallel for
                  for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
                  #pragma omp parallel for
                       for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                            do_block( nfilasa,ncolumnasb, ncolumnasa, A, B, C, i, j, k );
        }
}

int prueba_int(int m,int n,int o,int p,int q,int r)
{
    int *A;
    int *B;
    int *C;
    A=crea_matrix(A,m,n);
    B=crea_matrix(B,o,p);
    C=crea_matrix(C,q,r);
    fill(A,m,n);
    fill(B,o,p);
    fill(C,q,r); 
    double tiempo;
    
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Int Naive Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix_openmp (A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Int NaiveOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Int Blocked Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix_openmp(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Int BlockedOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    free(A);
    free(B);
    free(C);
    return 0;
}
int prueba_float(int m,int n,int o,int p,int q,int r)
{
    float *A;
    float *B;
    float *C;
    A=crea_matrix(A,m,n);
    B=crea_matrix(B,o,p);
    C=crea_matrix(C,q,r);
    fill(A,m,n);
    fill(B,o,p);
    fill(C,q,r); 
    double tiempo;
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Float Naive Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix_openmp (A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Float NaiveOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Float Blocked Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix_openmp(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Float BlockedOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    free(A);
    free(B);
    free(C);
    return 0;
}
int prueba_double(int m,int n,int o,int p,int q,int r)
{
    double *A;
    double *B;
    double *C;
    A=crea_matrix(A,m,n);
    B=crea_matrix(B,o,p);
    C=crea_matrix(C,q,r);
    fill(A,m,n);
    fill(B,o,p);
    fill(C,q,r);
    double tiempo;
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Double Naive Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        naive_multiplymatrix_openmp (A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Double NaiveOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Double Blocked Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    start_clock();
    for (int j=0;j<1;j++)
    {
        blocked_multiplymatrix_openmp(A,B,C,m,n,o,p,q,r);
    }
    tiempo=end_clock();
    printf ("Double BlockedOmp Tamaños %d %d %d %d %d %d Tiempo %lf Mflops %lf\n",m,n,o,p,q,r,tiempo,m*p*n*2e-6/tiempo);
    free(A);
    free(B);
    free(C);
    return 0;
}

int prueba_int(int n)
{
    prueba_int(n,n,n,n,n,n);
}
int prueba_float(int n)
{
    prueba_float(n,n,n,n,n,n);    
}
int prueba_double(int n)
{
    prueba_double(n,n,n,n,n,n); 
}
