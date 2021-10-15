#include <iostream>

class Test
{
    int a;
    public:

    Test()
    {
        a = 10;
    }
};

void print(Test* obj)
{
    if(NULL == obj)
    {
        std::cout<<"Fail";
    }
    else
    {
        std::cout<<"PASS";
    }
    
}

int main()
{
    Test t;
    print(&t);
    return 0;
}