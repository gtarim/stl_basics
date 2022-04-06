#include <iostream>
#include <forward_list>
#include <list>
#include <vector>

template <typename InputIterator, typename Distance>                    
void advance_impl(InputIterator& iter, Distance n, std::input_iterator_tag) 
{
    if (n >= 0)
    {
        while (n--) 
            ++iter; 
    }
}

template <typename BidirectionalIterator, typename Distance>              
void advance_impl(BidirectionalIterator& iter, Distance n, std::bidirectional_iterator_tag) 
{
    if (n >= 0)
    {
        while (n--)
            ++iter;
    }
    else
    {
        while (n++) 
            --iter;
    } 
}

template <typename RandomAccessIterator, typename Distance>             
void advance_impl(RandomAccessIterator& iter, Distance n, std::random_access_iterator_tag) 
{
    iter += n;
}

template <typename InputIterator, typename Distance>                    // (4)
void advance_(InputIterator& iter, Distance n) 
{
    typename std::iterator_traits<InputIterator>::iterator_category category;    
    advance_impl(iter, n, category);                                               
}

int main()
{
    std::forward_list<int> flist { 10, 20, 30, 40, 50 };
    auto iterFList = flist.begin();
    advance_(iterFList, 2);
    std::cout << *iterFList << "\n";

    std::list<int> list { 10, 20, 30, 40, 50 };
    auto iterList = list.begin();
    advance_(iterList, 2);
    std::cout << *iterList << "\n";

    std::vector<int> vec { 10, 20, 30, 40, 50 };
    auto iterVec = vec.begin();
    advance_(iterVec, 2);
    std::cout << *iterVec << "\n";
}