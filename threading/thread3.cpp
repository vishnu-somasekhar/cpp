#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int iTotal = 0;

std::mutex m1;
void Add(int x)
{
    m1.lock();

    cout<< std::this_thread::get_id() << endl;
    iTotal += x;

    m1.unlock();
}


int main()
{
    thread T1(Add, 10);
    thread T2(Add, 20);

    if(T1.joinable())
        T1.join();

    if(T2.joinable())
        T2.join();

    m1.lock();
    cout<< iTotal << endl;
    m1.unlock();

    return 0;



}