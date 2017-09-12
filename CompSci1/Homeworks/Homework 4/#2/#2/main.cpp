//Bryan Burkhardt
//CS201
//12 Oct 2015
//Homework 4, #2 - Program that calls the distance function and computes the distance an object has fallen based on the time it
//has been falling.

#include <iostream>
using namespace std;

//Function called distance that accepts the time in seconds and returns the distance the object has fallen in meters
double distance(double s)
{
    return (0.5*(9.81 * (s*s)));
}

//Main function that shows many different values passed through the distance function.
//BB: maybe say how much time has passed each time you output
int main()
{
    cout << "Distance object has fallen: " << distance(10) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(15) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(20) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(23) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(28) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(37) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(40) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(46) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(50) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(53) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(68) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(100) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(350) << " meters." << endl;
    cout << "Distance object has fallen: " << distance(500) << " meters." << endl;
    
    return 0;
    
}
