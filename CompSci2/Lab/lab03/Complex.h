#ifndef Complex_hpp
#define Complex_hpp

#include <iostream>
using std::cout;
using std::endl;


class Complex
{
public:
    Complex();
    Complex(double x);
    Complex(double real, double imag);
    
    double getReal();
    double getImag();
    double getReal() const;
    double getImag() const;
    void setReal(double real);
    void setImag(double imag);
    void print();
    
    friend Complex operator+(const Complex &lhs, Complex &rhs);
    friend Complex operator-(const Complex &lhs, Complex &rhs);
    friend Complex operator*(const Complex &lhs, Complex &rhs);
    friend Complex operator/(const Complex &lhs, Complex &rhs);
    
    
    
private:
    double real_;
    double imag_;

    
    
};

#endif
