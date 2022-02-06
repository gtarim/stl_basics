#include <iostream>

template <typename T, int capacity=0>
class queue
{
    int _size;
    struct Node
    {
        T data;
        Node* next;
        explicit Node( const T& data, Node* next=nullptr ) : data{data}, next{ next }{ } 
        explicit Node( T&& data, Node* next ) noexcept : data{std::move(data)}, next{ next }{ } 
    };
    Node* _front;
    Node* _back;
public:
    queue() : _size{}, _front{nullptr}, _back{nullptr} { }
    ~queue() { while(_front) { pop(); } }

    void push( const T& data )
    {
        if( capacity )
        {
          if( capacity == _size ) return;
        }   

        Node* node = new Node{ data };

        if( !_size ) { _front = node; }
        else { _back->next = node; }
        _back = node;
        ++_size;
    }

    void pop() 
    {
        if( !_front ) return;
        Node* tmp = _front;
        _front = _front->next;
        delete tmp;
        --_size;
    }

    T& front() 
    {
        if( !_front ) throw std::runtime_error("no front exist!");
        return _front->data; 
    }

    const T& front() const 
    {
        if( !_front ) throw std::runtime_error("no front exist!");
        return _front->data; 
    }

    T& back()
    {
        if( !_back ) throw std::runtime_error("no back exist!");
        return _back->data; 
    }

    const T& back() const 
    {
        if( !_back ) throw std::runtime_error("no back exist!");
        return _back->data; 
    }
    bool empty() const { return _size; }
    int size() const { return _size; }
    int cap() { return capacity; }
};

int main()
{
    queue<int> que;
    que.push( 10 );
    que.push( 20 );
    que.push( 30 );
    std::cout << que.front() << "\n";
    std::cout << que.back() << "\n\n";

    que.pop();
    std::cout << que.front() << "\n";
    que.pop();
    std::cout << que.front() << "\n";

}