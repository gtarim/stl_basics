#include <iostream>

template <typename T>
class unique_ptr
{
    T* ptr;
public:
    explicit unique_ptr() : ptr{ nullptr } { }
    explicit unique_ptr( T* _ptr ) : ptr{ _ptr } { }
    ~unique_ptr() { reset(); }
    unique_ptr( const unique_ptr& ) = delete;
    unique_ptr& operator=( const unique_ptr& ) = delete;
    unique_ptr( unique_ptr&& oth ) : ptr { std::move( oth.ptr ) } { oth.ptr = nullptr; }
    unique_ptr& operator=( unique_ptr&& oth ) 
    {
        if( this == &oth ) return *this;
        reset();
        ptr = oth.ptr;
        oth.ptr = nullptr;
        return *this;
    }
    T* release()
    {
        T* nptr = nullptr;
        std::swap( ptr, nptr );
        return nptr;
    }

    void reset()
    {
        if( ptr != nullptr )
        {
            if( std::is_array_v<T> )
                delete[] ptr;
            else
                delete ptr;
        }
        ptr = nullptr;
    }

    T* get() const { return ptr; }
    operator bool() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    void swap( unique_ptr&& oth) { std::swap( this, oth ); }
};

int main()
{
    unique_ptr<int> ptr;

    ptr = std::move( unique_ptr<int>{ new int{1120} } );
    std::cout << *ptr.get() << "\n";
}