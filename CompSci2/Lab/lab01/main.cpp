//Bryan Burkhardt
//CS 202 Lab 1
//Creates a class that creates and prints out boxes. Main.cpp demonstrates different functions in the class.
#include <iostream>
#include "Box.h"
using namespace std;
int main()
{
    //Create 2 boxes using each constructor
    Box b1;
    Box b2(10);
    //Prints both boxes showing constructors work properly
    b1.print();
    b2.print();
    //Retrieves length of constructor boxes
    b1.getLength();
    b2.getLength();
    //Changes the length of the boxes made with constructors
    b1.setLength(5);
    b2.setLength(2);
    //Shows that setLength() function works
    b1.getLength();
    b2.getLength();
    cout << endl;
    //Print out new boxes with their changed sizes
    b1.print();
    cout << endl;
    b2.print();
    //Create 1 more box
    Box b3(20);
    cout << endl;
    //Print new box
    b3.print();
    cout << endl;
    //Demonstrates the getCount fucntion prints how many boxes are currently made
    b3.getCount();
    cout << endl;
    
    
    return 0;
}
