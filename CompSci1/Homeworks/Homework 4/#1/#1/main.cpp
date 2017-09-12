//Bryan Burkhardt
//CS201
//12 Oct 2015
//Homework 4, #1 - Program that calls two functions to return the area and perimeter of a rectangle.

#include <iostream>
using namespace std;
//BB:good comments

//Function that accepts two doubles and returns the area of a rectangle as a double.
double getArea(double l, double w)
{
    return l*w;
}

//Function that accepts two doubles and returns the perimeter of a rectangle as a double.
double getPerim(double l, double w)
{
    return ((2*l) + (2*w));
}


//Main function that prompts the user for length and width, then calls functions to compute and output the area and perimeter
//of a rectangle with the given measurments.
int main()
{
    //Variables used to pass to functions
    int l;
    int w;
    cout << "Please enter the length." << endl;
    cin >> l;
    cout << "Please enter the width." << endl;
    cin >> w;
    cout << "The area of your rectangle is: " << getArea(l,w) << " units." << endl;
    cout << "The perimeter of your rectangle is: " << getPerim(l,w) << " units." << endl;
    
    return 0;
}
