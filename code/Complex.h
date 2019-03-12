#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex
{
public:
	Complex(double r = 0, double i = 0) : real(r), imag(i){}
	Complex& operator=(const Complex&);
	Complex operator+(const Complex&);
	Complex operator*(const Complex&);
	double Modular();

private:
	double real;
	double imag;
};

#endif