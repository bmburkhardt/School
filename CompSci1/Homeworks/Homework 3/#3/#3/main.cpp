//Bryan Burkhardt
//CS 201
//05 Oct 2015
//Homework 3 #3 - Program that accepts ints from the user until -1 is entered then outputs the sum of all the numbers.

#include <iostream>
using namespace std;

int main()
{
    //declaring variables
    int a;
    int sum = 0;
    
    //While loop that runs until the user enters -1 and adds user input to the sum
    while (a != -1)
    {
        sum += a;
        cout << "Please enter an integer. (Enter -1 to quit)" << endl;
        cin >> a;
        
    }
    
    cout << "The sum of your numbers is: " << sum << "." << endl;
    return 0;
}
