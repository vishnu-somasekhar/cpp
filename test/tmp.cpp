// Example program
#include <iostream>
#include <string>

class Interface
{
    public:
    virtual void Set(int a) = 0;
    
    virtual int get() = 0;
};

static Interface* _obj = nullptr;

class Derived : public Interface
{
    private:
    int m_a;
    
    protected:
    
    virtual void Set(int a)
    {
        m_a = a;
    }
    
    virtual int get() { return m_a; }
    
};

Interface* GetObject()
{
    if(_obj == nullptr)
        _obj = new Derived;
    
    return _obj;
}


int main()
{
    Interface* a = GetObject();
    
    a->Set(10);
    
    std::cout<<a->get()<<"  \n";

    delete a;

    a = nullptr;

    Interface* b = GetObject();
    b->Set(10);
    
    std::cout<<b->get()<<"  \n";

    return 0;
}
