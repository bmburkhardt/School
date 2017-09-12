// llnode.h
// VERSION 2
// Glenn G. Chappell
// 9 Nov 2016
// Updated: 10 Nov 2016
//
// For CS 311 Fall 2016
// Open Access Singly Linked List Node
// + Associated Functionality
// Used in Assignment 6, Exercises A, B, C

#ifndef FILE_LLNODE_H_INCLUDED
#define FILE_LLNODE_H_INCLUDED

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
#include <cstddef>
using std::size_t;
#include <memory>
using std::shared_ptr;
using std::make_shared;


// struct LLNode
// Linked List node with client-specified value type. It is expected
// that LLNode objects will be created with make_shared, and always
// held by a shared_ptr. An empty list is represented by an empty
// shared_ptr.
// Invariants:
//     _next points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
template <typename ValueType>
struct LLNode {
    ValueType          _data;  // Data for this node
    shared_ptr<LLNode> _next;  // Ptr to next node, or empty if none

    // The following simplify creation & destruction

    // 1- & 2-param ctor
    // Pre: None.
    // Post:
    //     _data == data.
    //     If _next passed, then _next == next. Otherwise, _next is an
    //      empty shared_ptr.
    // Strong guarantee
    // Exception neutral: throws what & when a ValueType operation
    // throws.
    explicit LLNode(const ValueType & data,
                    shared_ptr<LLNode> next = nullptr)
        :_data(data),
         _next(next)
    {}

    ~LLNode() = default;
};


// size
// Given shared_ptr to Linked List, return its size (number of nodes).
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Post:
//     Return is size of list (0 if head is empty).
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
// No-Throw Guarantee
template <typename ValueType>
size_t size(shared_ptr<LLNode<ValueType> > head)
{
    auto p = head;  // Iterates through list
    size_t n = 0;   // Number of nodes so far
    while (p)
    {
        p = p->_next;
        ++n;
    }
    return n;
}


// isEmpty
// Given ptr to Linked List, returns true if the list is empty, false
// otherwise.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Post:
//     Return is true if list is nonempty. Otherwise, false.
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
// No Throw Guarantee
template <typename ValueType>
bool isEmpty(shared_ptr<LLNode<ValueType> > head)
{
    return !head;
}


// push_front
// Given ptr to Linked List, and a ValueType item, push the item onto
// the front of the list. head becomes a pointer to the new list.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Post:
//     List has been altered as required.
//     head points to the new list.
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
// Strong Guarantee
// Exception neutral: throws what & when a ValueType operation throws.
template <typename ValueType>
void push_front(shared_ptr<LLNode<ValueType> > & head,
                const ValueType & item)
{
    head = make_shared<LLNode<ValueType> >(item, head);
}


// pop_front
// Given shared_ptr to Linked List, removes first item from list, if
// list is nonempty. If list is empty, does nothing.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Post:
//     List has been altered as required.
//     head points to the new list.
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
// No Throw Guarantee
template <typename ValueType>
void pop_front(shared_ptr<LLNode<ValueType> > & head)
{
    if (head)
        head = head->_next;
}


// print_list
// Given shared_ptr to Linked List, prints it to given output stream --
// or cout, if none is given -- a blank separating each item, with a
// single trailing newline.
// Pre:
//     head points to empty-ptr-terminated Linked List, or is an empty
//      shared_ptr.
// Post:
//     Values have been printed, as required.
// Requirements on Types:
//     ValueType must have a copy ctor and a dctor.
//     ValueType dctor must not throw.
//     ValueType must have operator<< (stream insertion).
// Strong Guarantee
// Exception neutral: throws what & when a ValueType operation throws.
template <typename ValueType>
void print_list(shared_ptr<LLNode<ValueType> > head,
                ostream & outstr=cout)
{
    while (head)
    {
        outstr << head->_data;
        head = head->_next;
        if (head)
            outstr << " ";
    }
    outstr << endl;
}

#endif //#ifndef FILE_LLNODE_H_INCLUDED

