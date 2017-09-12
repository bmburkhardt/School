//Bryan Burkhardt
//CS 201
//05 Oct 2015
//Lab - Program that accepts 4 doubles from the user and computes and outputs the average.

#include <iostream>
using namespace std;

int main()
{
    //Declaring variables for user input
    double a;
    double b;
    double c;
    double d;
    
    cout << "Please enter a number." << endl;
    cin >> a;
    cout << "Please enter another number." << endl;
    cin >> b;
    cout << "Please enter another number." << endl;
    cin >> c;
    cout << "Please enter another number." << endl;
    cin >> d;
    cout << "The average of your numbers is: " << (a+b+c+d)/4 << endl; //Part of the program that computes the average.
    
    return 0;
    
}