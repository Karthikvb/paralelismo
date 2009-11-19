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

#include "matrix.hpp"
#include <stdlib.h>
#include <stdio.h>
void fill (int * m,int nfilas,int ncolumnas)
{
	for( int i = 0; i < nfilas*ncolumnas; i++ )
        m[i] = 2 * lrand48( ) - 1;
}
void fill (int * m,int n)
{
	for( int i = 0; i < n*n; i++ )
        m[i] = 2 * lrand48( ) - 1;
}
void fill (float * m,int nfilas,int ncolumnas)
{
	for( int i = 0; i < nfilas*ncolumnas; i++ )
        m[i] = 2 * drand48( ) - 1;
}
void fill (float * m,int n)
{
	for( int i = 0; i < n*n; i++ )
        m[i] = 2 * drand48( ) - 1;
}
void fill (double * m,int nfilas,int ncolumnas)
{
	for( int i = 0; i < nfilas*ncolumnas; i++ )
        m[i] = 2 * drand48( ) - 1;
}
void fill (double * m,int n)
{
	for( int i = 0; i < n*n; i++ )
        m[i] = 2 * drand48( ) - 1;
}
void fill (Complex * m,int nfilas,int ncolumnas)
{
	for( int i = 0; i < nfilas*ncolumnas; i++ )
        m[i] = Complex(2 * drand48( ) - 1,2 * drand48( ) - 1);
}
void fill (Complex * m,int n)
{
	for( int i = 0; i < n*n; i++ )
        m[i] = Complex(2 * drand48( ) - 1,2 * drand48( ) - 1);
}
int * crea_matrix(int * m,int n)
{
	m=(int *)malloc(sizeof(int)*n*n);
	return m;
}
int * crea_matrix(int * m,int a,int b)
{
	m=(int *)malloc(sizeof(int)*a*b);
	return m;
}
float * crea_matrix(float * m,int n)
{
	m=(float *)malloc(sizeof(float)*n*n);
	return m;
}
float * crea_matrix(float * m,int a,int b)
{
	m=(float *)malloc(sizeof(float)*a*b);
	return m;
}
double * crea_matrix(double * m,int n)
{
	m=(double *)malloc(sizeof(double)*n*n);
	return m;
}
double * crea_matrix(double * m,int a,int b)
{
	m=(double *)malloc(sizeof(double)*a*b);
	return m;
}
Complex * crea_matrix(Complex * m,int n)
{
	m=(Complex *)malloc(sizeof(Complex)*n*n);
	return m;
}
Complex * crea_matrix(Complex * m,int a,int b)
{
	m=(Complex *)malloc(sizeof(Complex)*a*b);
	return m;
}




