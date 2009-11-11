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
int naive_multiplymatrix( matrix *,matrix *, matrix *);
int naive_multiplymatrix_openmp( matrix *,matrix * B, matrix * C);
int blocked_multiplymatrix(matrix *,matrix * , matrix *);
int blocked_multiplymatrix_openmp(matrix *,matrix *, matrix *);
