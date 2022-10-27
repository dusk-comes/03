#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "allocator.hpp"
#include <map>
#include <new>

TEST_CASE( "map<int, int> uses custom allocator", "[map<int, int>]" )
{
    std::map<int, int, std::less<>, Alloc<3, std::pair<const int, int>>> m;

    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    
    SECTION( "map contains exact values" )
    {
        REQUIRE(m.at(1) == 1);
        REQUIRE(m.at(2) == 2);
        REQUIRE(m.at(3) == 3);
    }

    SECTION( "cannot add more than allocator permits")
    {
        REQUIRE_THROWS_AS(m[4], const std::bad_alloc&);
    }
}
