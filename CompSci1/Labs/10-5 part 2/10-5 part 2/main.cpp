//Bryan Burkhardt
//CS 201
//05 Oct 2015
//Lab - Program that accepts an int from the user and counts to 1000 using that number.

#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Please enter a number between 0 and 1000." << endl;
    cin >> n;
    
    //for loop that counts in intervals of n between 0 and 1000 and prints out  those intervals to the console.
    for (int i = 0; i <= 1000; i+=n)
    {
        cout << i << endl;
    }
    
}
