
#include <iostream.h>

/**
  Clase que implementa el tipo complejo
*/
class Complex {
 protected:
  double re, im;
 public:
  Complex();
  Complex(double);
  Complex(double , double );
  Complex(const Complex &c);
  /**asignacion:*/
  Complex& operator=(const Complex &c);
  /**suma: complejo+complejo*/
  Complex operator+(const Complex &c) const;
  /**suma: double+complejo*/
  friend Complex operator+(double d, const Complex &c);
  /**suma y asigna: complejo+=complejo*/
  Complex operator+=(const Complex &c) const;
  /**resta: complejo-complejo*/
  Complex operator-(const Complex &c) const;
  /**resta: double-complejo*/
  friend Complex operator-(double d, const Complex &c);
  /**producto: complejo*complejo*/
  Complex operator*(const Complex &c) const;
  /**producto: double*complejo*/
  friend Complex operator*(double d, const Complex &c);
  /**producto: complejo*complejo*/
  Complex operator-() const;
  /**operador de salida:*/
  friend ostream & operator<<(ostream &o, const Complex &c);
};
