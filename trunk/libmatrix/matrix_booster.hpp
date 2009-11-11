#include "block.h"
#include "matrix.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>
void start_clock();
double end_clock();
int naive_multiplymatrix( int *,int *, int *,int,int,int,int,int,int);
int naive_multiplymatrix_openmp( int *,int *, int *,int,int,int,int,int,int);
int blocked_multiplymatrix(int *,int *, int *,int,int,int,int,int,int);
int blocked_multiplymatrix_openmp(int *,int *, int *,int,int,int,int,int,int);

int naive_multiplymatrix( float *,float *, float *,int,int,int,int,int,int);
int naive_multiplymatrix_openmp( float *,float *, float *,int,int,int,int,int,int);
int blocked_multiplymatrix(float *,float *, float *,int,int,int,int,int,int);
int blocked_multiplymatrix_openmp(float *,float *, float *,int,int,int,int,int,int);

int naive_multiplymatrix( double *,double*, double *,int,int,int,int,int,int);
int naive_multiplymatrix_openmp( double *,double *, double *,int,int,int,int,int,int);
int blocked_multiplymatrix(double *,double *, double *,int,int,int,int,int,int);
int blocked_multiplymatrix_openmp(double *,double *, double *,int,int,int,int,int,int);

int prueba_int(int,int,int,int,int,int);
int prueba_float(int,int,int,int,int,int);
int prueba_double(int,int,int,int,int,int);
int prueba_int(int);
int prueba_float(int);
int prueba_double(int);
