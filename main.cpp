#include <utility>
#include <map>
#include <iostream>
#include "allocator.hpp"

template <int P>
struct Factorial
{
    static const int value = P * Factorial<P - 1>::value;
};

template <>
struct Factorial<0>
{
    static const int value = 1;
};


int main()
{
    std::map<int, int, std::less<int>, Alloc<4, std::pair<const int, int>>> m;
    std::cout << "start to fill" << std::endl;
    m[1] = Factorial<1>::value;
    m[2] = Factorial<2>::value;
    m[3] = Factorial<3>::value;
    m[4] = Factorial<4>::value;
    //m[5] = Factorial<5>::value; Allocator throw the error here
        
    return 0;
}
