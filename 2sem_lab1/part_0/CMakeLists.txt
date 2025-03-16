cmake_minimum_required(VERSION 3.26)
project(lab_4_mipt/part_0)

set(CMAKE_CXX_STANDARD 20)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
        GIT_PROGRESS TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(linalg)
add_subdirectory(tests/matrix_tests)
add_subdirectory(tests/subvector_tests)
