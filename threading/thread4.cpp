#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int X = 0, Y = 0;

std::mutex m1,m2;

void dosomethingElse() 
{ 
    std::this_thread::sleep_for(chrono::seconds(1));
}

void IncrementXY(int& XorY, std::mutex& m, const char* desc)
{
    for(int i = 0; i < 5; i++)
    {
        m.lock();

        //cout<<"Thread " << this_thread::get_id()<<endl;
        ++XorY;
        cout<< desc << " " << XorY<<endl;
        m.unlock();
        dosomethingElse();
    }
}

void ConusumeXY()
{
    int useCount = 5;
    int XplusY = 0;

    while(1)
    {
        int lockResult = std::try_lock(m1,m2);
        if(lockResult == -1)
        {
            if(X == 5 && Y == 5)
            {
                --useCount;
                XplusY += X + Y;
                X = 0;
                Y = 0;
                cout<< "XpluxY "<< XplusY << endl;
            }
            m1.unlock();
            m2.unlock();

        }

            if(useCount != 5)
                break;

    }
}

int main()
{
    std::thread T1(IncrementXY, std::ref(X), std::ref(m1), "X ");
    std::thread T2(IncrementXY, std::ref(Y), std::ref(m2), "Y ");
    std::thread T3(ConusumeXY);

    T1.join();
    T2.join();
    T3.join();

    cout<<"END"<<endl;
    return 0;
}