// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/lazy_ptr.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("lazy_ptr constructors", "[lazy_ptr]", type::integral)
{
    using lazy_type = lazy_ptr<TestType>;

    SECTION("standard ctor")
    {
        lazy_type ptr([]()
        {
            return new TestType(1);
        });

        REQUIRE(!ptr.initialized());

        REQUIRE(*ptr == 1);

        REQUIRE(ptr.initialized());
    }
}

