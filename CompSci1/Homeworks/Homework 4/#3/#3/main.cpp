//Bryan Burkhardt
//CS201
//12 Oct 2015
//Homework 4, #3 - Program that uses a function called multTable that displays the multiplication table for a number given
//by the user.

#include <iostream>
#include <iomanip>
using namespace std;

//Function that accepts an int from the user and prints out the multiplication table to the console.
void multTable(int n)
{
    //for loop that restricts the multiplication table from exceeding the given number.
    for (int i = 0; i <= n; i++)
    {
        cout << n << " * " << right << setw(3) << i << " = " << setw(5) << right << n*i << endl;
    }
}


//Main function that calls for user input to run multTable function.
int main()
{
    int n;
    cout << "Please enter a number you would like to see the multiplication table for." << endl;
    cin >> n;
    multTable(n);
    
    return 0;
}
