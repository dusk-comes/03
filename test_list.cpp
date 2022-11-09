#include <catch2/catch_test_macros.hpp>

#include "list.hpp"
#include "allocator.hpp"

TEST_CASE("iterate over list")
{
    const size_t elements = 3;
    List<int, Alloc<elements, Link<int>>> l;
    for (size_t i = 0; i < elements; ++i)
        l.push_back(i);

    REQUIRE(l.size() == elements);

    int expected = 0;
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        REQUIRE(expected++ == *it);
    }
}
