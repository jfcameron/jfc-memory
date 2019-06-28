// © 2019 Joseph Cameron - All Rights Reserved

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <jfc/catch.hpp>
#include <jfc/types.h>

#include <jfc/locking_queue.h>

using namespace jfc;

const unsigned int thread_count = std::thread::hardware_concurrency();

TEMPLATE_LIST_TEST_CASE("locking_queue test", "[locking_queue]", type::arithmetic)
{
    using test_type = locking_queue<TestType>;

    SECTION("thread group consumption")
    {
        test_type queue;

        for (auto i = 1, s = 100; i < s; ++i) queue.push(TestType(i));

        std::vector<std::thread> threads;

        for (unsigned int i = 0, s = thread_count > 1 ? thread_count - 1 : 0; i < s; ++i) 
            threads.push_back(std::thread([&]() 
            {
                TestType ioData = 0;

                if (queue.pop(ioData)) 
                    REQUIRE(ioData != 0);
                else 
                    REQUIRE(ioData == 0);
            }));
        
        for (auto &thread : threads) thread.join();
    }
    
    SECTION("thread group production and consumption")
    {
        test_type queue;

        std::vector<std::thread> threads;

        for (unsigned int i = 0, s = thread_count > 1 ? thread_count - 1 : 0; i < s; ++i) 
            threads.push_back(std::thread([&]() 
            {
                queue.push(1);
                queue.push(2);

                TestType ioData = 0;

                if (queue.pop(ioData)) 
                    REQUIRE(ioData != 0);
                else 
                    REQUIRE(ioData == 0);
            }));

        for (auto &thread : threads) thread.join();
    }
}

