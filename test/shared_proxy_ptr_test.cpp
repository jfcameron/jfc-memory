// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/shared_proxy_ptr.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("shared_proxy_ptr constructors", "[shared_proxy_ptr]", type::arithmetic)
{
    using shared_proxy_type = shared_proxy_ptr<TestType>;

    SECTION("standard ctor")
    {
        shared_proxy_type ptr([]()
        {
            return new TestType(1);
        });

        REQUIRE(!ptr.initialized());

        REQUIRE(*ptr == 1);

        REQUIRE(ptr.initialized());
    }
}

