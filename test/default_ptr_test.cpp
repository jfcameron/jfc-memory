// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/default_ptr.h>

using namespace jfc;

/// \brief example of a handle creation function e.g: gl_genbuffer
template<class T>
T create()
{
    return T(1);
}

/// \brief example of a handle cleanup function e.g: gl_deletebuffer
template<class T>
void destroy(T &a)
{
    REQUIRE((a = 0) == 0);
}

TEMPLATE_LIST_TEST_CASE("default_ptr everything", "[default_ptr]", type::arithmetic)
{
    using test_type = default_ptr<TestType>;

    SECTION("everything")
    {
        test_type a(create<TestType>(), [](TestType a)
        {
            destroy(a);
        });

        REQUIRE(a.get() == 1);
    }
}

