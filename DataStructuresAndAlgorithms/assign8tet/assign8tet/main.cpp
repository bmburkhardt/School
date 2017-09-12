//
//  main.cpp
//  assign8tet
//
//  Created by Bryan Burkhardt on 12/6/16.
//  Copyright © 2016 Bryan Burkhardt. All rights reserved.
//

#include <algorithm>
using std::sort;
#include <fstream>
using std::ifstream;
#include <functional>
#include <iostream>
using std::cout;
using std::endl;
#include <iterator>
#include <map>
using std::map;
#include <string>
using std::string;
#include <vector>
using std::vector;
//using namespace std;
using std::pair;

// types
typedef pair<string, size_t> frequency_t;
typedef vector<frequency_t> words_t;

// predicates
static bool byDescendingFrequency(const frequency_t& a, const frequency_t& b)
{ return b.second > a.second; }

const struct isGTE // greater than or equal
{
    size_t inclusive_threshold;
    bool operator()(const frequency_t& record) const
    { return record.second >= inclusive_threshold; }
} over1000 = { 100000000000 }, zero  = { 0 };

/*bool greaterzero( i)
{
    return true;
}*/

bool fexists(const string& filename) {
    ifstream ifile(filename.c_str());
    return (bool)ifile;
}

int main()
{
    string fname;
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
    
    words_t words;
    {
        map<string, size_t> tally;
        
        ifstream inFile(fname);
        string s;
        while (inFile >> s)
            tally[s]++;
        
        remove_copy_if(tally.begin(), tally.end(),
                       back_inserter(words), over1000);
    }
    
    words_t::iterator begin = words.begin(),
    end = partition(begin, words.end(), zero);
    sort(begin, end, &byDescendingFrequency);
    
    for (words_t::const_iterator it=begin; it!=end; it++)
        cout << it->first << "  " << it->second << endl;
    }