// da3.h
// Bryan Burkhardt
// 01 Oct 2016
// CS 311 - Assignment 3
// Source file for assignment 3

#include "da3.h"       // For Assignment 3 prototypes & templates
#include <functional>
using std::function;


// callBetween function.
// (See header for docs.)
void callBetween(const std::function<void()> & start,
                 const std::function<void()> & middle,
                 const std::function<void()> & finish)
{
    start();
    try
    {
        middle();
    }
    catch(...)
    {
        finish();
        throw;
    }
    finish();
}
// primeRecursion function.
// Workhorse for isPrime function.
// Pre:
//      None.
// Post:
//      Returns true if number is prime or false if number is not prime.
bool primeRecursion(int n, int k)
{
    // BASE CASES
    if (k*k < n)
    {
        return true;
    }
    if (n%k == 0)
    {
        return false;
    }
    
    // RECURSIVE CASE
    else
    {
        return primeRecursion(n, k-1);
    }
}

// isPrime function.
// (See header for docs.)
bool isPrime(int n)
{
    // BASE CASE
    if (n<=1)
    {
        return false;
    }
    
    // RECURSIVE CASE
    else
    {
        return primeRecursion(n, n-1);
    }
    

}



