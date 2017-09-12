// da6.h
// Bryan Burkhardt
// 16 Nov 2016
// CS 311 - Assignment 6
// Header file for void reverseList, class SLQueue, and class SLMap

#ifndef FILE_DA6_H_INCLUDED
#define FILE_DA6_H_INCLUDED

#include "llnode.h"
#include <functional>
#include <memory>
using std::make_shared;
#include <utility>
using std::pair;
using std::make_pair;
using std::size_t;


//******************************************************************
// Template function reverseList - Function definition
//******************************************************************

// Pre:
//		None.
// Post:
//		Linked list is reversed.
// Requirements on type:
//		Default ctor.
// Exception Neutral.
// No-Throw Guarantee.
template<typename ValueType>
void reverseList(shared_ptr<LLNode<ValueType> > & head)
{
	if (head!=nullptr)
	{
		shared_ptr<LLNode<ValueType> > current = head, next, prev = nullptr;

		while (current!=nullptr)
		{
			next = current->_next;
			current->_next = prev;
			prev = current;
			current = next;
		} 

		head = prev;
	}
}


//******************************************************************
// Template class SLQueue - Class Definition
//******************************************************************

// class SLQueue
// Queue class that holds shared_ptrs of value_type ValueType
// Invariants:
//		data_ == nullptr || data_ points to front of queue.
//		current_ points to end of queue.
//		size_ >= 0
// Requirements on Type:
//		Copy ctor.
template<typename ValueType>
class SLQueue
{

public:

	
	// Default ctor.
	// Pre:
	//		None.
	// Post:
	//		data_ = nullptr;
	//		size_ = 0;
	// Exception Neutral
	// No-Throw Guarantee
	SLQueue():data_(nullptr),size_(0) 
	{}

	SLQueue(const SLQueue & copy) = delete;
	SLQueue(SLQueue && copy) = delete;
	SLQueue operator=(const SLQueue & copy) = delete;
	SLQueue operator=(SLQueue && copy) = delete;
	
	// Dctor
	// Pre:
	//		None.
	// Post:
	//		None.
	// Exception Neutral
	// No-Throw Guarantee
	~SLQueue() = default;
	
	// Empty (non const and const)
	// Pre:
	//		None
	// Post:
	//		Returns true if queue is empty or false if queue is not empty
	// Exception Neutral
	// No-Throw Guarantee
	bool empty()
	{ return data_ == nullptr; }
	bool empty() const
	{ return data_ == nullptr; }
	
	// Size (non const and const)
	// Pre:
	//		None.
	// Post:
	//		Returns size of queue.
	// Exception Neutral
	// No-Throw Guarantee
	std::size_t size()
	{ return size_; }
	std::size_t size() const
	{ return size_; }
	
	// Front (non const and const)
	// Pre:
	//		None.
	// Post:
	//		Returns data at front of queue.
	// Exception Neutral
	// No-Throw Guarantee
	ValueType & front()
	{ return data_->_data; }
	ValueType & front() const
	{ return data_->_data; }
	
	// Push
	// Pre:
	//		None.
	// Post:
	//		Puts object at back of the queue.
	// 		current_ points to end of queue.
	//		Increments size_ of queue by 1.
	// Exception Neutral
	// Strong Guarantee
	void push(const ValueType & obj)
	{
		shared_ptr<LLNode<ValueType> > objptr = make_shared<LLNode<ValueType> >(obj);

		if (data_!=nullptr)
		{
			current_->_next = objptr;
			current_ = current_->_next;
		}
		else
		{
			data_ = objptr;
			current_ = data_;
		}
		++size_;
	}
	
	// Pop
	// Pre:
	//		None.
	// Post:
	//		data_ points to next node in the queue.
	//		Decerements size_ of queue by 1.
	// Exception Neutral
	// No-Throw Guarantee
	void pop()
	{
		if (data_!=nullptr)
		{
			data_ = data_->_next;
			--size_;
		}
	}

// ***** SLQueue: Data Members *****
private:
	shared_ptr<LLNode<ValueType> > data_;
	shared_ptr<LLNode<ValueType> > current_;
	size_t size_;

}; // End of class SLQueue


//******************************************************************
// Template class SLMap - Class definition
//******************************************************************

// class SLMap
// Map class holding shared_ptrs of value_type KEY_TYPE and value_type DATA_TYPE
// Invariants:
//		map_ == nullptr for map of size 0 or points to first node in map
//		current_ points to last inserted KVTYPE
//		size_ >= 0
// Requirements on Type:
//		Copy ctors
//		== for KEY_TYPE
//		& for DATA_TYPE
template<typename KEY_TYPE, typename DATA_TYPE>
class SLMap
{

public:
	
	// Default ctor
	// Pre:
	//		None.
	// Post:
	//		map_ = nullptr;
	//		size_ = 0;
	// Exception Neutral
	// No-Throw Guarantee
	SLMap():map_(nullptr),size_(0)
	{}

	SLMap(const SLMap & copy) = delete;
	SLMap(SLMap && copy) = delete;
	SLMap operator=(const SLMap & copy) = delete;
	SLMap operator=(SLMap && copy) = delete;

	// Dctor
	// Pre:
	//		None.
	// Post:
	//		None.
	// Exception Neutral
	// No-Throw Guarantee
	~SLMap() = default;

	// Empty (non const and const)
	// Pre:
	//		None.
	// Post:
	//		Returns true if map is empty or false is map is not empty
	// Exception Neutral
	// No-Throw Guarantee
	bool empty()
	{ return map_ == nullptr; }
	bool empty() const
	{ return map_ == nullptr; }
	
	// Size (non const and const)
	// Pre:
	//		None.
	// Post:
	//		Returns size of map
	// Exception Neutral
	// No-Throw Guarantee
	size_t size()
	{ return size_; }
	size_t size() const
	{ return size_; }
	
	// Find (non const and const)
	// Pre:
	//		None.
	// Post:
	//		Returns value of the map by reference for the given key.
	//		If key does not exist, returns nullptr.
	// Exception Neutral
	// No-Throw Guarantee
	DATA_TYPE * find(const KEY_TYPE & key)
	{
		shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > current;

		current = map_;
		while(current)
		{
			if (current->_data.first == key)
			{
				return &(current->_data.second);
			}
			current = current->_next;
		}
		return nullptr;
	}
	const DATA_TYPE * find(const KEY_TYPE & key) const
	{
		shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > current;

		current = map_;
		while(current)
		{
			if (current->_data.first == key)
			{
				return &(current->_data.second);
			}
			current = current->_next;
		}
		return nullptr;
	}
	
	// Insert
	// Pre:
	//		None.
	// Post:
	//		Inserts the KVPair into the next node in LL
	//		Increments size of map by 1
	// Exception Neutral
	// Strong Guarantee
	void insert(const KEY_TYPE & key, const DATA_TYPE & data)
	{		
		if (!current_)
		{
			map_ = make_shared<LLNode<pair<KEY_TYPE,DATA_TYPE> > >(make_pair(key,data));
			current_ = map_;
		}
		else
		{
			current_->_next = make_shared<LLNode<pair<KEY_TYPE,DATA_TYPE> > >(make_pair(key,data));
			current_ = current_->_next;
		}
		++size_;
	}	
	
	// Remove
	// Pre:
	//		None.
	// Post:
	//		Removes KVPair
	//		Decrements size of map by 1
	// Exception Neutral
	// No-Throw Guarantee
	void remove(const KEY_TYPE & key)
	{
		shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > current = map_;

		if (current->_data.first == key)
		{
			map_ = map_->_next;
			--size_;
			return;
		}
		while (current->_next)
		{
			if (current->_next->_data.first == key)
			{
				current->_next = current->_next->_next;
				--size_;
				return;
			}
			current = current->_next;
		}
	}
	
	// Traverse
	// Pre:
	//		None.
	// Post:
	//		None.
	// Exception Neutral
	// Strong Guarantee
	void traverse(std::function<void(KEY_TYPE,DATA_TYPE)> f)
	{
		shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > current = map_;

		while (current)
		{
			f(current->_data.first,current->_data.second);
			current = current->_next;
		}
	}

// ***** SLMap: Data Members *****
private:
	shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > map_;
	shared_ptr<LLNode<pair<KEY_TYPE,DATA_TYPE> > > current_;
	size_t size_;	

}; // End of class SLMap



#endif //FILE_DA6_H_INCLUDED