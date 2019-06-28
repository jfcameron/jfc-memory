// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/static_pool.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("static_pool constructors", "[static_pool]", type::arithmetic)
{
    const size_t size = 1;

    using static_pool_type = static_pool<TestType, size>;

    SECTION("usage")
    {
        static_pool_type pool([]()
        {
            return TestType(1);
        });

        std::vector<std::shared_ptr<TestType>> consumers;

        for (size_t i = 0; i < size; ++i) 
        {
            consumers.push_back(pool.get());

            REQUIRE(consumers.back());
        }
        
        consumers.push_back(pool.get());

        REQUIRE(!consumers.back());
    }
}

