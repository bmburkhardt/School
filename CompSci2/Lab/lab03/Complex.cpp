#include "Complex.h"

//Default constuctors
Complex::Complex()
{
    real_=0;
    imag_=0;
}

Complex::Complex(double x)
{
    real_=x;
    imag_=x;
}

Complex::Complex(double real, double imag)
{
    real_=real;
    imag_=imag;
}

//get and set functions
double Complex::getReal() const
{
    return real_;
}
double Complex::getImag() const
{
    return imag_;
}
double Complex::getReal()
{
    return real_;
}
double Complex::getImag()
{
    return imag_;
}
void Complex::setReal(double real)
{
    real_=real;
}
void Complex::setImag(double imag)
{
    imag_=imag;
}
//BB: I feel this should print out a-bi instead of a+-bi
void Complex::print()
{
    cout << real_ << " + " << imag_ << "i" << endl;
}

//operator functions

Complex operator+(const Complex &lhs, Complex &rhs) // adds complex numbers
{
    Complex temp;
    temp.setReal(lhs.getReal()+rhs.getReal());
    temp.setImag(lhs.getImag()+rhs.getImag());
    return temp;
}

Complex operator-(const Complex &lhs, Complex &rhs) // subtracts complex numbers
{
    Complex temp;
    temp.setReal(lhs.getReal()-rhs.getReal());
    temp.setImag(lhs.getImag()-rhs.getImag());
    return temp;
}
Complex operator*(const Complex &lhs, Complex &rhs) // multiply complex numbers
{
    Complex temp;
    temp.setReal((lhs.getReal()*rhs.getReal())-(lhs.getImag()*rhs.getImag()));
    temp.setImag((lhs.getImag()*rhs.getReal())+(lhs.getReal()*rhs.getImag()));
    return temp;
}
Complex operator/(const Complex &lhs, Complex &rhs) //divides complex numbers
{
    Complex temp;
    temp.setReal(((lhs.getReal()*rhs.getReal())+(lhs.getImag()*rhs.getImag()))/((rhs.getReal()*rhs.getReal())+(rhs.getImag()*rhs.getImag())));
    temp.setImag(((lhs.getReal()*rhs.getImag()*(-1))+(lhs.getImag()*rhs.getReal()))/((rhs.getReal()*rhs.getReal())+(rhs.getImag()*rhs.getImag())));

    return temp;
}

