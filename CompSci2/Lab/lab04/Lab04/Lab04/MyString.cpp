//Bryan Burkhardt
//CS202
//Lab04 - MyString class source file. Class that acts similarly to strings

#include "MyString.h"

//MyString constructor that accepts and int and creates a new char array
//  of size given and fills the array withs zeros using a for loop.
MyString::MyString(int s)
{
    size_=s;
    data_=new char[size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i]=0;
    }
}

//MyString constructor that accepts another MyString and creates a new copy
//  of that MyString using a for loop.
MyString::MyString(const MyString & orig)
{
    size_=orig.size();
    data_=new char[size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i] = orig[i];
    }
}

//MyString deconstructor.
MyString::~MyString()
{
}

//MyString assignment operator. Function accepts a MyString and assigns that
//  MyString to a new MyString and returns it.
MyString & MyString::operator=(MyString &rhs)
{
    if(!(&rhs==this))
    {
        delete [] data_;
        size_=rhs.size();
        data_=new char[size_];
        for(int i = 0; i < size_; ++i)
        {
            data_[i]=rhs[i];
        }
    }
    return *this;
}

//Ostream operator that accepts an ostream reference and a MyString reference.
//  The function streams the MyString array to the ostream with no whitespace
//  or new lines. Function then returns the ostream.
std::ostream & operator<<(std::ostream & lhs, const MyString & rhs)
{
    for(int i = 0; i <rhs.size(); ++i)
    {
        lhs << rhs[i];
    }
    return lhs;
}

//MyString [] operator that accepts and int and returns the value in that index
//  of the array.
char & MyString::operator[](int s)
{
    return data_[s];
}

//const MyString [] operator that accepts and int and returns the value in that index
//  of the array.
char & MyString::operator[](int s) const
{
    return data_[s];
}

//MyString + operator that accepts two MyString references and adds them together to
//  create one array. The rhs of the operator is concatinated to the lhs.
MyString operator+(MyString &lhs, MyString &rhs)
{
    
    int size_=(lhs.size() + rhs.size());
    MyString data_(size_);
    
    //for loop that puts the lhs into a new array.
    for(int i=0; i<lhs.size(); ++i)
    {
        data_[i]=lhs[i];
    }
    
    //for loops that puts the rhs into the new array where the lhs left off.
    for(int i=0; i < rhs.size(); ++i)
    {
        data_[i+10]=rhs[i];
    }
    return data_;
}

//MyString == operator that compares two MyString references and returns a bool
//  based on if the two string are identical.
bool & operator==(MyString &lhs, MyString &rhs)
{
    bool result = true;
    int count = 0;
    int max = rhs.size();
    
    //for loop that compares two string and increments the counter by 1 if
    //  the values in the indexes are equal.
    for(int idx = 0; idx < lhs.size(); ++idx)
    {
        if(lhs[idx]==rhs[idx])
        {
            count ++;
        }
    }
    
    //If the counter from the for loop does not equal the size of one of the array's
    //  being passed, then they are not equal.
    if(count != max)
    {
        result = false;
    }
    return result;
}

//MyString != operator that compares two MyString references and returns a bool
//  based on if the two strings are different.
bool operator!=(MyString &lhs, MyString &rhs)
{
    return !(rhs==lhs);
}

//MyString size functions that returns the size of the array that the function
//  is being called on.
unsigned int MyString::size()
{
    return size_;
}

//const MyString size functions that returns the size of the array that the function
//  is being called on.
unsigned int MyString::size() const
{
    return size_;
}

//Resize function that accepts an int and resizes a MyString array to the new given size.
void resize(int s)
{
    MyString data_(s);
}
