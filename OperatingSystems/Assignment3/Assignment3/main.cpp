//
//  main.cpp
//  Assignment3
//
//  Created by Bryan Burkhardt on 4/4/17.
//  Copyright © 2017 Bryan Burkhardt. All rights reserved.
//

#include <iostream>
#include "mapalloc.h"
int main() {
    
    char * p = (char*) mapAlloc(5000);
    p[0]='Q';
    p[100]='W';
    p[5000]='E';
    
    std::cout << p[0] << " " << p[100] << " " << p[5000] << " " << p[200] << " " << std::endl;
    std::cout << (&p) << std::endl;
    
    mapFree(p);
    
    //std::cout << p[0] << " " << p[100] << " " << p[5000] << " " << p[200] <<  " " << std::endl;
    return 0;
}
