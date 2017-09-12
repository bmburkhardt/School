//
//  main.cpp
//  Assignment 8
//
//  Created by Bryan Burkhardt on 12/2/16.
//  Copyright © 2016 Bryan Burkhardt. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <sstream>
#include <vector>
using std::vector;

bool fexists(const string& filename) {
    ifstream ifile(filename.c_str());
    return (bool)ifile;
}

/*template <typename T>
vector uniqueCount(ifstream ifs)
{
    return 1;
}*/

int main() {
    
    string fname;
    //ifstream ifs;
    bool status = false;

    
    while(!status){
        cout << "Please enter a file name or 0 to exit" << endl;
        getline(std::cin, fname);
        ifstream ifs(fname);
        if(fexists(fname))
        {
            status = true;
        }
        else if(fname=="0")
        {
            return 0;
        }
        
    }
    
    
    return 0;
}
