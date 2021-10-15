#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int Val = 0;

std::recursive_mutex m1;

void Recursive(char c, int x)
{
    if( x > 0)
    {
        m1.lock();
        Val += x;
        cout<< "Thread "<< c << " Val " << Val << endl;
        Recursive(c, --x);

        m1.unlock();
    }

}

int main()
{
    thread T1(Recursive, '1', 5);
    thread T2(Recursive, '2', 5);

    T1.join();
    T2.join();
    return 0;
}