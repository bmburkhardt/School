//Bryan Burkhardt
//CS201
//Homework 6 - function that accepts an array and its size then copies that array and reverses the order of its indexes.

#include "HW6.h"


int * reverseArray(const int arry[], const int size)
{

    int * revArray = new int[size]; //New pointer array with size of array being passed.
    
    int len;
    if(size%2)//If size is even, then use size/2+1 for for loop.
    {
        len=size/2+1;
    }
    else//If size is else, then use size/2 for for loop.
    {
        len = size/2;
    }

    
    //For loop that assigns values to new pointer array in reverse order.
    for (int i = 0; i < len; ++i)
    {
        revArray[i] = arry[size-(i+1)];
        revArray[size-(i+1)] = arry[i];
    }
    
    return revArray;
    
}