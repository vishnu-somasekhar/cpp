#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

int MAX_BUFFER = 50;
deque<int> buffer;
condition_variable cv;
mutex m;


void Producer(int x)
{
    while(x > 0)
    {
        unique_lock<mutex> lock1(m);

        cv.wait(lock1, []{ 
            return buffer.size() < MAX_BUFFER? true : false;
        });

        buffer.push_back(x);
        cout<<"_____Produced : "<< x << endl;
        x--;
        lock1.unlock();
        cv.notify_all();
    }
}

void consumer1()
{
    while(true)
    {
        unique_lock<mutex> lock2(m);
        cv.wait(lock2, []{
            return buffer.size() >= 1 ? true : false;
        });

        int val = buffer.back();
        buffer.pop_back();
        cout<< "consumer1 Consumed : " << val << endl;
        lock2.unlock();
        cv.notify_all();
    }
}
void consumer2()
{
    while(true)
    {
        unique_lock<mutex> lock2(m);
        cv.wait(lock2, []{
            return buffer.size() >= 1 ? true : false;
        });

        int val = buffer.back();
        buffer.pop_back();
        cout<< "consumer2 Consumed : " << val << endl;
        lock2.unlock();
        cv.notify_all();
    }
}


int main()
{
    thread T1(Producer, 100);
    thread T2(consumer1);
    thread T3(consumer2);

    T1.join();
    T2.join();
    T3.join();
    return 0;
}