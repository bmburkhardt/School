//Bryan Burkhardt
//CS 202
//06 May 2016
//Final Exam

#ifndef Final_hpp
#define Final_hpp

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


//Part A, Create a money class

class Money
{
public:
    
    
    Money();                  //Default ctor
    Money(int d, int c);      //ctor that accepts two ints for dollars and cents
    Money(double d);          //ctor that accepts a double for dollars
    Money(const Money & rhs); //Copy ctor
    ~Money();                 //Destructor
    
    //Get and set functions for dollars and cents
    void setD(double d);
    void setC(double c);
    double getD();
    double getC();
    double getD() const;
    double getC() const;
    
    //toString function that is used in the ostream output
    std::string toString();
    std::string toString() const;
    
    //Overloaded operators
    Money operator/(double rhs);
    double operator*(Money &rhs) const;
    Money operator/(double rhs) const;
    Money operator=(const Money & rhs);
    Money &operator+=(const Money &rhs);
    Money &operator-=(const Money &rhs);
    Money &operator*=(const double &rhs);
    Money &operator/=(const double &rhs);
    friend bool operator==(const Money &lhs, const Money & rhs);
    friend bool operator !=(const Money &lhs, const Money & rhs);
    friend bool operator<(const Money &lhs, const Money & rhs);
    friend bool operator<=(const Money &lhs, const Money & rhs);
    friend bool operator>(const Money &lhs, const Money & rhs);
    friend bool operator>=(const Money &lhs, const Money & rhs);
    friend Money operator+(const Money &lhs, const Money & rhs);
    friend Money operator-(const Money &lhs, const Money & rhs);
    friend Money operator*(double lhs, Money rhs);
    friend Money operator*(Money lhs, double rhs);
    friend std::ostream &operator<<(std::ostream &os, const Money & rhs);
    
    
private:
    double d_;
    double c_;
    
};

bool operator==(const Money &lhs, const Money & rhs);
bool operator !=(const Money &lhs, const Money & rhs);
bool operator<(const Money &lhs, const Money & rhs);
bool operator<=(const Money &lhs, const Money & rhs);
bool operator>(const Money &lhs, const Money & rhs);
bool operator>=(const Money &lhs, const Money & rhs);
Money operator+(const Money &lhs, const Money & rhs);
Money operator-(const Money &lhs, const Money & rhs);
Money operator*(double lhs, Money rhs);
Money operator*(Money lhs, double rhs);
std::ostream &operator<<(std::ostream &os, const Money & rhs);



//Part B: Create a printVector function template


template <typename T>
//printVector function that accepts an ostream reference and a template vector reference
void printVector(std::ostream &os, std::vector<T> &vec)
{
    //for loop that runs through each element of the vector and prints it to the ostream
    //with a new line between each element.
    for (int i=0; i<vec.size(); ++i)
    {
        os << vec[i] << "\n";
    }
}


template <typename T>
//printVector function that accepts an ostream reference and a const template vector reference
void printVector(std::ostream &os, const std::vector<T> &vec)
{
    //for loop that runs through each element of the const vector and prints it to the ostream
    //with a new line between each element.
    for (int i=0; i<vec.size(); ++i)
    {
        os << vec[i] << "\n";
    }
}

//Part C: Create a template class called RAIIPtr
template <typename T>
class RAIIPtr
{
public:
    //ctor that accepts a T pointer
    RAIIPtr<T>(T* s)
    {
        t_=s;
    }
    
    //Destructor
    ~RAIIPtr<T>()
    {
        delete t_;
    }
    
    //* operator that returns a pointer to t_
    T & operator*()
    {
        return *t_;
    }
    
    //-> operator that return the pointer of T
    T * operator->()
    {
        return t_;
    }
    
private:
    T* t_;
    
    //Copy ctor declared
    RAIIPtr<T>(const RAIIPtr<T> & orig)
    {}
    
    //Assignment operator declared
    RAIIPtr<T> &operator=(const RAIIPtr<T> & rhs)
    {}
    
};
#endif /* Final_hpp */
