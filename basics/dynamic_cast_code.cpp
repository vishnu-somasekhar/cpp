#include <iostream>

using namespace std;

class Base1
{
    int x;

    public:

    virtual int getX() { return x; }

    virtual void SetX(int a) { x = a; }

};

class Derived1 : public Base1
{
    int y;
    public:

    int getX() { return y;}

    void SetX(int a) { y = a; }
};

class Derived2 : public Base1
{
    int z;
    public:

    int getX() { return z;}

    void SetX(int a) { z = a; }
};

int main()
{
    Base1 *b1 = new Base1();
    Derived1 *d1 = new Derived1();

    b1->SetX(10);
    d1->SetX(20);
    cout<< d1->getX() << endl;
    cout<< b1->getX() << endl;
    
    b1 = dynamic_cast<Base1*>(d1);
    cout<< b1->getX() << endl;

    Derived2 *d2 = dynamic_cast<Derived2*>(b1);
    if (nullptr == d2)
    {
        cout<< "Failed to cast" << endl;
    }
    else
    {
        cout<< d2->getX() << endl;
    }

    Derived1 *d3 = dynamic_cast<Derived1*>(b1);
    if (nullptr == d3)
    {
        cout<< "Failed to cast" << endl;
    }
    else
    {
        cout<< d3->getX() << endl;
    }
        
    return 0;
}