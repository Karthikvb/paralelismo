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


int * crea_matrix(int *,int);
int * crea_matrix(int *,int,int);
float * crea_matrix(float *,int);
float * crea_matrix(float *,int,int);
double * crea_matrix(double *,int);
double * crea_matrix(double *,int,int);
void fill (int *,int);
void fill (int *,int,int);
void fill (float *,int);
void fill (float *,int,int);
void fill (double *,int);
void fill (double *,int,int);
#endif // _MATRIX_HPP_
