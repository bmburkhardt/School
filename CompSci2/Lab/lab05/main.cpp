//Bryan Burkhardt
//CS 202
//Lab 5 - inheritance lab that uses 2-dimensional and 3-dimensional points

#include <iostream>
#include "Points.h"
using namespace std;
int main()
{
    //Demonstrates constructing two different TwoD objects
    TwoD twoOne(2, 2);
    TwoD twoTwo(3, 4);
    
    //Demonstrates constructing two different ThreeD objects
    ThreeD threeOne(3, 4, 5);
    ThreeD threeTwo(6, 7, 8);
    
    //Calculates the distance between two TwoD objects
    cout << distance(twoOne, twoTwo)<< endl;
    
    //Calculates the distance between two ThreeD objects
    cout << distance(threeOne, threeTwo) << endl;
    
    return 0;
}
