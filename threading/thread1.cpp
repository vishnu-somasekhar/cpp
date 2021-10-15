#include <thread>
#include <iostream>
#include <future>
#include <chrono>

using namespace std;
int AddEven(int x) {

    auto start_time = chrono::high_resolution_clock::now();
    std::cout<< "AddEven Thread started 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<< "AddEven Thread started" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    int sum = 0;
    while(x != 0)
    {
        if(x % 2 == 0)
            sum += x;
        

        x--;
    }
    std::cout<< "AddEven Thread finished but wait fro 1 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<< "AddEven Thread wait over" << std::endl;

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ellapsed = end_time - start_time;
    std::cout<< "Time taken by thread AddEven : "<< ellapsed.count() << "ms\n";
    return sum;
}
int main()
{
    auto start_time = chrono::high_resolution_clock::now();
    std::cout<<"Main Started" << std::endl;
    auto f1 = std::async(std::launch::async, AddEven, 10);
    this_thread::sleep_for(chrono::seconds(3));
    std::cout<<"Main thread started" << std::endl;
    int x = f1.get();
    std:;this_thread::sleep_for(std::chrono::seconds(3));
    std::cout<< x << std::endl;

    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ellapsed = end_time - start_time;
    std::cout<< "Time taken by Main : " << ellapsed.count() << "ms\n";

    return 0;
}