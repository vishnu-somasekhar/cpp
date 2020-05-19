#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <queue>



class ThreadPool{

public:
    explicit ThreadPool(int iNumThreads)
    {
        start(iNumThreads);
    }

    ~ThreadPool()
    {
        stop();
    }

    using Task = std::function<void()>;

    template<typename T>
    auto enqueue(T task)->std::future<decltype(task())>
    {
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mTasks.emplace(task);
        }

        mConditionVariable.notify_one();
    }


private:

    std::vector<std::thread> mThreads;
    std::condition_variable mConditionVariable;
    std::mutex mMutex;
    bool mStopped{false};
    std::queue<Task> mTasks;

    void start(int iNumberThreads)
    {
        for(auto i = 0; i < iNumberThreads; i++)
        {
            mThreads.emplace_back([=]{
                while(true)
                {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(mMutex);
                        mConditionVariable.wait(lock, [=]{return mStopped || !mTasks.empty();} );

                        if(mStopped && mTasks.empty())
                            break;

                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }    

                    task();
                    
                }
            });
        }
    }

    void stop() noexcept
    {
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mStopped = true;
        }

        mConditionVariable.notify_all();

        for(auto &thread : mThreads)
            thread.join();
    }

};

int main()
{
    ThreadPool pool{4};
    
    pool.enqueue([]{
        using namespace std::chrono_literals;
        std::cout<<"Print from task 1 start"<<std::endl;
        std::this_thread::sleep_for(2s);
        std::cout<<"Print from task 1 ends"<<std::endl;
    });

     pool.enqueue([]{
        using namespace std::chrono_literals;
        std::cout<<"Print from task 2 start"<<std::endl;
        std::this_thread::sleep_for(2s);
        std::cout<<"Print from task 2 ends"<<std::endl;
    });
    pool.enqueue([]{
        using namespace std::chrono_literals;
        std::cout<<"Print from task 3 start"<<std::endl;
        std::this_thread::sleep_for(2s);
        std::cout<<"Print from task 3 ends"<<std::endl;
    });
    pool.enqueue([]{
        using namespace std::chrono_literals;
        std::cout<<"Print from task 4 start"<<std::endl;
        std::this_thread::sleep_for(2s);
        std::cout<<"Print from task 4 ends"<<std::endl;
    });
    pool.enqueue([]{
        using namespace std::chrono_literals;
        std::cout<<"Print from task 5 start"<<std::endl;
        std::this_thread::sleep_for(2s);
        std::cout<<"Print from task 5 ends"<<std::endl;
    });

    return 0;
}