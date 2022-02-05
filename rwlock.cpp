#include <iostream>
#include <vector>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <functional>
#include <type_traits>

class RWLock
{
    std::shared_mutex mutex;
public:
    RWLock( ) { }
    RWLock ( const RWLock& ) = delete;
    
    template <typename Callback, typename ...Args>
    auto read( Callback&& f, Args&&... args)
    {
        std::shared_lock<std::shared_mutex> lock( mutex );
        auto task( std::bind( std::forward<Callback>(f), std::forward<Args>(args)... ) );
        // std::function<typename std::result_of<Callback(Args...)>::type()> task( std::bind( std::forward<Callback>(f), std::forward<Args>(args)... ) ); // pretty same as above.
        return task();
    }

    template <typename Callback, typename ...Args>
    auto write( Callback&& f, Args&&... args )
    {
        std::unique_lock<std::shared_mutex> lock( mutex );
        auto task { std::bind( std::forward<Callback>(f), std::forward<Args>(args)... ) };
        return task();
    }
};

class IntContainer
{
    std::vector<int> data;
public:
    explicit IntContainer( std::vector<int> data ) : data{ data } { }

    int get( int index )
    {
        if( index >= data.size() ) return -1;
        return data[index];
    }

    void set( int index, int val )
    {
        if( index >= data.size() ) return;
        data[index] = val;
    }
};

std::vector<int> data = { 10, 20, 30, 40, 50 };
IntContainer container{ data };
RWLock rwlock{};

void readerFunc()
{
    int i = 4;
    while( i > 0)
    {
        auto val = rwlock.read( &IntContainer::get, &container, i );
        std::cout << "reader=" << val << "\n";
        --i;
    }
}

void writerFunc()
{
    int i = 4;
    while( i > 0)
    {
        rwlock.write( &IntContainer::set, &container, i, i*100 );
        --i;
    }
}

int main()
{
    std::thread thReader{ readerFunc };
    thReader.join();

    std::thread thWriter{ writerFunc };
    thReader = std::move( std::thread{ readerFunc } );
    thWriter.join();
    thReader.join();

    return 1;
}