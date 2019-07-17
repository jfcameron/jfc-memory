// © 2019 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/dynamic_pool.h>

using namespace jfc;

TEMPLATE_LIST_TEST_CASE("dynamic_pool tests", "[dynamic_pool]", type::integral)
{
    using pool_type = dynamic_pool<TestType>;

    SECTION("standard and move constructors, get operator")
    {
        pool_type pool(1, [](){return 1;});

        REQUIRE(*pool.get() == 1);

        pool_type b(std::move(pool));

        REQUIRE(*b.get() == 1);
    }

    SECTION("size and trim")
    {
        const typename pool_type::size_type initialSize = 1;

        pool_type pool(initialSize);

        std::vector<std::shared_ptr<TestType>> consumers(initialSize);

        for (typename std::remove_cv<decltype(initialSize)>::type i = 0; i < 1 + initialSize; ++i)
        {
            consumers.push_back(pool.get());
        }

        REQUIRE(pool.size() != initialSize);

        consumers.clear();
        pool.trim();

        REQUIRE(pool.size() == initialSize);
    }
}

