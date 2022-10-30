#include <catch2/catch_test_macros.hpp>

#include "list.hpp"

TEST_CASE( "fill list of int", "[list<int>]" )
{
    List<int> l;
    auto head = l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    REQUIRE(head->val == 1);
    REQUIRE(head->next->val == 2);
    REQUIRE(head->next->next->val == 3);
}

