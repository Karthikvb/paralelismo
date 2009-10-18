//#include <acml.h> //assumes AMD platform

#include <cblas.h>
const char* dgemm_desc = "BLAS dgemm.";
void square_dgemm( int n, double *A, double *B, double *C )
{
    cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans, n,n,n, 1, A,n, B,n, 1, C,n );
}
