// © 2019 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/strong_vector.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("strong_vector constructors", "[strong_vector]", type::arithmetic)
{
    using strong_vector_type = strong_vector<TestType>;

    SECTION("standard usage")
    {
        strong_vector_type vector;

        REQUIRE(vector.size() == 0);
        
        vector.push_back(TestType(1));

        REQUIRE(vector.size() == 1);

        if (auto sp = vector[0].lock()) REQUIRE(*sp == 1);
    }
}

