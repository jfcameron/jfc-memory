# © 2018 Joseph Cameron - All Rights Reserved

jfc_add_tests(
    C++_STANDARD 17
    C_STANDARD 90

    TEST_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/default_ptr_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/dynamic_pool_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/final_action_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/lazy_ptr_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/locking_queue_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/resource_manager_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/static_pool_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/strong_map_test.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/strong_vector_test.cpp"

    INCLUDE_DIRECTORIES
        "${${PROJECT_NAME}_INCLUDE_DIRECTORIES}"
)
