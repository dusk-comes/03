#include <utility>
#include <map>
#include <iostream>
#include "allocator.hpp"

int factorial(int i)
{
    return (i == 0) ? 1 : factorial(i-1);
}


int main()
{
    std::map<int, int> m1;
    for (int i = 0; i < 10; ++i)
        m1[i] = factorial(i);

    std::map<int, int, std::less<int>, Alloc<10, std::pair<const int, int>>> m2;
    for (int i = 0; i < 10; ++i)
        m2[i] = factorial(i);
        
    return 0;
}
