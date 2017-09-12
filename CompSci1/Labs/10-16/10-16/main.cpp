//Bryan Burkhardt
//CS 201
//16 Oct 2015
//Lab 10-16, program that calls the function mean and outputs the avg of the numbers in the array.

#include <iostream>

using namespace std;

//function that accepts an array of doubles and its size and returns the average of the numbers in the array.
double mean(double data[], int size)
{
    double sum = 0;
    
    for(int i = 0; i < size; i++)
    {
        sum += data[i];
    }
    
    return sum/size;
}

//Main function that creates and array, fills it with values, and calls the mean() function
int main()
{
    const int SIZE = 20;
    double arry[SIZE];
    
    //For loop that fills array with values
    for (int i = 0; i < SIZE; i++)
    {
        arry[i] = i;
    }
    
    cout << mean(arry, SIZE) << endl;

    return 0;
}