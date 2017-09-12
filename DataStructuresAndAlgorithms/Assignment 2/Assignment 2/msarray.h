// msarray.h
// Bryan Burkhardt
// 20 September 2016
// CS 311 - Assignment 2
// Header file for class MSArray
// Smart array class that manages it's own resources.


#ifndef FILE_MSARRAY_H_INCLUDED
#define FILE_MSARRAY_H_INCLUDED

#include <iostream>
#include <cstddef> //for std::size_t
#include <algorithm>
using std::swap;


//**************************************************************
// Template class MSArray - Class definition
//**************************************************************


// class MSArray
// Simple RAII class holding dynamic array of value_type T
// Invariants:
//      arrayptr_ points to an array of value_type T, allocated by new[], owned by *this
template <typename T>
class MSArray {
    
// ***** MSArray: Types *****
public:
    using size_type = std::size_t;
    using value_type = T;
    
// ***** MSArray Ctors, dctor, op= *****
public:
    
    // Default ctor.
    // Creates an array of value_type T with arraysize_ 10.
    // Pre:
    //      none.
    // Post:
    //      arrayptr_ points to array of size 10.
    MSArray()
    {
        arrayptr_ = new value_type[10];
        arraysize_ = 10;
    }
    
    // Ctor from one parameter(size).
    // Creates an array of value_type T with given size.
    // Pre:
    //      size >=0
    // Post:
    //      arrayptr_ points to array of given size.
    explicit MSArray(size_type size)
    {
        arrayptr_ = new value_type[size];
        arraysize_ = size;
    }
    
    // Ctor from two parameters(size and elements).
    // Creates and array of value_type T and fills it with value_type x.
    // Pre:
    //      size >= 0
    //      x must be of same value_type T
    // Post:
    //      arrayptr_ points to array of given size and fills with given element(x).
    MSArray(size_type size, value_type x)
    {
        arrayptr_ = new value_type[size];
        arraysize_ = size;
        for(size_type i=0; i<arraysize_; ++i)
        {
            arrayptr_[i]=x;
        }
    }
    
    // Copy ctor.
    // Creates a new array of value_type T and copies the arraysize_ and contents of passed array orig.
    // Pre:
    //      Object passed must be a MSArray.
    // Post:
    // arrayptr_ points to new array identical to given array.
    MSArray(const MSArray & orig)
    {
        arrayptr_ = new value_type[orig.arraysize_];
        arraysize_ = orig.arraysize_;
        for(size_type i=0; i<arraysize_; ++i)
        {
            arrayptr_[i]=orig[i];
        }
    }
    
    // Move ctor.
    // Moves passed array to new location in memory.
    // Pre:
    //      Object passed must of a MSArray.
    // Post:
    //      arrayptr_ is moved to new location in memory.
    MSArray(MSArray && orig) noexcept
    {
        myswap(orig);
    }
    
    // Copy assignment ctor.
    // Copies rhs and returns current object by *this.
    // Pre:
    //      Object passed must be a MSArray.
    // Post:
    //      Returns copy of rhs by *this.
    MSArray & operator=(const MSArray &rhs)
    {
        MSArray temp(rhs);
        myswap(temp);
        return *this;
    }
    
    // Move assignment operator.
    // Moves current object to new location in memory.
    // Pre:
    //      Object passed must be a MSArray.
    // Post:
    //      Returns new location of object by *this
    MSArray &operator=(MSArray && rhs) noexcept
    {
        myswap(rhs);
        return *this;
    }
    
    // Destructor.
    // Pre:
    //      None.
    // Post:
    //      Array referenced by arrayptr_ has been destroyed.
    ~MSArray() //dctor
    {
        delete [] arrayptr_;
    }
    
    
// ***** MSArray: Iterators begin and end. *****
public:
    
    // Random access iterator for the beginning index of arrayptr_
    // Pre:
    //      None.
    // Post:
    //      Points to index 0 of arrayptr_
    value_type * begin()
    {
        return arrayptr_;
    }
    
    // Const random access iterator for the beginning index of arrayptr_
    // Pre:
    //      None.
    // Post:
    //      Points to index 0 of arrayptr_
    const value_type * begin() const
    {
        return arrayptr_;
    }
    
    // Random access iterator that points to (last+1) index of arrayptr_
    // Pre:
    //      None.
    // Post:
    // Points to last index (arrayptr_ + arraysize_) of arrayptr_
    value_type * end()
    {
        return arrayptr_ + arraysize_;
    }
    
    // Const random access iterator that points to (last+1) index of arrayptr_
    // Pre:
    //      None.
    // Post:
    // Points to last index (arrayptr_ + arraysize_) of arrayptr_
    const value_type * end() const
    {
        return arrayptr_ +arraysize_;
    }
    
// ***** MSArray: op[] and public size function. *****
public:
    
    // Operator[] const and non const.
    // Pre:
    //      0 <= index < (size of allocated array).
    // Post:
    //      Return is a reference to item #index of allocated array
    const value_type & operator[](size_type index) const
    {
        return *(arrayptr_ + index);
    }
    
    value_type & operator[](size_type index)
    {
        return *(arrayptr_ + index);
    }
    
    // Const size function.
    // Pre:
    //      None.
    // Post:
    //      Returns arraysize_ of MSArray.
    size_type size() const
    {
        return arraysize_;
    }
    
// ***** MSArray: data members. *****
private:
    
    value_type * arrayptr_=nullptr; // Pointer to our dynamic array. Initialized to nullptr.
    size_type arraysize_; // Size of our dynamic array.
    
// ***** MSArray: private swap function. *****
private:
    
    // myswap for MSArray using std::swap from <algorithm>
    // Pre:
    //      arraysize_ >= 0
    // Post:
    //      Swaps given MSArray objects.
    void myswap(MSArray &orig) noexcept
    {
        swap(arraysize_, orig.arraysize_);
        swap(arrayptr_, orig.arrayptr_);
    }
    
};  // End class MSArray

//**************************************************************
// class MSArray - Declarations of asociated global operators.
//**************************************************************

// template op==(MSArray<T>, MSArray<T>)
// Pre:
//      None.
// Post:
//      Return is true if lhs and rhs are identical.
template <typename T>
bool operator==(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    if(lhs.size() != rhs.size())
    {
        return false;
    }
    for(size_t i = 0; i < lhs.size(); ++i)
    {
        if(lhs[i] != rhs[i])
        {
            return false;
        }

    }
    return true;
}

// template op!=(MSArray<T>, MSArray<T>)
// Pre:
//      None.
// Post:
//      Return is false if lhs and rhs are not identical.
template <typename T>
bool operator!=(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    return !(lhs==rhs);
}

// template op<(MSArray<T>, MSArray<T>)
// Pre:
//      Both MSArray objects must be of same value_type
// Post:
//      Return is true if    lhs[i]<rhs[i]
//      Return is false if   lhs[i]>rhs[i]
//      If all array elements are the same up to last element in shorter array then:
//      Return is true if    lhs.size()<rhs.size()
//      Return is false if   lhs.size()>rhs.size()
template <typename T>
bool operator<(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    size_t shorter;
    if(lhs.size() < rhs.size())
    {
        shorter = lhs.size();
    }
    else
    {
        shorter = rhs.size();
    }
    
    for(size_t i = 0; i < shorter; ++i)
    {
        if(lhs[i]<rhs[i])
        {
            return true;
        }
        if(lhs[i]>rhs[i])
        {
            return false;
        }
        
    }
    
    if(lhs.size() < rhs.size())
    {
        return true;
    }
    return false;
}

// template op<=(MSArray<T>, MSArray<T>)
// Pre:
//      Both MSArray objects must be of same value_type
// Post:
//      Return is true if    lhs[i]<=rhs[i]
//      Return is false if   lhs[i]>rhs[i]
//      If all array elements are the same up to last element in shorter array then:
//      Return is true if    lhs.size()<=rhs.size()
//      Return is false if   lhs.size()>rhs.size()
template <typename T>
bool operator<=(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    return (lhs == rhs || lhs < rhs);
}

// template op>(MSArray<T>, MSArray<T>)
// Pre:
//      Both MSArray objects must be of same value_type
// Post:
//      Return is true if    lhs[i]>rhs[i]
//      Return is false if   lhs[i]<rhs[i]
//      If all array elements are the same up to last element in shorter array then:
//      Return is true if    lhs.size()>rhs.size()
//      Return is false if   lhs.size()<rhs.size()
template <typename T>
bool operator>(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    return !(lhs == rhs || lhs < rhs);
}

// template op>=(MSArray<T>, MSArray<T>)
// Pre:
//      Both MSArray objects must be of same value_type
// Post:
//      Return is true if    lhs[i]>=rhs[i]
//      Return is false if   lhs[i]<rhs[i]
//      If all array elements are the same up to last element in shorter array then:
//      Return is true if    lhs.size()>=rhs.size()
//      Return is false if   lhs.size()<rhs.size()
template <typename T>
bool operator>=(const MSArray<T> &lhs, const MSArray<T> &rhs)
{
    return !(lhs < rhs);
}

#endif //#ifndef FILE_MSARRAY_H_INCLUDED
