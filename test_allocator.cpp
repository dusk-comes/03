#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "allocator.hpp"
#include <map>
#include <string>
#include <new>

TEST_CASE( "map<int, int> uses custom allocator", "[map<int, int>]" )
{
    std::map<int, int, std::less<>, Alloc<10, std::pair<const int, int>>> m;
    for (auto i = 0; i < 10; ++i)
        m[i] = i;

    for (auto i = 0; i < 10; ++i)
        REQUIRE(m.at(i) == i);

    REQUIRE_THROWS_AS(m[11], const std::bad_alloc&);
}

TEST_CASE( "map<int, string> uses custom allocator", "[map<int, string>]" )
{

    using alloc = Alloc<10, std::pair<const int, std::string>>;
    std::map<int, std::string, std::less<>, alloc> m;
    m[1] = "one";
    m[2] = "two";
    m[3] = "three";
    m[4] = "four";
    m[5] = "five";
    m[6] = "six";
    m[7] = "seven";
    m[8] = "eight";
    m[9] = "nine";
    m[10] = "ten";

    REQUIRE(m.at(1) == "one");
    REQUIRE(m.at(2) == "two");
    REQUIRE(m.at(3) == "three");
    REQUIRE(m.at(4) == "four");
    REQUIRE(m.at(5) == "five");
    REQUIRE(m.at(6) == "six");
    REQUIRE(m.at(7) == "seven");
    REQUIRE(m.at(8) == "eight");
    REQUIRE(m.at(9) == "nine");
    REQUIRE(m.at(10) == "ten");

    REQUIRE_THROWS_AS(m[11], const std::bad_alloc&);
}

