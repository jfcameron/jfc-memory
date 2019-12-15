# © 2018 Joseph Cameron - All Rights Reserved

jfc_add_tests(
    C++_STANDARD 17
    C_STANDARD 90

    TEST_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/default_ptr_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/dynamic_pool_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/shared_proxy_ptr_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/static_pool_test.cpp"
    
    INCLUDE_DIRECTORIES
        "${${PROJECT_NAME}_INCLUDE_DIRECTORIES}"
)

