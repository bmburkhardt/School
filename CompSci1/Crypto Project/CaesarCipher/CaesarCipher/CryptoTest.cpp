/***************************
*
* This is the testing program for the CS201 Fall 2015
* Crypto project
*
*
* Brandon Marken (bamarken@alaska.edu)
* 
* 
*
******************************/
#include "Crypto.h"
#include "Crypto.h" //double inclusion check

#include <iostream>
#include <cstring>
#include <typeinfo> //to check types

using namespace std;

bool charMemCmp(const char arry[], char * arry2, const int size)
{
    for(int i=0; i<size; ++i)
    {   
        if (arry[i]!=arry2[i])
        {return false;}
    }
    return true;
}

void assignString(char s1[], const char * s2)
{
    int length=strlen(s2);
    for(int i=0; i<length+1; ++i)
    {
        s1[i]=s2[i];
    }
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

//tests the caesar cipher
void testCaesar(Tester & t)
{
    char cipherText[]="WITH THE LIGHTS OUT";
    char * res=encryptCaesar(cipherText,3);
    t.test(charMemCmp("ZLWK WKH OLJKWV RXW",res, strlen(cipherText)), "Testing Caesar Cipher Encrypt With Shift of 3");
    delete[] res;

    char plainText[]="ZLWK WKH OLJKWV RXW";
    res=decryptCaesar(plainText,3);
    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Decrypt With Shift of 3");
    delete[] res;

    res=encryptCaesar(cipherText,0);
    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Encrypt With Shift of 0");
    delete[] res;

    res=decryptCaesar(cipherText,0);
    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Decrypt With Shift of 0");
    delete[] res;

    res=encryptCaesar(cipherText,15);
    t.test(charMemCmp("LXIW IWT AXVWIH DJI",res, strlen(cipherText)), "Testing Caesar Cipher Encrypt With Shift of 15");
    delete[] res;

    assignString(plainText,"LXIW IWT AXVWIH DJI");
    res=decryptCaesar(plainText,15);

    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Decrypt With Shift of 15");
    delete[] res;

    res=encryptCaesar(cipherText,26);
    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Encrypt With Shift of 26");
    delete[] res;

    res=decryptCaesar(cipherText,26);
    t.test(charMemCmp("WITH THE LIGHTS OUT",res, strlen(cipherText)), "Testing Caesar Cipher Decrypt With Shift of 26");
    delete[] res;

}

void testMorse(Tester & t)
{
    char plainText[]="NICE MARMOT";
    char plainText2[]="AND PROUD WE ARE OF ALL OF THEM";
    char plainText3[]="HE WAS THE LAZIEST MAN IN LOS ANGELES COUNTY";
    char cipherText[]="-. .. -.-. .     -- .- .-. -- --- -";
    char cipherText2[]=".- -. -..     .--. .-. --- ..- -..     .-- .     .- .-. .     --- ..-.     .- .-.. .-..     --- ..-.     - .... . --";
    char cipherText3[]=".... .     .-- .- ...     - .... .     .-.. .- --.. .. . ... -     -- .- -.     .. -.     .-.. --- ...     .- -. --. . .-.. . ...     -.-. --- ..- -. - -.--";
    
    char* testVal=encryptMorse(plainText);
    t.test(charMemCmp("-. .. -.-. .     -- .- .-. -- --- -", testVal,35), "Testing Morse Code Encrypt Plaintext1");
    delete[] testVal;

    testVal=encryptMorse(plainText2);
    t.test(charMemCmp(".- -. -..     .--. .-. --- ..- -..     .-- .     .- .-. .     --- ..-.     .- .-.. .-..     --- ..-.     - .... . --", testVal,strlen(cipherText2)) ,"Testing Morse Code Encrypt Plaintext2");
    delete[] testVal;

    testVal=encryptMorse(plainText3);
    t.test(charMemCmp(".... .     .-- .- ...     - .... .     .-.. .- --.. .. . ... -     -- .- -.     .. -.     .-.. --- ...     .- -. --. . .-.. . ...     -.-. --- ..- -. - -.--", testVal,strlen(cipherText3)), "Testing Morse Code Encrypt Plaintext3");
    delete[] testVal;

    testVal=decryptMorse(cipherText);
    t.test(charMemCmp("NICE MARMOT", testVal, strlen(plainText)), "Testing Morse Code Decrypt Ciphertext 1");
    delete[] testVal;

    testVal=decryptMorse(cipherText2);
    t.test(charMemCmp("AND PROUD WE ARE OF ALL OF THEM", testVal, strlen(plainText2)), "Testing Morse Code Decrypt Ciphertext 2");
    delete[] testVal;

    testVal=decryptMorse(cipherText3);
    t.test(charMemCmp("HE WAS THE LAZIEST MAN IN LOS ANGELES COUNTY", testVal, strlen(plainText3)), "Testing Morse Code Decrypt Ciphertext 3");
    delete[] testVal;
}
void testSub(Tester & t)
{
    char key1[26]={'Z','Y','X','W','V','U','T','S','R','Q','P','O','N','M','L','K','J','I','H','G','F','E','D','C','B','A'};
    char key2[26]={'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M'};
    char key3[26]={'M','N','B','V','C','X','Z','L','K','J','H','G','F','D','S','A','P','O','I','U','Y','T','R','E','W','Q'};

    char plainText[]="Where is my mind";

    char * test = encryptSub(plainText,key1);
    t.test(charMemCmp("DSVIV RH NB NRMW", test, strlen(plainText)), "Texting Substitution Cipher Encrypt Key1");
    delete [] test;

    test = encryptSub(plainText,key2);
    t.test(charMemCmp("VITKT OL DN DOFR", test, strlen(plainText)), "Texting Substitution Cipher Encrypt Key2");
    delete [] test;

    test = encryptSub(plainText,key3);
    t.test(charMemCmp("RLCOC KI FW FKDV", test, strlen(plainText)), "Texting Substitution Cipher Encrypt Key3");
    delete [] test;

    char cipher1[]="DSVIV RH NB NRMW";
    char cipher2[]="VITKT OL DN DOFR";
    char cipher3[]="RLCOC KI FW FKDV";

    test = decryptSub(cipher1,key1);
    t.test(charMemCmp("WHERE IS MY MIND", test, strlen(plainText)), "Texting Substitution Cipher Decrypt Key1");
    delete [] test;

    test = decryptSub(cipher2,key2);
    t.test(charMemCmp("WHERE IS MY MIND", test, strlen(plainText)), "Texting Substitution Cipher Decrypt Key2");
    delete [] test;

    test = decryptSub(cipher3,key3);
    t.test(charMemCmp("WHERE IS MY MIND", test, strlen(plainText)), "Texting Substitution Cipher Decrypt Key3");
    delete [] test;

}


int main()
{
  Tester t;     //our tester
  cout << "Testing Caesar Cipher Functions" << endl;
  testCaesar(t);

  cout << "Testing Morse Code Functions" << endl;
  testMorse(t);

  cout << "Testing Substitution Cipher Functions" << endl;
  testSub(t);
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
