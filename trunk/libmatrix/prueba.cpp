
#include "matrix_booster.hpp"
#include <sys/time.h>
#include <stdio.h>
#include "mkl.h"
#include "mkl_boost_ublas_matrix_prod.hpp"
MKL_Complex16 * crea_matrix(MKL_Complex16 * m,int n)
{
	m=(MKL_Complex16 *)malloc(sizeof(MKL_Complex16)*n*n);
	return m;
}

void fill (MKL_Complex16 * m,int n)
{
	for( int i = 0; i < n*n; i++ )
        {
                m[i].real=2 * drand48( ) - 1;
                m[i].imag=2 * drand48( ) - 1;
        }
}
int prueba_blas_float(int tamano)
{
        double tiempo;
        float *A;
        float *B;
        float *C;
        float lda=1;
        A=crea_matrix (A,tamano);
        B=crea_matrix (B,tamano);
        C=crea_matrix (C,tamano);
        fill(A,tamano);
        fill(B,tamano);
        fill(C,tamano);
        start_clock();
        sgemm("N","N",&tamano,&tamano,&tamano,&lda,A,&tamano,B,&tamano,&lda,C,&tamano);
        tiempo=end_clock ();
        printf("Float Blas Tamano %d Tiempo %lf MFlops %lf\n",tamano,tiempo, (2e-6*tamano*tamano*tamano)/tiempo);
        return 0;
}
int prueba_blas_double(int tamano)
{
        double tiempo;
        double *A;
        double *B;
        double *C;
        double lda=1;
        A=crea_matrix (A,tamano);
        B=crea_matrix (B,tamano);
        C=crea_matrix (C,tamano);
        fill(A,tamano);
        fill(B,tamano);
        fill(C,tamano);
        start_clock();
        //C=prod(A,B)
        dgemm("N","N",&tamano,&tamano,&tamano,&lda,A,&tamano,B,&tamano,&lda,C,&tamano);
        tiempo=end_clock ();
        printf("Double Blas Tamano %d Tiempo %lf MFlops %lf\n",tamano,tiempo, (2e-6*tamano*tamano*tamano)/tiempo);
        return 0;
}
int prueba_blas_complex(int tamano)
{
        double tiempo;
        MKL_Complex16 *A,*B,*C;
        MKL_Complex16 lda;
        A=crea_matrix (A,tamano);
        B=crea_matrix (B,tamano);
        C=crea_matrix (C,tamano);
        fill(A,tamano);
        fill(B,tamano);
        fill(C,tamano);
        start_clock();
        zgemm("N","N",&tamano,&tamano,&tamano,&lda,A,&tamano,B,&tamano,&lda,C,&tamano);
        tiempo=end_clock ();
        printf("Complex Blas Tamano %d Tiempo %lf MFlops %lf\n",tamano,tiempo, (2e-6*tamano*tamano*tamano)/tiempo);
        return 0;
}
int main(int argc, char* argv[])
{
    int m,n,o,p,q,r;
    /*switch(argc)
    {
	case 1:
		m=1000;
                n=m;
                o=m;
                p=m;
                q=m;
                r=m;      
		break;
	case 2:
		m=atoi(argv[1]);
                n=m;
                o=m;
                p=m;
                q=m;
                r=m;
		break;
        case 4:
                m=atoi(argv[1]);
                n=atoi(argv[2]);
                p=atoi(argv[3]);
                o=n;
                q=m;
                r=p;
		break;
        case 7:
                m=atoi(argv[1]);
                n=atoi(argv[2]);
                p=atoi(argv[3]);
                o=n;
                q=m;
                r=p;
		break;

        default:
                printf("Nº de argumentos erróneo\n");
                return 1;
                break;
    }*/
    int test_sizes[] = {
        31, 32, 96, 97, 127, 128, 129, 191, 192, 229, 255, 256, 257,
        319, 320, 321, 417, 479, 480, 511, 512, 639, 640, 767, 768, 769, 1000,
    };
    //int test_sizes[] = {10,20,100,400,1000};    
    int tamano;
    for(int i=0;i<sizeof(test_sizes)/sizeof(test_sizes[0]);i++)
    {
            tamano=test_sizes[i];   
            prueba_int(tamano);
            prueba_float(tamano);
            prueba_double(tamano);
            prueba_Complex(tamano);
            prueba_stdcomplex (tamano);
            prueba_blas_float(tamano);
            prueba_blas_double(tamano);
            prueba_blas_complex(tamano);
    }
}


