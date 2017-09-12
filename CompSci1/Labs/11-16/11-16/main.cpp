//Bryan Burkhardt
//CS201
//Lab 11-16 - Create a class containing functions for a complex number.

#include <iostream>
#include "Complex.h"


using namespace std;

int main()
{
    Complex com;
    Complex com1;
    Complex com2;
    Complex com3;
    //Create com1
    com1.setReal(3.0);
    com1.setImag(5.0);
    
    //Create com2
    com2.setReal(6.0);
    com2.setImag(2.0);
    
    //Create com3
    com3.setReal(2.5);
    com3.setImag(4.3);
    
    
    //Demonstrating functions: getReal and getImag
    cout << "Demonstrate setReal: " << com1.getReal() << endl;
    cout << "Demonstrate setImag: " << com1.getImag() << "i" << endl;
    
    //Adding and Subtracting two complex numbers
    com.addComplex(com1, com2);
    com.subComplex(com1, com2);
    
    //Demonstrating add, substract, and print function.
    cout << "Complex number 1: ";
    com1.print();
    cout << "Complex number 2: ";
    com2.print();
    cout << "Complex number 1 + complex number 2 = ";
    com.addComplex(com1, com2).print();
    cout << "Complex number 1 - complex number 2 = ";
    com.subComplex(com1, com2).print();
    
    com.addComplex(com1, com3).print();
    return 0;
}
