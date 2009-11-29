/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * libmatrix
 * Copyright (C)  2009 <>
 * 
 * libmatrix is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libmatrix is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "complex.hpp"

#include <iostream.h>

Complex::Complex()
{
	re=0;
	im=0;
 }
Complex::Complex(double r)
{
	re=r;
	im=0;
 }
Complex::Complex(double r, double i)
{
	re=r;
	im=i;
 }
Complex::Complex(const Complex &c) : re(c.re), im(c.im) { }
Complex& Complex::operator=(const Complex &c) {
  re=c.re; im=c.im;
  return *this;
}
Complex Complex::operator+(const Complex &c) const {
  return Complex(re+c.re, im+c.im);
}
Complex operator+(double d,const Complex &c) {
  return Complex(d) + c;
}
Complex Complex::operator+=(const Complex &c) const {
  return Complex(re+c.re, im+c.im);
}
Complex Complex::operator-(const Complex &c) const {
  return Complex(re-c.re, im-c.im);
}
Complex operator-(double d,const Complex &c) {
  return Complex(d) - c;
}
Complex Complex::operator*(const Complex &c) const {
  return Complex(re*c.re - im*c.im, re*c.im + c.re*im);
}
Complex operator*(double d, const Complex &c) {
  return Complex(d) * c;
}

Complex Complex::operator-() const {
  return Complex(-re, -im);
}

ostream & operator<<(ostream & canal, const Complex & c) {
  if (c.im==0)
    canal << c.re;
  else
    canal << '(' << c.re << ',' << c.im << ')' ;
  return canal;
}

