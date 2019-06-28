// © 2018 Joseph Cameron - All Rights Reserved

#include <string>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/final_action.h>

using namespace jfc;

/// \brief example of a handle creation function e.g: gl_genbuffer
/// "1" represents a valid handle value for this fake handle initialization api.
template<class T>
T create()
{
    return T(1);
}

/// \brief example of a handle cleanup function e.g: gl_deletebuffer
/// A valid handle value is any non-zero arithmetic value. A zero value represents a null handle.
/// Attempting to destroy a null handle is an error case for this fake api.
template<class T>
void destroy(T &a)
{
    REQUIRE((a != 0)); //Checking that the managed object has not been deleted (e.g: problem with move operator/ctor or for whatever reason a copy operator/ctor has been defined... which destroys "ownership" and invites UB into the code of users of final_action)

    REQUIRE((a = 0) == 0);
}

TEMPLATE_LIST_TEST_CASE("final_action tests", "[final_action]", type::arithmetic)
{
    using test_type = final_action<TestType>;

    SECTION("creation and destruction")
    {
        test_type a(create<TestType>(), [](TestType a)
        {
            destroy(a);
        });

        REQUIRE(a.get() == 1);
    }
    
    SECTION("move operator")
    {
        test_type a(create<TestType>(), [](TestType a)
        {
            destroy(a);
        });

        test_type b = std::move(a);

        REQUIRE(b.get() == 1);
    }
    
    SECTION("move ctor")
    {
        test_type a(create<TestType>(), [](TestType a)
        {
            destroy(a);
        });

        test_type b(std::move(a));

        REQUIRE(b.get() == 1);
    }
}

