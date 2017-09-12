// tvsarray.h
// Bryan Burkhardt
// 29 Oct 2016
// CS 311 - Assignment 5
// Header file for class TVSArray
// Very smart array class thatat manages its own resource and acts similar to a vector.

#ifndef FILE_TVSARRAY_H_INCLUDED
#define FILE_TVSARRAY_H_INCLUDED

#include <iostream>
#include <cstddef>   //for std::size_t
#include <algorithm> //for std::swap, std::copy, std::rotate, std::distance
using std::copy;
#include <thread>

//******************************************************************
// Template class TVSArray - Class definition
//******************************************************************


// class TVSArray
// Simple RAII class holding dynamic array of value_type T.
// Invariants:
//		0 <= size_ <= capacity_
//		data_ points to a template array of value_type T, allocated with new[],
//			owned by *this, holding capacity_ T OR data_ is a null pointer,
//			and capacity_ == 0.
// Requirements on type:
//		Copy ctor.
template <typename T>
class TVSArray {

// ***** TVSArray: types *****
public:
	using size_type = std::size_t;
    using value_type = T;
	using iterator = value_type *;
	using const_iterator = const value_type *;

	static const size_type DEFAULT_CAP = size_type(16);

// ***** TVSAArray Ctors, dctor, op= *****
public:

	// Default ctor
	// Pre:
	//		None.
	// Post:
	//		size_ = 0;
	//		capacity_ = DEFAULT_CAP
	//		data_ = new array of type T
	// Exception Neutral
	// Strong Guarantee
	explicit TVSArray()
	:capacity_(DEFAULT_CAP),
	 size_(size_type(0)),
	 data_(new value_type[DEFAULT_CAP])
	{}

	// Ctor from size
	// Pre:
	//		size >= 0
	// Post:
	//		capacity_ == size
	//		size_ == size
	//		data_ = new array of type T
	// Eception Neutral
	// Strong Guarantee
	explicit TVSArray(size_type size)
		:capacity_(size),
		 size_(size),
		 data_(new value_type[size])
	{}


	// Copy ctor
	// Pre:
	// 		None.
	// Post:
	//		capacity_ == orig.capacity_
	//		size_ == orig.size_
	//		data_ == orig.data_
	// Exception Neutral
	// Strong Guarantee
	TVSArray(const TVSArray & orig)
	:capacity_(orig.capacity_),
	 size_(orig.size_),
	 data_(new value_type[orig.size_])
	{
		try
		{
			copy(orig.begin(), orig.end(), begin());
		}
		catch(...)
		{
			delete [] data_;
			throw;
		}
	}


	// Move ctor
	// Pre:
	//		None.
	// Post:
	//		capacity_ == orig.capacity_
	// 		size_ == orig.size_
	//		data_ == orig.data_
	//		orig TVSArray set to 0 and null
	// Exception Neutral
	// No-Throw Guarantee
	TVSArray(TVSArray && orig) noexcept
		:capacity_(orig.capacity_),
		 size_(orig.size_),
		 data_(orig.data_)
	{
		orig.capacity_ = size_type(0);
		orig.size_ = size_type(0);
		orig.data_ = nullptr;
	}


	// Copy Assignment
	// Pre:
	//		None.
	// Post:
	//		*this == rhs
	// Exception Neutral
	// Strong Guarantee
	TVSArray & operator=(const TVSArray &rhs)
    {
        TVSArray temp(rhs);
        swap(temp);
        return *this;
    }

	// Move Assignment 
	// Pre:
	// 		None.
	// Post:
	//		*this == rhs
	// Exception Neutral
	// No-Throw Guarantee
	TVSArray & operator=(TVSArray && rhs) noexcept
	{
        swap(rhs);
        return *this;
	}


	// Dctor
	// Pre:
	//		None.
	// Post:
	//		data_ deallocated
	// Exception Neutral
	// Strong Guarantee
    ~TVSArray()
	{
        delete [] data_;
	}


// ***** TVSArray: op[] *****
public:

	//operator[] const and non const
	// Pre:
	//		0 <= index < size_
	// Post:
	//		data_[index] is returned
	// Exception Neutral
	// No-throw Guarantee
	const value_type & operator[](size_type index) const
	{
		return data_[index];
	} 
	value_type & operator[](size_type index)
	{
		return data_[index];
	}

// ***** TVSrray: general public functions *****
public:

	// Size const
	// Pre:
	//		None.
	// Post:
	//		size_ returned
	// Exception Neutral
	// No-Throw Guarantee
	size_type size() const
	{ return size_; }

	// Empty
	// Pre:
	//		None.
	// Post:
	//		Returns true if array is empty or false if array is not empty.
	// Exception Neutral
	// No-Throw Guarantee
	bool empty() const
	{ return size_==0; }

	// Begin (const and non const)
	// Pre:
	//		None.
	// Post:
	//		data_ is returned
	// Exception Neutral
	// No-Throw Guarantee
	const_iterator begin() const
	{ return data_; }

	iterator begin()
	{ return data_; }

	// End (const and non const)
	// Pre:
	//		None.
	// Post:
	//		being()+size() is returned
	// Exception Neutral
	// No-Throw Guarantee
	const_iterator end() const
	{ return begin() + size(); }

	iterator end()
	{ return begin() + size(); }

	// Resize
	// Pre:
	//		newsize >= 0
	// Post:
	//		If newsize value is less than current capacity_ of array then the size_ is
	//			changed to newsize.
	//		Else the array is re-allocated and copied to array of newsize with capacity_
	//			= newsize*2
	// Exception Neutral
	// Strong Guarantee
	void resize(size_type newsize)
	{
		if(newsize <= capacity_)
		{
			size_ = newsize;
		}
		else
		{
			size_type newCapacity;
			value_type * newData;

			if(newsize > capacity_*2)
			{
				newCapacity = newsize;
			}
			else
			{
				newCapacity = newsize*2;
			}

			newData = new value_type[newCapacity];
			try
			{
				std::thread t(copy(begin(), middle(), newData));
				copy(middle()+1, end(), newData);
				t.join();
				//copy(begin(), end(), newData);
			}
			catch(...)
			{
				delete [] newData;
				throw;
			}
			delete [] data_;
			data_ = newData;
			capacity_ = newCapacity;
			size_ = newsize;
		}
	}
	

	// Insert
	// Pre:
	//		0 <= pos <= size_
	// Post:
	//		size_++
	//		data_[idx] = item
	//		iterator pointing to data_[idx] is returned
	// Exception Neutral
	// Basic Guarantee
	iterator insert(iterator pos, const value_type & item)
	{
		size_type idx = std::distance(begin(), pos);
		resize(size_+1);
		data_[size_-1] = item;
		pos = &data_[idx];
		std::rotate(pos, end()-1, end());
        return pos;
	}

	// Remove
	// Pre:
	//		0 <= pos <= size_
	// Post:
	//		size_--
	//		data_[pos] is removed
	//		iterator pointing to data_+1 is returned
	// Exception Neutral
	// Basic Guarantee
	iterator remove(iterator pos)
	{
		std::rotate(pos, pos+1, end());
		resize(size_-1);
        return pos;
	}

	// Swap
	// Pre:
	//		None.
	// Post:
	// 		capacity_ == orig.capacity_
	//		size_ == orig.size_
	//		data_ == orig.data_
	// Exception Neutral
	// No-Throw Guarantee
	void swap(TVSArray & orig) noexcept
	{
		std::swap(capacity_, orig.capacity_);
		std::swap(size_, orig.size_);
		std::swap(data_, orig.data_);
	}

// ***** TVSArray: Data Members *****
private:
	size_type capacity_;
	size_type size_;
	value_type * data_;

	iterator middle()
    {
        return begin() + (size_/2);
    }
    
    const_iterator middle() const
    {
        return begin() + (size_/2);
    }

	void firstHalf(iterator begin, iterator middle, value_type data)
    {
        copy(begin, middle, data);
    }
    void secondHalf(iterator middle, iterator end, value_type data)
    {
        copy(middle, end, data);
    }

}; // End of class TVSArray


#endif //FILE_TVSARRAY_H_INCLUDED