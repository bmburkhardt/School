//Bryan Burkhardt
//CS 201
//05 Oct 2015
//Homework 3 #1 - Program that accepts 2 numbers from the user and either adds, substract, multiplies, or divides based
//on the users choice. Will keep prompting user as long as an invalid choice is entered

#include <iostream>
using namespace std;

int main()
{
    //declare variables and prompt user for input on which variables and choice they would like to use
    double a;
    double b;
    int choice;
    cout << "Please enter a number." << endl;
    cin >> a;
    cout << "Please enter another number." << endl;
    cin >> b;
    cout << "Please select what you would like to do to your numbers." << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;
    cout << "Please enter 1, 2, 3, or 4" << endl;
    cin >> choice;
    
    //while loop that ensures the users input is valid for what they would like to do with their numbers
    while (choice != 1 && choice != 2 && choice != 3 && choice !=4)
    {
        cout << "Your choice is unknown. Please enter 1, 2, 3, or 4" << endl;
        cin >> choice;
    }
    
    //if/else statements to perform a certain calculation based on users choice
    if (choice == 1)
    {
        cout << a << " + " << b << " = " << a+b << endl;
    }
    else if(choice == 2)
    {
        cout << a << " - " << b << " = " << a-b << endl;
    }
    else if(choice == 3)
    {
        cout << a << " * " << b << " = " << a*b << endl;
    }
    else if(choice == 4)
    {
        cout << a << " / " << b << " = " << a/b << endl;
    }
    
    return 0;
    
}
