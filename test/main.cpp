#include <iostream>
#include "test.h"

int main()
{
    AAA a;
    Student obj;
    std::cout<<obj.Get()<<std::endl;
    obj.Set(a.m_iVal);
    std::cout<<obj.Get()<<std::endl;

    a.m_iVal = 1000;
    std::cout<<a.m_iVal<<std::endl;
    return 0;
}