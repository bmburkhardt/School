//Bryan Burkhardt
//CS202
//Homework2 - Box class source files
#include "Box.h"

//Box ctor that accepts width and height and creates a filled box with those values
Box::Box(int w, int h)
{
    h_=h;
    w_=w;
    type_=true;
}

//Box ctor that accepts a width, height, and bool then creates a box of given dimensions either filled or hollow
Box::Box(int w, int h, bool type)
{
    h_=h;
    w_=w;
    type_=type;
}

//type function that returns a string of "Filled" or "Hollow" based on what type of box the function
    //is used on.
std::string Box::type()
{
    if(type_)
    {
        return "Filled";
    }
    else
    {
        return "Hollow";
    }
}

//type function that returns a string of "Filled" or "Hollow" based on what type of box the function
//is used on.
std::string Box::type() const
{
    if(type_)
    {
        return "Filled";
    }
    else
    {
        return "Hollow";
    }
}

int Box::getHeight()
{
    return h_;
}

int Box::getWidth()
{
    return w_;
}

int Box::getHeight() const
{
    return h_;
}

int Box::getWidth() const 
{
    return w_;
}

void Box::setHeight(int h)
{
    h_=h;
}

void Box::setWidth(int w)
{
    w_=w;
}

//Print function that prints filled or hollow boxes to the ostream using "x" and " "
void Box::print(std::ostream &os) const
{
    //If statement that checks if the box is filled. If it is, the box is printed to the ostream.
    if (type_)
    {
        for(int i=0; i<h_; ++i)
        {
            for(int j=0; j<w_; ++j)
            {
                os << "x";
            }
            os << std::endl;
            
        }
    }
    //The following code prints hollow boxes to the ostream
    else
    {
        //If the box's dimensions are 1x1 or smaller
        if(w_<=1 && h_<=1 && type_==false)
        {
            os << "x";
            os << std::endl;
        }
        
        //If the box's dimensions are greater than 1x1
        else
        {
            //For loop that prints the top(closed) part of the box
            for(int i=0; i<w_; ++i)
            {
                os << "x";
            }
            os << '\n';
            //For loop that prints the hollow insides of the box
            for(int i=1; i<h_-1; ++i)
            {
                os<<'x';
                for(int j=0; j <w_-2; ++j)
                {
                    os << " ";
                }
                os << 'x'<<'\n';
            }
            //For loop that prints the bottom(closed) part of the box
            for(int i=0; i<w_; ++i)
            {
                os << "x";
            }
            os << '\n';
        }
    }
}
