#include <iostream>
#include <thread>
#include <future>
#include <algorithm>


using namespace std;

typedef unsigned long long ull;

ull FindOddSum(promise<ull>&& prom, ull start, ull end)
{
    ull sum = 0;
    for(ull i = start; i < end; i++)
    {
        if(i % 2 != 0)
            sum += i;
        
    }

    prom.set_value(sum);
}

int main()
{
    promise<ull> sumOut;
    future<ull> SumFuture = sumOut.get_future();

    thread T1(FindOddSum, std::move(sumOut), 0, 1900000000);

    cout<<"Waiting for result!\n";
    cout<<"Result: "<< SumFuture.get()<<endl;
    cout<<"Complete\n";
    T1.join();
    return 0;
}