//Bryan Burkhardt
//CS202
//Homework 2 - Box class header

#ifndef Box_h
#define Box_h
#include <string>
#include <ostream>

//Create a class named Box
class Box
{
public:
    //Box default ctor, sets height and width to 1 and filled.
    Box():h_(1), w_(1), type_(1)
    {}
    
    Box(int h, int w);
    Box(int h, int w, bool type);
    int getHeight();
    int getWidth();
    int getHeight() const;
    int getWidth() const;
    void setHeight(int h);
    void setWidth(int w);
    void print(std::ostream &os) const;
    std::string type();
    std::string type() const;
    
private:
    int h_;
    int w_;
    bool type_;
    
};

#endif
