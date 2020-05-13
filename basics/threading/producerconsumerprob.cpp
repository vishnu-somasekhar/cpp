//! PRODUCER CONSUMER PROBLEM / BOUNDED BUFFER PROBLEM

/*************PROBLEM STATEMENT*****************
 *
 * Producer will produce and consumer will consume with syncronization of a common buffer
 * Until producer produce consumer cant consume anything
 * Thread will use condetion_variable to notify each other
 *  
 ***/

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <thread>

std::condition_variable cv;
std::mutex m;
std::deque<int> buffer;
const unsigned int iBufferSize = 50;


void producer(int iValue)
{
    while(iValue)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [](){return buffer.size() < iBufferSize; });
        buffer.push_back(iValue);
        std::cout<< "Produced: " << iValue << std::endl;
        --iValue;
        lock.unlock();
        cv.notify_one();
    }
}

void consumer()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [](){ return buffer.size() > 0; });
        std::cout<< "Consumed : " << buffer.back()  << std::endl;
        buffer.pop_back();
        lock.unlock();
        cv.notify_one();
    }
    
}

int main()
{
    std::thread t1(producer, 10);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    std::cout<<"Done"<< std::endl;
    return 0;
}