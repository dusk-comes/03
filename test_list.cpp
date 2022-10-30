#include <catch2/catch_test_macros.hpp>

#include "list.hpp"

TEST_CASE("fill list of int")
{
    List<int> l;
    auto head = l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    REQUIRE(head->val == 1);
    REQUIRE(head->next->val == 2);
    REQUIRE(head->next->next->val == 3);
}

TEST_CASE("iterate over list")
{
    List<int> l;

    for (int i = 1; i < 4; ++i) l.push_back(i);

    REQUIRE(l.size() == 3);

    int expected = 1;
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        REQUIRE(expected++ == *it);
    }
}
