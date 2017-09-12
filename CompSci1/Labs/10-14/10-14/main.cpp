//Bryan Burkhardt
//CS201
//Lab 10-14
//Program that creates an array with a size of 100 and fills it with random numbers then outputs the sum of those numbers.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0)); //To better randomize the sum
    const int SIZE = 100;
    int array[SIZE]; //Creates array called array with 100 empty slots
    int sum = 0;
    
    //For loop to add random values to array and add them all to the variable sum
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand()%6+1;
        sum += array[i];
    }
    
    cout << "The sum of the array values is: " << sum << endl; //outputs sum of all numbers in array.
    
    return 0;
    
}