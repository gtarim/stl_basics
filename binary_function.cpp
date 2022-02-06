#include <iostream>
#include <vector>
#include <set>


class Human
{
    int age;
    std::string name;
public:
    explicit Human( std::string name, const int age ) : name{name}, age{age} { }
    ~Human() = default;
    auto getName() const { return name; }
    auto getAge() const { return age; }
    bool operator<( const Human& oth ) const { return age < oth.age; }
    friend std::ostream& operator<<( std::ostream& os, Human human) 
    {
        return os << human.name << " " << human.age << "\n";
    }
};

template <typename T>
struct cmp final : std::binary_function<T,T,bool>
{
    bool operator() ( const T& left, const T& right) const
    {
        return left < right; 
    }
};

int main()
{
    // std::set<Human> humanList;
    std::set<Human, cmp<Human>> humanList;
    humanList.insert( Human{ "human1", 31 } );
    humanList.insert( Human{ "human2", 30 } );
    humanList.insert( Human{ "human3", 29 } );
    humanList.insert( Human{ "human4", 33 } );
    humanList.insert( Human{ "human5", 22 } );


    for( auto const& item : humanList )
    {
        std::cout << item;
    }
}