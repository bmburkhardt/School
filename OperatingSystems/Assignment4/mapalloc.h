// mapalloc.h
// Bryan Burkhardt
// 10 Apr 2017
// CS 321 - Assignment 4
// Header file for mapalloc.cpp
// Simple Memory Manager

#ifndef MAP_ALLOC_HPP
#define MAP_ALLOC_HPP

#include <stdio.h>
#include <cstddef> // for size_t
#include <sys/mman.h> // for mmap, munmap

void * mapAlloc(std::size_t bytes);
void mapFree(void * memptr);
#endif // MAP_ALLOC_HPP 
