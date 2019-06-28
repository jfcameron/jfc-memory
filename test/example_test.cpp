// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

//using namespace gdk;

TEMPLATE_LIST_TEST_CASE("vector constructors", "[vector]", type::integral)
{
    using vector_type = std::vector<TestType>;

    SECTION("Default constructor produces a zero vector")
    {
        vector_type vector;

        REQUIRE(vector.size() == 0);
    }
}

