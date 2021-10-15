#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

condition_variable cv;
mutex m1;

int TotalBalance = 0;

void AddMoney(int money)
{
    while(TotalBalance < 600)
    {
        unique_lock<mutex> lock(m1);
        cv.wait(lock, [] { return TotalBalance < 1000 ? true : false; });
        TotalBalance += money;
        cout<< "Deposit : " << money <<endl;
        cout<< "Current Balance : " << TotalBalance << endl;
        cv.notify_one();
    }
}

void WithdrawMoney(int x)
{
    
    while (TotalBalance < 200)
    {
        cout<< "Current Balance Before: " << TotalBalance << endl;
        unique_lock<mutex> ul(m1);

        cv.wait(ul, [] { return TotalBalance >= 500 ? true : false; });
        if(TotalBalance >= x)
        {
            TotalBalance -= x;
            cout<< "Withdraw successful"<<endl;
        }
        else
        {
            cout<< "Insufficient Balance "<< endl;
        }

        cv.notify_one();
        cout<< "Current Balance : " << TotalBalance << endl;
    }

}

int main()
{
    thread T1(AddMoney, 100);
    thread T2(WithdrawMoney, 50);

    T1.join();
    T2.join();
    return 0;
}