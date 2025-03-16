include(GoogleTest)
set(CMAKE_CXX_STANDARD 20)

add_executable(subvector_tests
        subvector_test.cpp
)

target_link_libraries(subvector_tests
        PRIVATE
        linalg
        gtest
        gtest_main
)

gtest_discover_tests(subvector_tests)