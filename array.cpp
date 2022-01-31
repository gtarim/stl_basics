#include <iostream>

template <typename T, std::size_t size>
class array
{
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;

    T _data[size];
public:
    array() = default;
    template <typename ...Args>
    array( Args&& ...values ) : _data{ std::move( values ) ... } { }
    array( const array& ) = default;
    array& operator=( const array& ) = default;
    array( array && ) = default;
    array& operator=( array && ) = default;
    ~array() = default;

    constexpr reference operator[]( const std::size_t& index ) { return _data[index]; }
    constexpr const_reference operator[] ( const std::size_t& index) const { return _data[index]; }

    constexpr pointer begin() noexcept { return _data; }
    constexpr const_pointer begin() const noexcept { return _data; }

    constexpr pointer end() noexcept { return _data + size; }
    constexpr const_pointer end() const noexcept { return _data + size; }

    constexpr reference front() { return *begin(); }
    constexpr const_reference front() const { return *begin(); }

    constexpr reference back() { return (size) ? *( end()-1) : ( *end() ); }
    constexpr const_reference back() const { return (size) ? *( end()-1) : ( *end() ); }

    constexpr pointer data() noexcept { return &_data[0]; }
    constexpr const_pointer data() const noexcept { return &_data[0]; }
};

int main()
{
    array<int, 3> arr{ 10, 20, 30 };
    
    for( auto const& item : arr )
        std::cout << item << " ";
    std::cout << "\n";

    std::cout << "arr[1]=" << arr[1] << "\n";

    std::cout << "arr.begin()=" << *( arr.begin() ) << "\n";
    std::cout << "arr.end()-1=" << *(arr.end() - 1) << "\n";

    std::cout << "arr.front()=" << arr.front() << "\n";
    std::cout << "arr.back()=" << arr.back() << "\n";

    auto arr_clone = arr.data();
    std::cout << "arr_clone[1]=" << arr_clone[1] << "\n";

}