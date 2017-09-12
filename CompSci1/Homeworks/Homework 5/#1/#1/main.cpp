//Bryan Burkhardt
//CS 201
//Homework 5 - Program that has a user create a vector with size of their choice, then sorts the vector using an insertion
//sort method, then finds the index of a value the user is trying to find using a binary search function.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


//Binary search function for a vector
//BB: Well done
int binSearch(const vector<int> & data, int elem, int & steps)
{
    int beg = 0;
    int end = data.size()-1;
    int mid = (end-beg)/2;
    steps = 0;
    

    while (end-beg>1)
    {
        if (data[mid] == elem)
        {
            return mid;
        }
        else if(data[mid] < elem)
        {
            beg = mid;
            mid = beg+(end-beg)/2;
        }
        else
        {
            end = mid;
            mid = beg+(end-beg)/2;
        }
        steps++;
    }
    return -1;
}

//Insertion sort method
//BB: This is not selection sort or insertion sort. This is bubble sort.
void insertionSort(vector<int> & data, int & steps)
{
    steps = 0;
    for(int i = 1; i < data.size(); ++i)
    {
        int x = data[i];
        int j = i;
        
        while (j > 0 && data[j-1] > x)
        {
            data[j] = data[j-1];
            j = j-1;
            steps++;
        }
        data[j] = x;
    }
}



//Main function that accepts user input then creates a vector, fills with random data, sorts it, and find a certain value's
//index
int main()
{
    srand(time(0));
    int elem;
    int x;
    int steps;
    cout << "Please enter the size of you would like your vector to be." << endl;
    cin >> x;
    vector<int> ourVec(x);
    
    //Fill the vector with random data
    for(int i = 0; i < ourVec.size(); ++i)
    {
        ourVec[i] = rand()%100;
    }
    
    insertionSort(ourVec, steps);
    cout << endl;
    
    //For loop to print the vector contents for proof that sorting works
    for(int i = 0; i < ourVec.size(); ++i)
    {
        cout << ourVec[i] << " ";
    }
    
    cout << endl << endl << "Sorting took: " << steps << " steps" << endl << endl;
    
    //Prompt user for value they would like to find
    cout << "Please enter a number you would like to find in the vector." << endl;
    cin >> elem;
    
    //outputs values index using a binary search function.
    cout << endl << "The number you are looking for is located at index " << binSearch(ourVec, elem, steps) << " in the vector." << endl << endl;
    cout << "It took " << steps << " steps to find." << endl << endl;
    

    return 0;
    
}
