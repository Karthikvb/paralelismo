/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * matrix.cpp
 * Copyright (C) David Álvarez Oquina 2009 <david2ao@gmail.com>
 * 
 * matrix.cpp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * matrix.cpp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include "complex.hpp"

/**Devuelve un puntero a una matrix de enteros de tamaño n*n */
int * crea_matrix(int *,int n);
/**Devuelve un puntero a una matrix de enteros de tamaño a*b */
int * crea_matrix(int *,int a,int b);
/**Devuelve un puntero a una matrix de float de tamaño n*n */
float * crea_matrix(float *,int n);
/**Devuelve un puntero a una matrix de float de tamaño a*b */
float * crea_matrix(float *,int a,int b);
/**Devuelve un puntero a una matrix de double de tamaño n*n*/
double * crea_matrix(double *,int n);
/**Devuelve un puntero a una matrix de double de tamaño a*b */
double * crea_matrix(double *,int a,int b);
/**Devuelve un puntero a una matrix de complex de tamaño n*n*/
Complex * crea_matrix(Complex *,int n);
/**Devuelve un puntero a una matrix de complex de tamaño a*b */
Complex * crea_matrix(Complex *,int a,int b);
/**Devuelve un puntero a una matrix de complex de tamaño n*n*/
complex<double> * crea_matrix(complex<double> *,int n);
/**Devuelve un puntero a una matrix de complex de tamaño a*b */
complex<double> * crea_matrix(complex<double> *,int a,int b);
/** Rellena una matriz de enteros de tamaño n*n con valores aleatorios */
void fill (int *,int n);
/** Rellena una matriz de enteros de tamaño a*b con valores aleatorios */
void fill (int *,int a,int b);
/** Rellena una matriz de float de tamaño n*n con valores aleatorios */
void fill (float *,int n);
/** Rellena una matriz de enteros de tamaño a*b con valores aleatorios */
void fill (float *,int a,int b);
/** Rellena una matriz de double de tamaño n*n con valores aleatorios */
void fill (double *,int n);
/** Rellena una matriz de enteros de tamaño a*b con valores aleatorios */
void fill (double *,int a,int b);
/** Rellena una matriz de complex de tamaño n*n con valores aleatorios */
void fill (Complex *,int n);
/** Rellena una matriz de enteros de tamaño a*b con valores aleatorios */
void fill (Complex *,int a,int b);
/** Rellena una matriz de complex de tamaño n*n con valores aleatorios */
void fill (complex<double> *,int n);
/** Rellena una matriz de enteros de tamaño a*b con valores aleatorios */
void fill (complex<double>  *,int a,int b);

#endif // _MATRIX_HPP_
