//Bryan Burkhardt
//CS201
//hw7.cpp file that contains all the required functions.
#include <iostream>
#include "hw7.h"
using namespace std;


//Default constructor
Rational::Rational()
{
    num_=1;
    denom_=1;
}

//Constructor with two parameters to set num_ and denom_
Rational::Rational(double n, double d)
{
    num_=n;
    denom_=d;
}

//Mutator functions
void Rational::setNumerator(double n)
{
    num_=n;
}

void Rational::setDenominator(double d)
{
    denom_=d;
}


//Accessor Functions

double Rational::getNumerator()
{
    return num_;
}

double Rational::getDenominator()
{
    return denom_;
}

//Print function
//Used for self testing purposes
void Rational::print()
{
    cout << num_ << endl;
    cout << denom_ << endl;
}

//Add Rationals function
Rational Rational::add(Rational a)
{
    Rational rv;

    //Common denominators
    if (a.getDenominator() == denom_)
    {
        rv.setNumerator(a.getNumerator() + num_);
        rv.setDenominator(a.getDenominator());
        return rv;
    }
    
    //Non-common denominators
    else
    {
        rv.setNumerator(((a.getNumerator()*denom_)+(num_*a.getDenominator())));
        rv.setDenominator(a.getDenominator() * denom_);
        return rv;
    }
}

//Subtract rationals functions
Rational Rational::sub(Rational a)
{
    Rational rv;
    
    //Common denominators
    if (a.getDenominator() == denom_)
    {
        rv.setNumerator(num_ - a.getNumerator());
        rv.setDenominator(a.getDenominator());
        return rv;
    }
    
    //Non-common denominators
    else
    {
        rv.setNumerator(((num_*a.getDenominator())-(a.getNumerator()*denom_)));
        rv.setDenominator(a.getDenominator() * denom_);
        return rv;
    }
}

