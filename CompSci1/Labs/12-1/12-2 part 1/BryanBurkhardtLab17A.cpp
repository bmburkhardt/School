//Bryan Burkhardt
//CS 201
//Lab 12-1 part 1
#include <iostream>
#include <fstream>
#include <string>
#include <istream>

using namespace std;

int main()
{
    string buffer;
    int result;
    string song = "song.txt";
    
    cout << "Please enter which option you would like to use." << endl;
    cout << "1. Print lyrics to console. (enter 1)." << endl;
    cout << "2. Print lyrics to file. (enter 2)." << endl;
    cin >> result;
    

    
    //Prints lyrics to console.
    if (result == 1)
    {
        ifstream ifs(song);
        while(!ifs.eof())
        {
            getline(ifs, buffer);
            cout << buffer << endl;
        }
        ifs.close();
    }
    
    //Prints lyrics to new file given by user.
    else if(result == 2)
    {
        string fname;
        cout << "Please enter name of file you would like to save lyrics to." << endl;

        //cin >> fname;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, fname);
        ofstream ofs(fname);
        ifstream ifs2(song);

    
        while(!ifs2.eof())
        {
            getline(ifs2, buffer);
            ofs << buffer << endl;
        }
        ifs2.close();
    }
    
    //If invalid input is given by user. Program stops running.
    else
    {
        cout << "Invalid input, closing program." << endl;
        return 0;
    }
    return 0;
}
