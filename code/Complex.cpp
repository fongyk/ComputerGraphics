#include "Complex.h"

Complex& Complex::operator=(const Complex& rhs)
{
	real = rhs.real;
	imag = rhs.imag;
	return *this;
}
Complex Complex::operator+(const Complex& rhs)
{
	real += rhs.real;
	imag += rhs.imag;
	return *this;
}
Complex Complex::operator*(const Complex& rhs)
{
	double tmpreal1 = real;
	double tmpreal2 = rhs.real;
	real = real * rhs.real - imag * rhs.imag;
	imag = tmpreal1 * rhs.imag + imag * tmpreal2;
	//if (this != &rhs)
	//{
	//	double tmpreal = real;
	//	real = real * rhs.real - imag * rhs.imag;
	//	imag = tmpreal * rhs.imag + imag * rhs.real;
	//}
	//else
	//{
	//	double tmpreal = real;
	//	real = real * real - imag * imag;
	//	imag = tmpreal * imag + imag * tmpreal;
	//}
	return *this;
}
double Complex::Modular()
{
	return std::sqrt(real * real + imag * imag);
}