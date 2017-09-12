//Bryan Burkhardt
//CS 201
//Lab 10-30: Creates a pointer array with size given by user. Fill array with random data. Deletes memory location of array

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    
    srand(time(0));
    int size;
    
    cout << "Please enter a size." << endl;
    cin >> size;
    
    //Creates a new pointer array with size given by user.
    int * iptr = new int[size];
    
    
    //for loop that fills pointer array with random numbers and prints out the values stored in it.
    cout << endl;
    for(int i = 0; i < size; ++i)
    {
        *(iptr + i) = rand()%100;
        cout << *(iptr + i) << endl;
    }
    
    //Deletes the memory locations of the pointer array.
    delete [] iptr;
    
    return 0;
}