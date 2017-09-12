//Bryan Burkhardt
//CS 201
//07 Oct 2015
//Lab - Program that accepts 4 doubles from the user and computes the average using a function.

#include <iostream>
using namespace std;
//Function that takes 4 doubles and computes the average.
double avg(double a, double b, double c, double d)
{
    return ((a+b+c+d)/4);
}


int main()
{
    //Declaring variables for user input
    double a;
    double b;
    double c;
    double d;
    
    cout << "Please enter grade 1." << endl;
    cin >> a;
    cout << "Please enter grade 2." << endl;
    cin >> b;
    cout << "Please enter grade 3." << endl;
    cin >> c;
    cout << "Please enter grade 4." << endl;
    cin >> d;
    
    //Output of function to console
    cout << "Your average is: " << avg(a, b, c, d) << endl;
    
    return 0;
}
