#include "block.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/time.h>

typedef struct{
        int nfilas;
        int ncolumnas;
        double *datos;
        } matrix;
void start_clock();
double end_clock();
void fill (matrix *,int );
void fill (matrix *,int ,int);
int naive_multiplymatrix( matrix *,matrix *, matrix *);
int naive_multiplymatrix_openmp( matrix *,matrix * B, matrix * C);
int blocked_multiplymatrix(matrix *,matrix * , matrix *);
int blocked_multiplymatrix_openmp(matrix *,matrix *, matrix *);
void square_dgemm( int , double *, double *, double *);
