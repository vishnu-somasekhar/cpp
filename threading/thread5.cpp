#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std;

std::timed_mutex m1;
int iTotalAmount = 1000;
void increment(int x)
{
    if(m1.try_lock_for(chrono::seconds(2)))
    {
        ++iTotalAmount;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"Thread Entered "<< x << endl;
        m1.unlock();
    }
    else{
        cout<< "Thread count not enter "<< x << endl;
    }
}

void decremnet(int x)
{
    auto now = chrono::steady_clock::now();
    auto now1 = chrono::high_resolution_clock::now();
    if(m1.try_lock_until(now1 + chrono::seconds(6)))
    {
        --iTotalAmount;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"Thread Entered "<< x << endl;
        m1.unlock();
    }
    else{
        cout<< "Thread count not enter "<< x << endl;
    }
}

int main()
{
    std::thread T1(increment,1);
    std::thread T2(increment,2);
    std::thread T3(decremnet,3);
    std::thread T4(decremnet,4);
    T1.join();
    T2.join();
    T3.join();
    T4.join();
    return 0;
}