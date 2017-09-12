// wordcount.cpp
// Bryan Burkhardt
// 06 Dec 2016
// CS 311 - Assignment 8
// Cpp file for Assignment 8.

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <map>
using std::map;
#include <string>
using std::string;
#include <utility>
using std::size_t;


typedef map<string, size_t> wordCount;

// countWords
// Pre:
//      None.
// Post: 
//      Fills map with unique words and how many times that word occurs
// Exception Neutral
// Strong Guarantee
void countWords(ifstream& in, wordCount& words)
{
    string str;
    while (in >> str)
    {
        ++words[str];
    }
}

// fileExists
// Pre:
//      None.
// Post:
//      Returns true if passed file exists.
//      Returns false if passed file does not exist.
// Exception Neutral
// No-Throw Guarantee
bool fileExists(const string& fname)
{
    ifstream file(fname.c_str());
    return (bool)file;
}

//*********************************************************************************
// Main
//*********************************************************************************
int main()
{
    
    string fname;
    bool status = false;
    
    // while loop that prompts user to input name of file they wish to scan through.
    // Pre:
    //      None.
    // Post:
    //      if (file exists), exits while loop and continues program.
    //      if (file does not exist), prompts user to enter file name again.
    //      if (input == 0), program exits and returns 0.
    while(!status){
        cout << "Please enter a file name or 0 to exit" << endl;
        getline(std::cin, fname);
        ifstream ifs(fname);
        if(fileExists(fname))
        {
            status = true;
        }
        else if(fname=="0")
        {
            return 0;
        }
    }
    
    ifstream infile(fname); // New ifstream of passed file.
    wordCount w;            // Creates map
    countWords(infile, w);  // Calls countWord function, passing the input file and map
    
    cout << "Number of Distinct Words: " << w.size() << endl;
    
    // Loop that prints distinct words and how many times each occurs.
    for (wordCount::iterator p = w.begin(); p != w.end(); ++p)
    {
        cout << p->first << " "<< p->second << endl;
    }
    return 0;
}