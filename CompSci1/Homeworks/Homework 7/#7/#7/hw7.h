//Bryan Burkhardt
//CS201
//hw7 header file that contains all the function headers.
#ifndef Rational_h
#define Rational_h
#include <iostream>

class Rational{
public:
    Rational();
    Rational(double n, double d);
    void setNumerator(double n);
    void setDenominator(double d);
    double getNumerator();
    double getDenominator();
    void print();
    Rational add(Rational a);
    Rational sub(Rational a);

    
private:
    double num_;
    double denom_;
};
#endif
