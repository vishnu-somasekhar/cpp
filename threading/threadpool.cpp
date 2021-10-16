#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <vector>
#include <functional>
#include <queue>
#include <chrono>


class ThreadPool
{
public:

    using Task = std::function<void()>;

    explicit ThreadPool(int iCount)
    {
        Start(iCount);
    }

    ~ThreadPool()
    {
        Stop();
    }

    void Start(int iCount)
    {
        for(int i = 0; i < iCount; i++)
        {
            m_threads.emplace_back([=]{

                while(true)
                {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(mx);

                        cv.wait(lock, [=]{
                            return bStop || !m_task.empty();
                        });
                        
                        if(bStop && m_task.empty())
                            break;

                        task = std::move(m_task.front());
                        m_task.pop();
                    }

                    task();
                    
                    
                }

            });
        }

    }

    void Stop() noexcept
    {
        {
            std::unique_lock<std::mutex> lock(mx);
            bStop = true;    
        }

        cv.notify_all();

        for(auto &thread : m_threads)
            thread.join();

    }

    template<typename T>
    auto enqueue(T t)->std::future<decltype(t())>
    {
        auto wrapper = std::make_shared<std::packaged_task<decltype(t()) ()>>(std::move(t));
        {
            std::unique_lock<std::mutex> lock(mx);

            m_task.emplace([=]{
                (*wrapper)();
            });
        }
        cv.notify_one();

        return wrapper->get_future();
        
    }

private:

    std::vector<std::thread> m_threads;
    std::condition_variable cv;
    std::mutex mx;
    bool bStop{false};
    std::queue<Task> m_task;


};


int main()
{
    {
    ThreadPool tp{4};

    auto r1 = tp.enqueue([]{

        std::cout<<"inside thread 1"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout<<"inside thread 1 END"<<std::endl;
        return 1;
    });

    auto r2 = tp.enqueue([]{

        std::cout<<"inside thread  2"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout<<"inside thread 2 END"<<std::endl;
        return 2;
    });

    auto r3 = tp.enqueue([]{

        std::cout<<"inside thread 3"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout<<"inside thread 3 END"<<std::endl;
        return 3;
    });

    auto r4 = tp.enqueue([]{

        std::cout<<"inside thread  4"<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout<<"inside thread 4 END"<<std::endl;
        return 4;
    });

        auto r5 = tp.enqueue([]{

        std::cout<<"inside thread 5"<<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(3));
         std::cout<<"inside thread 5 END"<<std::endl;
        return 5;
    });

    auto r6 = tp.enqueue([]{

        std::cout<<" inside thread 6"<<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(4));
         std::cout<<"inside thread 6 END"<<std::endl;
        return 6;
    });

        auto r7 = tp.enqueue([]{

        std::cout<<"inside thread 7"<<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(5));
         std::cout<<"inside thread 7 END"<<std::endl;
        return 7;
    });

    auto r8 = tp.enqueue([]{

        std::cout<<"inside thread  8"<<std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(2));
         std::cout<<"inside thread 8 END"<<std::endl;
        return 8;
    });

    std::cout<< r1.get() + r2.get() + r3.get() + r4.get() + r5.get() + r6.get() + r7.get() + r8.get() << std::endl;
    }


    return 0;

}