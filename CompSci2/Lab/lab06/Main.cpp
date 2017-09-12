//Bryan Burkhardt
//CS202
//Lab06 - Changed MyString lab into MyTemplate lab to demonstrate use of template classes
#include <iostream>
#include "MyTemplate.h"

int main()
{
    char y = 66;
    MyTemplate<int> a;
    MyTemplate<char> b(y);
    MyTemplate<float> c(3.2);
    MyTemplate<double> d(7.4);
    MyTemplate<int> e(4);
    MyTemplate<int> f;
    MyTemplate<int> g(4);
    MyTemplate<int> h(a);
    
    std::cout << "a:" << std::endl;
    a.print();
    
    std::cout << "b:" << std::endl;
    b.print();
    
    std::cout << "c:" << std::endl;
    c.print();
    
    std::cout << "d:" << std::endl;
    d.print();
    
    std::cout << "e:" << std::endl;
    e.print();
    
    std::cout << "a+e:" << std::endl;
    f = (a+e);
    f.print();
    
    std::cout << "g:" << std::endl;
    g.print();
    
    std::cout << "h:" << std::endl;
    h.print();
    
    std::cout << "Does e==g?" << std::endl;
    std::cout << (e==g) << std::endl;
    
    std::cout << "Does e!=g?" << std::endl;
    std::cout << (e!=g) << std::endl;
}
