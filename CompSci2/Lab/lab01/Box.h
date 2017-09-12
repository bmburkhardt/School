//BB: missing top of file comments
#ifndef Box_h
#define Box_h
#include <iostream>
using namespace std;

class Box{
public:
    
    
    //*****Default constructors*****//
    
    //Box size 0
    Box()
    {
        len_=0;
        count_++;
    }
    
    //Box size x
    Box(double x)
    {
        len_=x;
        count_++;
    }
    
    //Destructor
    ~Box()
    {
        cout << "Box Destroyed!" << endl;
        count_--;
    }
    
    
    void setLength(double x);
    double getLength();
    void print();
    static void getCount();
    
private:
    double len_;
    static int count_;
    
    
};

#endif
