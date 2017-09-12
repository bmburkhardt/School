//Bryan Burkhardt
//CS 201
//05 Oct 2015
//Homework 3 #2 - Program that computes the factorial value of a number given by the user.

#include <iostream>
using namespace std;

int main()
{
    //Declaring variables
    double a;
    double fact = 1;
    
    cout << "Please enter a number" << endl;
    cin >> a;
    
    //For loop that computes the factorial for the users input
    for (int i = 1; i <= a; i++)
    {
        fact = fact * i;
        cout << fact << endl;
    }
   
    cout << "The factorial of " << a << " is " << fact << endl;
    
    return 0;
    
}
