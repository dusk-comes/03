#include <catch2/catch_test_macros.hpp>

#include "list.hpp"

TEST_CASE("iterate over list")
{
    List<int> l;
    for (int i = 0; i < 3; ++i)
        l.push_back(i);

    REQUIRE(l.size() == 3);

    int expected = 0;
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        REQUIRE(expected++ == *it);
    }
}
