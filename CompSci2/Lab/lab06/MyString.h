//Bryan Burkhardt
//CS202
//Lab04 - MyString class header file. Class that acts similarly to strings

#ifndef MyString_hpp
#define MyString_hpp
#include <ostream>
#include <iostream>

template<typename T>
class MyString
{
public:
    //MyString default constructor that creates a new char array of size 0.
    MyString()
    {
        size_=0;
        data_=new T[0];
    }
    
    MyString(T s);
    MyString(const MyString & orig);
    ~MyString();
    MyString &operator=(MyString &rhs);
    friend std::ostream & operator<<(std::ostream &lhs, const MyString &rhs);
    char & operator[](T s);
    char & operator[](T s) const;
    friend MyString operator+(MyString &lhs, MyString &rhs);
    friend bool & operator==(MyString &lhs, MyString &rhs);
    friend bool operator!=(MyString &lhs, MyString &rhs);
    unsigned int size();
    unsigned int size() const;
    void print();
    
private:
    T size_;
    T * data_;
    
    
};

template<typename T>
bool & operator==(MyString<T> &lhs, MyString<T> &rhs);

template<typename T>
std::ostream & operator<<(std::ostream &lhs, const MyString<T> &rhs);

template<typename T>
MyString<T> operator+(MyString<T> &lhs, MyString<T> &rhs);

template<typename T>
bool operator!=(MyString<T> &lhs, MyString<T> &rhs);

template <typename T>
void MyString<T>::print()
{
    std::cout << "Size: " << size_ << std::endl;
    for(int i =0; i < size_; i++)
    {
        std::cout << data_[i] << " ";
    }
    std::cout << std::endl << std::endl;;
}

//MyString constructor that accepts and int and creates a new char array
//  of size given and fills the array withs zeros using a for loop.
template<typename T>
MyString<T>::MyString(T s)
{
    size_=s;
    data_=new T[size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i]=0;
    }
}

//MyString constructor that accepts another MyString and creates a new copy
//  of that MyString using a for loop.
template<typename T>
MyString<T>::MyString(const MyString & orig)
{
    size_=orig.size();
    data_=new char[size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i] = orig[i];
    }
}

//MyString deconstructor.
template<typename T>
MyString<T>::~MyString()
{
    for(int i=0; i<size_; ++i)
    {
        data_[i]=0;
    }
    if(size_)
    {
        size_=0;
    }
    if(data_!=0)
    {
        delete [] data_;
        data_=0;
    }
}

//MyString assignment operator. Function accepts a MyString and assigns that
//  MyString to a new MyString and returns it.
template<typename T>
MyString<T> & MyString<T>::operator=(MyString<T> &rhs)
{
    if(!(&rhs==this))
    {
        delete [] data_;
        size_=rhs.size();
        data_=new T[size_];
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
template<typename T>
std::ostream & operator<<(std::ostream & lhs, const MyString<T> & rhs)
{
    for(int i = 0; i <rhs.size(); ++i)
    {
        lhs << rhs[i];
    }
    return lhs;
}

//MyString [] operator that accepts and int and returns the value in that index
//  of the array.
template<typename T>
char & MyString<T>::operator[](T s)
{
    return data_[s];
}

//const MyString [] operator that accepts and int and returns the value in that index
//  of the array.
template<typename T>
char & MyString<T>::operator[](T s) const
{
    return data_[s];
}

//MyString + operator that accepts two MyString references and adds them together to
//  create one array. The rhs of the operator is concatinated to the lhs.
template<typename T>
MyString<T> operator+(MyString<T> &lhs, MyString<T> &rhs)
{
    
    int size_=(lhs.size() + rhs.size());
    MyString<T> data_(size_);
    
    //for loop that puts the lhs into a new array.
    for(int i=0; i<lhs.size(); ++i)
    {
        data_[i]=lhs[i];
    }
    //for loops that puts the rhs into the new array where the lhs left off.
    for(int i=0; i < rhs.size(); ++i)
    {
        data_[i+lhs.size()]=rhs[i];
    }
    return data_;
}

//MyString == operator that compares two MyString references and returns a bool
//  based on if the two string are identical.
template<typename T>
bool & operator==(MyString<T> &lhs, MyString<T> &rhs)
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
template<typename T>
bool operator!=(MyString<T> &lhs, MyString<T> &rhs)
{
    return !(rhs==lhs);
}

//MyString size functions that returns the size of the array that the function
//  is being called on.
template<typename T>
unsigned int MyString<T>::size()
{
    return size_;
}

//const MyString size functions that returns the size of the array that the function
//  is being called on.
template<typename T>
unsigned int MyString<T>::size() const
{
    return size_;
}






#endif
