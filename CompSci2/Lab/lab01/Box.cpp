//BB: missing top of file comments
#include "Box.h"
#include <iostream>
using namespace std;

int Box::count_=0;
//Class function that sets length of box
void Box::setLength(double x)
{
    len_=x;
}

//Class function that gets length of box
double Box::getLength()
{
    return len_;
}

//Class function that prints the box using X's
void Box::print()
{
    for(int i = 0; i < len_; ++i)
    {
        for(int i = 0; i < len_; ++i)
        {
            cout << "X ";
        }
        cout << endl;
    }
}

//Class function that displays how many boxes are made
void Box::getCount()
{
    cout << "There are " << count_ << " Boxes." << endl;
}
