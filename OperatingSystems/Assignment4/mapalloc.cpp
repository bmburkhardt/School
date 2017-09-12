// mapalloc.h
// Bryan Burkhardt
// 10 Apr 2017
// CS 321 - Assignment 4
// Source file for mapalloc.h
// Simple Memory Manager

#include "mapalloc.h"
#include <map>
using std::map;
using std::size_t;

map<void *, size_t> memBlockSize;


void * mapAlloc(size_t bytes) {
    void * addr = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (addr==MAP_FAILED) {
        return nullptr;
    }
    else {
        memBlockSize[addr] = bytes;
        return addr;
    }
}
void mapFree(void * memptr) {
    munmap(memptr,memBlockSize[memptr]);
}