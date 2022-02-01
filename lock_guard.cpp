#include <iostream>
#include <thread>
#include <mutex>

template <typename Mutex>
class lock_guard
{
    Mutex& mutex;
public:
    explicit lock_guard( Mutex& mutex ) : mutex{ mutex } { mutex.lock(); }
    ~lock_guard() { mutex.unlock(); }
};

std::mutex mutex;
int i = 0;

void th1()
{
    while( i < 10 )
    {
        lock_guard<std::mutex> lock( mutex );
        std::cout << "th1=" << i++ << "\n";
    }
}

void th2()
{
    while( i < 10 )
    {
        lock_guard<std::mutex> lock( mutex );
        std::cout << "th2=" << i++ << "\n";
    }
}

int main()
{
    std::thread t1 ( th1 );
    std::thread t2 ( th2 );
    t1.join();
    t2.join();
}