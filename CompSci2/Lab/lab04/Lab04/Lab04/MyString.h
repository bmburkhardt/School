//Bryan Burkhardt
//CS202
//Lab04 - MyString class header file. Class that acts similarly to strings

#ifndef MyString_hpp
#define MyString_hpp
#include <ostream>

class MyString
{
public:
    //MyString default constructor that creates a new char array of size 0.
    MyString()
    {
        size_=0;
        data_=new char[0];
    }
    
    MyString(int s);
    MyString(const MyString & orig);
    ~MyString();
    MyString &operator=(MyString &rhs);
    friend std::ostream & operator<<(std::ostream &lhs, const MyString &rhs);
    char & operator[](int s);
    char & operator[](int s) const;
    friend MyString operator+(MyString &lhs, MyString &rhs);
    friend bool & operator==(MyString &lhs, MyString &rhs);
    friend bool operator!=(MyString &lhs, MyString &rhs);
    unsigned int size();
    unsigned int size() const;
    void resize(int s);
    
private:
    int size_;
    char * data_;
    
    
};

bool & operator==(MyString &lhs, MyString &rhs);
std::ostream & operator<<(std::ostream &lhs, const MyString &rhs);
MyString operator+(MyString &lhs, MyString &rhs);
bool operator!=(MyString &lhs, MyString &rhs);




#endif
