#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

template <std::size_t size = 1>
class semaphore
{
    std::mutex mutex;
    std::condition_variable cvar;
    std::size_t count;
public:
    constexpr semaphore() : count{ size } {}
    semaphore( const semaphore& ) = delete;

    void acquire()
    {
        std::unique_lock<std::mutex> lock( mutex );
        cvar.wait( lock, [&]{ return count > 0; } );
        --count;
    }

    void release()
    {
        std::unique_lock<std::mutex> lock( mutex );
        ++count;
        lock.unlock();
        cvar.notify_all();
    }

    std::size_t max() { return size; }
};

semaphore<> sp;
void tf1()
{
    std::cout << "tf1 : began...\n";
    sp.acquire();
    std::cout << "tf1 : some operations...\n";
    std::this_thread::sleep_for( std::chrono::seconds(1) );
    std::cout << "tf1 : some more operations...\n";
    sp.release();
}

void tf2()
{
    std::cout << "tf2 : began...\n";
    sp.acquire();
    std::cout << "tf2 : some operations...\n";
    sp.release();
}


int main()
{
    std::cout << "semaphore size=" << sp.max() << "\n";
    
    std::thread t1( tf1 );
    std::thread t2( tf2 );

    t1.join();
    t2.join();

    return 1;
}