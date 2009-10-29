#include "matrix_booster.h"
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
void square_dgemm( int n, double *A, double *B, double *C )
{
  for( int i = 0; i < n; i++ )
       for( int j = 0; j < n; j++ ) 
       {
            double cij = C[i+j*n];
            for( int k = 0; k < n; k++ )
                 cij += A[i+k*n] * B[k+j*n];
            C[i+j*n] = cij;
       }
}
int naive_multiplymatrix( matrix * A,matrix * B, matrix * C)
{
  int nfilasa=A->nfilas;
  int ncolumnasa=A->ncolumnas;
  int nfilasb=B->nfilas;
  int ncolumnasb=B->ncolumnas;
  int nfilasc=C->nfilas;
  int ncolumnasc=C->ncolumnas;
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto naive\n");
        return 1;
  }  
  for( int i = 0; i < nfilasa; i++ )
       for( int j = 0; j < ncolumnasb; j++ ) 
       {
            double cij = C->datos[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij += A->datos[i*ncolumnasa+k] * B->datos[k*ncolumnasb+j];
            C->datos[i*ncolumnasb+j] = cij;
       }
  return 0;
}


int naive_multiplymatrix_openmp( matrix * A,matrix * B, matrix * C)
{
  int nfilasa=A->nfilas;
  int ncolumnasa=A->ncolumnas;
  int nfilasb=B->nfilas;
  int ncolumnasb=B->ncolumnas;
  int nfilasc=C->nfilas;
  int ncolumnasc=C->ncolumnas;
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
            double cij = C->datos[i*ncolumnasb+j];
            for( int k = 0; k < ncolumnasa; k++ )
                 cij +=  A->datos[i*ncolumnasa+k] * B->datos[k*ncolumnasb+j];
            C->datos[i*ncolumnasb+j] = cij;
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
int blocked_multiplymatrix(matrix * A,matrix * B, matrix * C)
{
  int nfilasa=A->nfilas;
  int ncolumnasa=A->ncolumnas;
  int nfilasb=B->nfilas;
  int ncolumnasb=B->ncolumnas;
  int nfilasc=C->nfilas;
  int ncolumnasc=C->ncolumnas;
  if (ncolumnasa!=nfilasb || nfilasa!=nfilasc || ncolumnasb!=ncolumnasc)
  {
        printf("Tamaños de matrices incompatibles para el producto blocked\n");
        return 1;
  }      
  for( int i = 0; i < nfilasa; i += BLOCK_SIZE )
          for( int j = 0; j < ncolumnasb; j += BLOCK_SIZE )
               for( int k = 0; k < ncolumnasa; k += BLOCK_SIZE )
                    do_block( nfilasa,ncolumnasb,ncolumnasa, A->datos, B->datos, C->datos, i, j, k );
}
int blocked_multiplymatrix_openmp(matrix * A,matrix * B, matrix * C)
{
  int nfilasa=A->nfilas;
  int ncolumnasa=A->ncolumnas;
  int nfilasb=B->nfilas;
  int ncolumnasb=B->ncolumnas;
  int nfilasc=C->nfilas;
  int ncolumnasc=C->ncolumnas;
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
                            do_block( nfilasa,ncolumnasb, nfilasa, A->datos, B->datos, C->datos, i, j, k );
        }
}

void fill (matrix *A, int n)
{
  A->nfilas=n;
  A->ncolumnas=n;
  A->datos=(double*) malloc( n * n * sizeof(double) );
  for( int i = 0; i < n*n; i++ )
        A->datos[i] = 2 * drand48( ) - 1;
}
void fill (matrix *A, int a, int b)
{
  A->nfilas=a;
  A->ncolumnas=b;
  A->datos=(double*) malloc( a * b * sizeof(double) );
  for( int i = 0; i < (a*b); i++ )
        A->datos[i] = 2 * drand48( ) - 1;
}
