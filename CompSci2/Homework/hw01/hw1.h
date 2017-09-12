//Bryan Burkhardt
//CS202
//Homework 1: getIdFromFile and numberChase functions that retrieve data from a file from the istream and print to the ostream
#ifndef hw1_h
#define hw1_h

#include <fstream>
#include <vector>
using std::istream;
using std::ostream;
using std::ifstream;
using std::string;
using std::endl;
using std::vector;


int getIdFromFile(string fname, istream &is, ostream &os);
void numberChase(string fname, ostream &os);

#endif
