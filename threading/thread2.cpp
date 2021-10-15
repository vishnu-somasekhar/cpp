#include <iostream>
#include <thread>

using namespace std;

class AddEvenFuntor {

public:

void operator()(int x)
{
    int sum = 0;
    while (x-- > 0)
    {
        if(x % 2 == 0)
            sum += x;
    }
    cout<< "Even Sum from Functor : "<< sum << endl;
    return;
}
};

class Add{

    static int _x;

public:

void AddEven(int x)
{
    int sum = 0;
    while (x-- > 0)
    {
        if(x % 2 == 0)
            sum += x;
    }
    cout<< "Even Sum from member functoin : "<< sum << endl;
    return;
}

static void _AddEven(int x);

};

void Add::_AddEven(int x)
{
    int sum = 0;
    while (x-- > 0)
    {
        if(x % 2 == 0)
            sum += x;
    }
    cout<< "Even Sum from static function : "<< sum << endl;
    return;
}

int main()
{
    thread T1((AddEvenFuntor()), 11);
    T1.join();

    thread T2([](int x) {

int sum = 0;
    while (x-- > 0)
    {
        if(x % 2 == 0)
            sum += x;
    }
    cout<< "Even Sum from Lamda : "<< sum << endl;
    }, 11);

    T2.join();


    thread T3(&Add::_AddEven, 11);

    T3.join();

    Add a;
    thread T4(&Add::AddEven, &a, 11);
    T4.join();
    return 0;
}