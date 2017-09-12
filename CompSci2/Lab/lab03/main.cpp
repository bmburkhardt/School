//Bryan Burkhardt
//CS202
//Lab 2-2: Complex class which contains operator functions and then overloads them in the main program.
#include <iostream>
#include "Complex.h"

int main() {
    
    //BB: the complex tests are nice, but I would also like some simple ones as well
    // *** DEMONSTRATES CONSTRUCTORS AND OPERATOR FUNCTIONS WORK PROPERLY ***
    Complex a(1, 1);
    Complex b(2, 2);
    Complex c = a+b; // should = 7 + 7i
    Complex d = a-b-a-b; // should = -4 + -4i
    Complex e = a*b*b;   // should = -8 + 8i
    Complex f = a/b/b;   // should = 0.125 - 0.125i
    c.print();
    d.print();
    e.print();
    f.print();
    
    //Just to demonstrate other constructors
    Complex g;
    Complex h(4);
    g.print();
    h.print();
    return 0;
}
