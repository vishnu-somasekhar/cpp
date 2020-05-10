//! RACE CONDITION
//! 2 or more process/thread happend to change a common/shared data at same time.
//! If there is a chance to race condition then we have to protect it and the protected data/section is called critical section/region

//! MUTEX is used to avoid race condition by using lock() and unlock()
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int _MyMoney = 10;
int _iTryLockSample = 0;

std::mutex m;
std::mutex _mTryLock;

void addMoney(int x)
{
    m.lock();
    _MyMoney += x;
    m.unlock();
}

void trylock_sample()
{
    for(int i = 0; i < 10000; i++)
        {
            if(_mTryLock.try_lock())
            {
                _iTryLockSample++;
                _mTryLock.unlock();
            }
        }
}

int main()
{
    thread t1(addMoney, 10);
    thread t2(addMoney, 20);

    t1.join();
    t2.join();

    cout<<_MyMoney<<endl;

    thread t3(trylock_sample);
    thread t4(trylock_sample);

    t3.join();
    t4.join();

    cout<< _iTryLockSample << endl;

    return 0;
}