//Bryan Burkhardt
//CS202
//Lab 1-28: Program that reads data from a binary file and outputs the average of the numbers in the
//file.

#include <iostream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int main()
{
    //Declaration of variables
    double sum = 0;
    int count = 0;
    char * buffer = new char [4];
    
    ifstream ifs; //Creates input file stream
    ifs.open("data.dat", std::ios::binary); //opens binary file "data.dat"
    
    while(!ifs.eof()) //While loop that reads through the file while increasing the sum and
                      //incrementing the counter
    {
        ifs.read(buffer, 4);
        sum+=(float)*buffer;
        count++;
        
    }
    delete[] buffer;
    
    cout << "The count is " << count << endl;
    cout << "The average is: " << (float)sum/count << endl;
    
    return 0;
}
