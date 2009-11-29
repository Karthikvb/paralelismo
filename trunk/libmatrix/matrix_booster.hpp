#include "block.h"
#include "matrix.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
#include <mkl.h>
/**Inicia la cuenta del reloj*/
void start_clock();
/**Finaliza la cuenta del reloj y devuelve el tiempo transcurrido*/
double end_clock();

/*!Realiza el producto de matrices de enteros A y B y los suma a la matriz C  
*mediante el metodo naive.
*     @param int *A
*        Puntero a matriz de enteros.
*     @param int *B
*        Puntero a matriz de enteros.
*     @param int *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param intnfilasc
*        Nº de filas matriz C.
*     @param intncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix(int * A,int * B, int* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de enteros A y B y los suma a la matriz C  
*mediante el metodo naive con paralelismo mediante openmp.
*     @param int *A
*        Puntero a matriz de enteros.
*     @param int *B
*        Puntero a matriz de enteros.
*     @param int *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix_openmp(int * A,int * B, int* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de enteros A y B y los suma a la matriz C  
*mediante el metodo blocked
*     @param int *A
*        Puntero a matriz de enteros.
*     @param int *B
*        Puntero a matriz de enteros.
*     @param int *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix(int * A,int * B, int* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de enteros A y B y los suma a la matriz C  
*mediante el metodo blocked con paralelismo mediante openmp
*     @param int *A
*        Puntero a matriz de enteros.
*     @param int *B
*        Puntero a matriz de enteros.
*     @param int *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/

int blocked_multiplymatrix_openmp(int * A,int * B, int* C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/*!Realiza el producto de matrices de float A y B y los suma a la matriz C  
*mediante el metodo naive 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix( float *A,float *B, float *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de float A y B y los suma a la matriz C  
*mediante el metodo naive con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix_openmp( float *A,float *B, float *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de float A y B y los suma a la matriz C  
*mediante el metodo blocked 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix(float *A,float *B, float *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de float A y B y los suma a la matriz C  
*mediante el metodo blocked con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix_openmp( float *A,float *B, float *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/*!Realiza el producto de matrices de double A y B y los suma a la matriz C  
*mediante el metodo naive 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix( double *A,double *B, double *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/*!Realiza el producto de matrices de double A y B y los suma a la matriz C  
*mediante el metodo naive con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix_openmp( double *A,double *B, double *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de double A y B y los suma a la matriz C  
*mediante el metodo blocked 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix(double *A,double *B, double *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de double A y B y los suma a la matriz C  
*mediante el metodo blocked con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix_openmp(double *A,double *B, double *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/*!Realiza el producto de matrices de Complex A y B y los suma a la matriz C  
*mediante el metodo naive 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrixc( Complex *A,Complex* B, Complex *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de Complex A y B y los suma a la matriz C  
*mediante el metodo naive con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix_openmp( Complex *A,Complex* B, Complex *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de Complex A y B y los suma a la matriz C  
*mediante el metodo blocked 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix(Complex *A,Complex* B, Complex *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de Complex A y B y los suma a la matriz C  
*mediante el metodo blocked con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix_openmp(Complex *A,Complex* B, Complex *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/*!Realiza el producto de matrices de std::complex<double> A y B y los suma a la matriz C  
*mediante el metodo naive
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix( complex<double> *A,complex<double> *B, complex<double>  *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de std::complex<double> A y B y los suma a la matriz C  
*mediante el metodo naive con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int naive_multiplymatrix_openmp( complex<double> *A,complex<double> *B, complex<double>  *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de std::complex<double> A y B y los suma a la matriz C  
*mediante el metodo blocked 
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix( complex<double> *A,complex<double> *B, complex<double>  *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);
/*!Realiza el producto de matrices de std::complex<double> A y B y los suma a la matriz C  
*mediante el metodo blocked con paralelismo mediante openmp
*     @param float *A
*        Puntero a matriz de enteros.
*     @param float *B
*        Puntero a matriz de enteros.
*     @param float *C
*        Puntero a matriz de enteros.
*     @param int nfilasa
*        Nº de filas matriz A.
*     @param int ncolumnasa
*        Nº de columnas matriz A.
*     @param int nfilasb
*        Nº de filas matriz B.
*     @param int ncolumnasb
*        Nº de columnas matriz B.
*     @param int nfilasc
*        Nº de filas matriz C.
*     @param int ncolumnasc
*        Nº de columnas matriz C.
*@return 0 si Ok
*@return 1 si los tamaños de las matrices son incompatibles.
*/
int blocked_multiplymatrix_openmp(complex<double> *A,complex<double> *B, complex<double>  *C,
int nfilasa,int ncolumnasa,int nfilasb,int ncolumnasb,int nfilasc,int ncolumnasc);

/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de enteros de los tamaños especificados por parámetro.
      @param int m
*        Nº de filas matriz A.
*     @param int n
*        Nº de columnas matriz A.
*     @param int o
*        Nº de filas matriz B.
*     @param int p
*        Nº de columnas matriz B.
*     @param int q       
*        Nº de filas matriz C.
*     @param int r
*        Nº de columnas matriz C.
*/     

int prueba_int(int m,int n,int o,int p,int q,int r);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de float de los tamaños especificados por parámetro.
      @param int m
*        Nº de filas matriz A.
*     @param int n
*        Nº de columnas matriz A.
*     @param int o
*        Nº de filas matriz B.
*     @param int p
*        Nº de columnas matriz B.
*     @param int q       
*        Nº de filas matriz C.
*     @param int r
*        Nº de columnas matriz C.
*/     
int prueba_float(int m,int n,int o,int p,int q,int r);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de double de los tamaños especificados por parámetro.
      @param int m
*        Nº de filas matriz A.
*     @param int n
*        Nº de columnas matriz A.
*     @param int o
*        Nº de filas matriz B.
*     @param int p
*        Nº de columnas matriz B.
*     @param int q       
*        Nº de filas matriz C.
*     @param int r
*        Nº de columnas matriz C.
*/     
int prueba_double(int m,int n,int o,int p,int q,int r);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de complejos de los tamaños especificados por parámetro.
      @param int m
*        Nº de filas matriz A.
*     @param int n
*        Nº de columnas matriz A.
*     @param int o
*        Nº de filas matriz B.
*     @param int p
*        Nº de columnas matriz B.
*     @param int q       
*        Nº de filas matriz C.
*     @param int r
*        Nº de columnas matriz C.
*/     
int prueba_Complex(int m,int n,int o,int p,int q,int r);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de std::complex<double> de los tamaños especificados por parámetro.
      @param int m
*        Nº de filas matriz A.
*     @param int n
*        Nº de columnas matriz A.
*     @param int o
*        Nº de filas matriz B.
*     @param int p
*        Nº de columnas matriz B.
*     @param int q       
*        Nº de filas matriz C.
*     @param int r
*        Nº de columnas matriz C.
*/     
int prueba_stdcomplex(int m,int n,int o,int p,int q,int r);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de enteros de los tamaños especificados por parámetro.
      @param int n
*        Dimensión de las matrices cuadradas a multiplicar
*/   
int prueba_int(int n);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de float de los tamaños especificados por parámetro.
      @param int n
*        Dimensión de las matrices cuadradas a multiplicar
*/    
int prueba_float(int n);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de double de los tamaños especificados por parámetro.
      @param int n
*        Dimensión de las matrices cuadradas a multiplicar
*/    
int prueba_double(int n);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de complejos de los tamaños especificados por parámetro.
      @param int n
*        Dimensión de las matrices cuadradas a multiplicar
*/    
int prueba_Complex(int n);
/**Realiza la prueba de rendimiento de los diferentes algoritmos
para el producto de matrices de std::complex<double> de los tamaños especificados por parámetro.
      @param int n
*        Dimensión de las matrices cuadradas a multiplicar
*/    
int prueba_stdcomplex(int n);
