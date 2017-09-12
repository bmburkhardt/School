//Bryan Burkhardt
//CS202
//Homework 1: getIdFromFile and numberChase functions that retrieve data from a file from the istream and print to the ostream
#include "hw1.h"

int getIdFromFile(string fname, istream &is, ostream &os)
{
    ifstream ifs(fname); //Create ifstream
    
    //Create 2 vectors to store names and ID's in
    vector<string> idVec;
    vector<int> idNum;
    
    if(!ifs.good())
    {
        return -1; //If the file doesn't exist or fails to open this will return -1
    }
    //Puts the names and ID's from the file into their proper vectors
    while(!ifs.eof())
    {
        string name;
        ifs >> name;
        int id;
        ifs >> id;
        
        idVec.push_back(name);
        idNum.push_back(id);
    }
    
    //Accepts names from the istream and scans the vectors for those names and returns thei ID numbers
    while(!is.eof())
    {
        string name;
        is >> name;
        bool found = false;
        if(name != "")
        {
            for(int i = 0; i < idVec.size()-1; ++i)
            {
                if (name == idVec[i])
                {
                    found = true;
                    os << idNum[i] << endl;
                }
            }
            if(found == false) //Prints error to the ostream if the name doesn't exist
            {
                os << "error" << endl;
            }
    
        }
    }
    return 0;
}



void numberChase(string fname, ostream &os)
{
    ifstream ifs(fname);
    ifs.seekg(0, ifs.end);    ///////////////////////////////////////
    int length = ifs.tellg(); //Used to find the size of the ifstream
    ifs.seekg(0, ifs.beg);    ///////////////////////////////////////
    
    //Create a pointer array to store the file data in
    int *arry = new int[length];
    ifs.read((char*)(arry), length);
    int i=0;
    //Goes through th epointer array and prints values to the ostream until a negative number is found
    while (i >=0 )
    {
        i=arry[i];
        os << i << "\n";
    }

}
