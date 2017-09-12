/***************************
 *
 * This is the testing program for CS201 Homework 6
 * Fall 2014.
 * Brandon Marken (bamarken@alaska.edu)
 *
 *
 *
 ******************************/
#include "HW6.h"
#include "HW6.h" //double inclusion check

#include <iostream>
#include <cstring>
#include <typeinfo> //to check types
using namespace std;

bool intMemCmp(const int arry[], int * arry2, const int size)
{
    for(int i=0; i<size; ++i)
    {
        if (arry[i]!=arry2[i])
        {return false;}
    }
    return true;
}

// ************************************************************************
// Testing Package:
//     Class Tester - For Tracking Tests
// ************************************************************************


// class Tester
// For extremely simple unit testing.
// Keeps track of number of tests and number of passes.
// Use test (with success/failure parameter) to do a test.
// Get results with numTests, numPassed, numFailed, allPassed.
// Restart testing with reset.
// Invariants:
//     countTests_ == number of tests (calls to test) since last reset.
//     countPasses_ == number of times function test called with true param
//      since last reset.
//     0 <= countPasses_ <= countTests_.
//     tolerance_ >= 0.
class Tester {
    
    // ***** Tester: ctors, dctor, op= *****
public:
    
    // Default ctor
    // Sets countTests_, countPasses_ to zero, tolerance_ to given value
    // Pre: None.
    // Post:
    //     numTests == 0, countPasses == 0, tolerance_ == abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    Tester(double theTolerance = 0.0000001)
    :countTests_(0),
    countPasses_(0),
    tolerance_(theTolerance >= 0 ? theTolerance : -theTolerance)
    {}
    
    // Compiler-generated copy ctor, copy op=, dctor are used
    
    // ***** Tester: general public functions *****
public:
    
    // test
    // Handles single test, param indicates pass/fail
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (success)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    //  - Assuming exceptions have not been turned on for cout.
    void test(bool success,
              const std::string & testName = "")
    {
        ++countTests_;
        if (success) ++countPasses_;
        
        std::cout << "    ";
        if (testName != "")
        {
            std::cout << "Test: "
            << testName
            << " - ";
        }
        std::cout << (success ? "passed" : "********** FAILED **********")
        << std::endl;
    }
    
    // ftest
    // Does single floating-point test.
    // Tests passes iff difference of first two values is <= tolerance.
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (abs(val1-val2) <= tolerance_)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    void ftest(double val1,
               double val2,
               const std::string & testName = "")
    { test(val1-val2 <= tolerance_ && val2-val1 <= tolerance_, testName); }
    
    // reset
    // Resets *this to default constructed state
    // Pre: None.
    // Post:
    //     countTests_ == 0, countPasses_ == 0
    // Does not throw (No-Throw Guarantee)
    void reset()
    {
        countTests_ = 0;
        countPasses_ = 0;
    }
    
    // numTests
    // Returns the number of tests that have been done since last reset
    // Pre: None.
    // Post:
    //     return == countTests_
    // Does not throw (No-Throw Guarantee)
    int numTests() const
    { return countTests_; }
    
    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPasses_
    // Does not throw (No-Throw Guarantee)
    int numPassed() const
    { return countPasses_; }
    
    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses_ == numTests_
    // Does not throw (No-Throw Guarantee)
    int numFailed() const
    { return countTests_ - countPasses_; }
    
    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses_ == countTests_)
    // Does not throw (No-Throw Guarantee)
    bool allPassed() const
    { return countPasses_ == countTests_; }
    
    // setTolerance
    // Sets tolerance_ to given value
    // Pre: None.
    // Post:
    //     tolerance_ = abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    void setTolerance(double theTolerance)
    { tolerance_ = (theTolerance >= 0 ? theTolerance : -theTolerance); }
    
    // ***** Tester: data members *****
private:
    
    int countTests_;    // Number of tests done since last reset
    int countPasses_;   // Number of tests passed since last reset
    double tolerance_;  // Tolerance for floating-point near-equality tests
    
};  // end class Tester

//the test reverse function
void testReverse(Tester & t)
{
    int arr1[]={0};
    int arr2[]={0,1};
    int arr3[]={0,1,2,3,4,5};
    int arr4[]={0,1,2,3,4,5,6,7,8,9,10};
    int * result = reverseArray(arr1,1);
    
    int arrTest2[]={1,0};
    int arrTest3[]={5,4,3,2,1,0};
    int arrTest4[]={10,9,8,7,6,5,4,3,2,1,0};
    //comparing then deleting memory
    t.test(intMemCmp(arr1,result,1),"Testing Array of Size 1");
    delete[] result;
    
    result=reverseArray(arr2,2);
    t.test(intMemCmp(arrTest2,result,2),"Testing Array of Size 2");
    delete[] result;
    
    result=reverseArray(arr3,6);
    t.test(intMemCmp(arrTest3,result,6),"Testing Array of Size 6");
    delete[] result;
    
    result=reverseArray(arr4,11);
    t.test(intMemCmp(arrTest4,result,11),"Testing Array of Size 11");
    delete[] result;
    
}

int main()
{
    Tester t;     //our tester
    cout << "Testing Reverse Function" << endl;
    testReverse(t);
    
    if (t.allPassed())
    {
        cout << "All tests passed!" << endl;
    }
    else
    {
        cout << t.numFailed() << " tests failed" << endl;
    }
    return 0;
}