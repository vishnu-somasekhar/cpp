//! Every application have a default thread called main()
//! If you want to create other thread then create inside main()

//! thread is also known as lightweight process, to acheive parallelism with the help of multiple threads
//! 

/**************** WAYS TO CREATE THREAD IN C++ 11 ******************************************
 * 
 * 1. FUNCTION POINTER
 * 2. LAMBDA FUNCTIONS
 * 3. FUNCTORS
 * 4. MEMBER FUNCTIONS
 * STATIC MEMBER FUNCTIONS
 * 
 * ****************/
#include <iostream>
#include <thread>

using namespace std;

void Fun( int x)
{
    while(x > 0)
    {
        cout<< x << " ";
        x--;
    }
    return;
}

class Functor
{
    public:
    void operator()(int x)
    {
        while(x > 0)
        {
            cout<< x << " ";
            x--;
        }  
    }
};

class Base
{
    public:
    void run(int x)
    {
        while(x-- > 0)
            cout<< x << " ";
    }

    static void run_static(int x)
    {
        while(x-- > 0)
            cout<< x << " ";
    }
};

void fun_sleep()
{
    cout<< "Thread before sleep" << endl;

    this_thread::sleep_for(chrono::seconds(3));

    cout<< "Thread after sleep" << endl;
}

int main()
{
    thread t(Fun, 10);

    t.join();
    cout<< endl;
    auto Fun_lambda = [](int x){
        while(x > 0)
        {
            cout<< x << " ";
            x--;
        }
    };

    thread t2(Fun_lambda, 11);
    t2.join();
    cout<< endl;

    thread t3(Functor(), 10);
    t3.join();
    cout<< endl;
    
    //! Calling non static member function
    Base b;
    thread t4(&Base::run, &b, 10);
    t4.join();
    cout<< endl;

    thread t5(&Base::run_static, 10);
    t5.join();

    cout<< endl;

    thread t6(fun_sleep);
    cout<< "Main before join" << endl;
    t6.join();
    cout<< "Main after join" << endl;

    return 0;
}