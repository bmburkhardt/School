#include <iostream>
#include "Complex.h"
using namespace std;

void Complex::setReal(double real)
{
    real_=real;
}

void Complex::setImag(double imag)
{
    imag_=imag;
}

double Complex::getReal()
{
    return real_;
}

double Complex::getImag() 
{
    return imag_;
}

void Complex::print()
{
    cout << "(" << real_ << " + " << imag_ << "i)" << endl;
}



Complex Complex::addComplex(Complex a, Complex b)
{

    Complex z;
    z.setReal(a.getReal() + b.getReal());
    z.setImag(a.getImag() + b.getImag());
    return z;
}

Complex Complex::subComplex(Complex a, Complex b)
{

    Complex z;
    z.setReal(a.getReal() - b.getReal());
    z.setImag(a.getImag() - b.getImag());
    return z;
}