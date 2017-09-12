//Bryan Burkhardt
//CS202
//Lab04 - MyTemplate class header and source file.

#ifndef MyTemplate_hpp
#define MyTemplate_hpp
#include <ostream>
#include <iostream>

template<typename T>
class MyTemplate
{
public:
    //MyTemplate default constructor that creates a new char array of size 0.
    MyTemplate()
    {
        size_=0;
        data_=new T[0];
    }
    
    MyTemplate<T>(T s);
    MyTemplate<T>(const MyTemplate<T> & orig);
    ~MyTemplate<T>();
    MyTemplate<T> &operator=(const MyTemplate<T> &rhs);
    
    template <typename E>
    friend std::ostream & operator<<(std::ostream &lhs, const MyTemplate<T> &rhs);
    
    T & operator[](T s);
    T & operator[](T s) const;
    
    template <typename E>
    friend MyTemplate<T> operator+(MyTemplate<T> &lhs, MyTemplate<T> &rhs);
    
    template <typename E>
    friend bool & operator==(MyTemplate<T> &lhs, MyTemplate<T> &rhs);
    
    template <typename E>
    friend bool operator!=(MyTemplate<T> &lhs, MyTemplate<T> &rhs);
    
    unsigned int size();
    unsigned int size() const;
    void print();
    
private:
    T size_;
    T * data_;
    
    
};

template<typename T>
bool & operator==(MyTemplate<T> &lhs, MyTemplate<T> &rhs);

template<typename T>
std::ostream & operator<<(std::ostream &lhs, const MyTemplate<T> &rhs);

template<typename T>
MyTemplate<T> operator+(MyTemplate<T> &lhs, MyTemplate<T> &rhs);

template<typename T>
bool operator!=(MyTemplate<T> &lhs, MyTemplate<T> &rhs);

template <typename T>
void MyTemplate<T>::print()
{
    std::cout << "Size: " << size_ << std::endl;
    for(int i =0; i < size_; i++)
    {
        std::cout << data_[i] << " ";
    }
    std::cout << std::endl << std::endl;;
}

//MyTemplate constructor that accepts and int and creates a new char array
//  of size given and fills the array withs zeros using a for loop.
template<typename T>
MyTemplate<T>::MyTemplate(T s)
{
    size_=s;
    data_=new T[(int)size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i]=0;
    }
}

//MyTemplate constructor that accepts another MyTemplate and creates a new copy
//  of that MyTemplate using a for loop.
template<typename T>
MyTemplate<T>::MyTemplate(const MyTemplate & orig)
{
    size_=orig.size();
    data_=new T[(int)size_];
    
    for(int i = 0; i < size_; ++i)
    {
        data_[i] = orig[i];
    }
}

//MyTemplate deconstructor.
template<typename T>
MyTemplate<T>::~MyTemplate()
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

//MyTemplate assignment operator. Function accepts a MyTemplate and assigns that
//  MyTemplate to a new MyTemplate and returns it.
template<typename T>
MyTemplate<T> & MyTemplate<T>::operator=(const MyTemplate<T> &rhs)
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

//Ostream operator that accepts an ostream reference and a MyTemplate reference.
//  The function streams the MyTemplate array to the ostream with no whitespace
//  or new lines. Function then returns the ostream.
template<typename T>
std::ostream & operator<<(std::ostream & lhs, const MyTemplate<T> & rhs)
{
    for(int i = 0; i <rhs.size(); ++i)
    {
        lhs << rhs[i];
    }
    return lhs;
}

//MyTemplate [] operator that accepts and int and returns the value in that index
//  of the array.
template<typename T>
T & MyTemplate<T>::operator[](T s)
{
    return data_[s];
}

//const MyTemplate [] operator that accepts and int and returns the value in that index
//  of the array.
template<typename T>
T & MyTemplate<T>::operator[](T s) const
{
    return data_[s];
}

//MyTemplate + operator that accepts two MyTemplate references and adds them together to
//  create one array. The rhs of the operator is concatinated to the lhs.
template<typename T>
MyTemplate<T> operator+(MyTemplate<T> &lhs, MyTemplate<T> &rhs)
{
    
    int size_=(lhs.size() + rhs.size());
    MyTemplate<T> data_(size_);
    
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

//MyTemplate == operator that compares two MyTemplate references and returns a bool
//  based on if the two string are identical.
template<typename T>
bool & operator==(MyTemplate<T> &lhs, MyTemplate<T> &rhs)
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

//MyTemplate != operator that compares two MyTemplate references and returns a bool
//  based on if the two strings are different.
template<typename T>
bool operator!=(MyTemplate<T> &lhs, MyTemplate<T> &rhs)
{
    return !(rhs==lhs);
}

//MyTemplate size functions that returns the size of the array that the function
//  is being called on.
template<typename T>
unsigned int MyTemplate<T>::size()
{
    return size_;
}

//const MyTemplate size functions that returns the size of the array that the function
//  is being called on.
template<typename T>
unsigned int MyTemplate<T>::size() const
{
    return size_;
}






#endif
