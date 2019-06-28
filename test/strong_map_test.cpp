// © 2019 Joseph Cameron - All Rights Reserved

#include <string>
#include <string_view>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/strong_map.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("strong_map constructors", "[strong_map]", type::arithmetic)
{
    using strong_map_type = strong_map<std::string_view, TestType>;

    SECTION("standard usage")
    {
        strong_map_type map;

        /*REQUIRE(map.size() == 0);

        map.push_back(TestType(1));

        REQUIRE(map.size() == 1);

        if (auto sp = map[0].lock()) REQUIRE(*sp == 1);*/
    }
}

