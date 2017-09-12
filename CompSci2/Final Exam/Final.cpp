//Bryan Burkhardt
//CS202
//06 May 2016
//Final Exam

#include "Final.h"
#include <iostream>


//Default ctor
Money::Money()
{
    d_=0;
    c_=0;
}

//ctor that accepts two ints for dollars and cents
Money::Money(int d, int c)
{
    d_=d;
    c_=c;
}

//ctor that accepts a double for dollars
Money::Money(double d)
{
    d_=d;
    c_='\0'; //Sets the value of cents to null
}

//Copy ctor
Money::Money(const Money & rhs)
{
    d_=rhs.getD();
    c_=rhs.getC();
}
//Destructor
Money::~Money()
{
}

//Get and set functions for dollars and cents
void Money::setD(double d)
{
    d_=d;
}
void Money::setC(double c)
{
    c_=c;
}
double Money::getD()
{
    return d_;
}
double Money::getC()
{
    return c_;
}
double Money::getD() const
{
    return d_;
}
double Money::getC() const
{
    return c_;
}

//toString function is used for printing to the ostream
std::string Money::toString()
{
    std::ostringstream os;
    os << '$' << d_ << ".0" << c_;
    return os.str();
}
std::string Money::toString() const
{
    std::ostringstream os;
    os << '$' << d_ << ".0" << c_;
    return os.str();
}

//Code for operators

//Division operator that divides a Money object by a double
Money Money::operator/(double rhs)
{
    Money rv(d_/rhs, c_/rhs);
    return rv;
}

//const version of division operator.
Money Money::operator/(double rhs) const
{
    Money rv(d_/rhs, c_/rhs);
    return rv;
}

//Assignment operator that assigns a Money object to another Money object
Money Money::operator=(const Money & rhs)
{
    if(!(&rhs==this))
    {

        d_=rhs.getD();
        c_=rhs.getC();
        
    }
    return *this;
}

//+= operator for two Money objects
Money &Money::operator+=(const Money &rhs)
{
    d_+=rhs.getD();
    c_+=rhs.getC();
    return *this;
}

//-= operator for two Money objects
Money &Money::operator-=(const Money &rhs)
{
    d_=(d_-rhs.getD());
    c_=(c_-rhs.getC());
    return *this;
}

//*= operator for two Money objects
Money &Money::operator*=(const double &rhs)
{
    d_=(d_*rhs);
    c_=(c_*rhs);
    return *this;
}

// /= operator for two Money objects
Money &Money::operator/=(const double &rhs)
{
    d_=(d_/rhs);
    c_=(c_/rhs);
    return *this;
}

// == operator that compares if two Money objects are equal to each other
bool operator==(const Money &lhs, const Money & rhs)
{
    if(lhs.d_!=rhs.d_)
    {
        return false;
    }
    if(lhs.c_!=rhs.c_)
    {
        return false;
    }
    return true;
}

// != operator that checks if two Money objects are different
bool operator !=(const Money &lhs, const Money & rhs)
{
    return !(lhs==rhs);
}

// < operator for two Money objects
bool operator<(const Money &lhs, const Money & rhs)
{
    if(lhs.d_>rhs.d_)
    {
        return false;
    }
    if((lhs.d_==rhs.d_) && (lhs.c_>=rhs.c_))
    {
        return false;
    }
    return true;
}

// <= operator for two Money objects
bool operator<=(const Money &lhs, const Money & rhs)
{
    return !(lhs>rhs);
}

// > operator for two Money objects
bool operator>(const Money &lhs, const Money & rhs)
{
    if(lhs.d_<rhs.d_)
    {
        return false;
    }
    if((lhs.d_==rhs.d_) && (lhs.c_<=rhs.c_))
    {
        return false;
    }
    return true;
}

// >= operator for two Money objects
bool operator>=(const Money &lhs, const Money & rhs)
{
    return !(lhs<rhs);
}

// Addition operator for two Money objects
Money operator+(const Money &lhs, const Money & rhs)
{
    Money rv((lhs.d_+rhs.d_), (lhs.c_+rhs.c_));
    return rv;
}

// Substraction operator for two Money objects
Money operator-(const Money &lhs, const Money & rhs)
{
    Money rv((lhs.d_-rhs.d_), (lhs.c_-rhs.c_));
    return rv;
}

// Multiplication operator that accepts a double and a Money. Returns a Money
Money operator*(double lhs, Money rhs)
{
    Money rv((rhs.d_*lhs), (rhs.c_*lhs));
    return rv;
}

// Multiplication operator that accepts a Money and a double. Returns a Money
Money operator*(Money lhs, double rhs)
{
    Money rv((lhs.d_*rhs), (lhs.c_*rhs));
    return rv;
}

// ostream operator that prints a Money object to the ostream in the format of "$x.xx"
std::ostream &operator<<(std::ostream &os, const Money & rhs)
{
    if (rhs.d_==0 && rhs.c_==0) //If statement for default Money object
    {
        os << rhs.toString();
    }
    else if (rhs.getC() < 10 && rhs.getC() != '\0') //If/else statement for if c_ has a value less than 10
    {
        os << rhs.toString();
    }
    else if (rhs.c_=='\0' && rhs.d_>0) // If/else statement for if c_ has no value and overall value is positive
    {
        os << '$' << std::setprecision(2) << std::fixed << rhs.d_;
    }
    else if (rhs.c_=='\0' && rhs.d_<0) // If/else statement for if c_ has no value and overall value is negative
    {
        os << "-$" << std::setprecision(2) << std::fixed << (rhs.d_)/-1.0;
    }
    return os;
}