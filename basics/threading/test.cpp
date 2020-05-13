#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <fstream>

using namespace std;

condition_variable cv;
mutex m;

deque<int> buffer;
const int max_buffer_size = 50;


void producer(int icount)
{
    while(icount > 0)
    {
        unique_lock<mutex> l(m);
        cv.wait(l, [](){return buffer.size() < max_buffer_size;});
        buffer.push_back(icount);
        cout<<"Produced value "<< icount << endl;
        --icount;
        l.unlock();
        cv.notify_one();
        this_thread::sleep_for(1s);
    }

}

void consumer()
{
    while(true)
    {
        unique_lock<mutex> l(m);
        cv.wait(l, [](){return buffer.size() > 0;});
        int value = buffer.back();
        buffer.pop_back();
        cout<<"Consumed value "<< value<<endl;
        l.unlock();
        cv.notify_one();
        this_thread::sleep_for(2s);
        if(buffer.size() == 0)
            break;
    }
}

bool isSubString(string s1, string s2)
{
    for(int i = 0; i <= (s2.length() - s1.length()); i++)
    {
        int j = 0;
        for(; j < s1.length(); j++)
        {
            if(s2[i+j] != s1[j])
            break;
        }

        if(j == s1.length())
            return true;
    }

    return false;
}

int main()
{
    // thread t(&producer, 5);
    // thread t2(&consumer);
    // t.join();
    // t2.join();

    string str1("Steel");
    string str2("Man of Steel");

    if(isSubString(str1, str2))
        cout<<"Found"<<endl;
    else
    {
        cout<<"Not Found"<<endl;
    }
    

   // fstream new_file;

    // new_file.open("threading.cpp", ios::app);

    // if(new_file)
    // {
    //     new_file<<"\nTest File write";
    //     new_file.close();
    // }

    // new_file.open("threading.cpp", ios::in);

    // if(new_file.is_open())
    // {
    //     string str;

    //     while(getline(new_file, str))
    //     {
    //         if(str.compare("Test File write") == 0)
    //         {
    //             new_file
    //         }
    //     }
    //         cout<<str<<endl;
        
        

    //     new_file.close();
    // }

    return 0;
}