include(GoogleTest)
set(CMAKE_CXX_STANDARD 20)

add_executable(matrix_tests matrix_test.cpp)

target_link_libraries(matrix_tests
        PRIVATE
        linalg
        gtest
        gtest_main
)

gtest_discover_tests(matrix_tests)