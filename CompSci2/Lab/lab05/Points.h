//Bryan Burkhardt
//CS202
//Lab05 header file that contains the headers for TwoD class and ThreeD class

#ifndef TwoD_h
#define TwoD_h
#include <math.h>

//TwoD class headers
class TwoD
{
public:
    
    //Default constructor that sets x and y to 0
    TwoD():x_(0), y_(0)
    {}

    TwoD(double x, double y);
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    friend double distance(TwoD i, TwoD j);
    
protected:
    
    double x_;
    double y_;
};



//ThreeD class headers
class ThreeD: public TwoD
{
public:
    
    //Default constructor that sets x, y, z to 0
    ThreeD(double z):TwoD(0, 0), z_(0)
    {}
    
    ThreeD(double x, double y, double z);
    
    double getZ();
    void setZ(double z);
    friend double distance(ThreeD i, ThreeD j);
    
protected:
    double z_;
    
};

#endif /* TwoD_h */
