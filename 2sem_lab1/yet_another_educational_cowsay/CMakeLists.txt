cmake_minimum_required(VERSION 3.26)
project(lab_4_mipt/part_1)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(yet_another_educational_cowsay
        src/Cow.cpp
        src/Parser.cpp
        src/Field.cpp
        src/Cloud.cpp
        src/ASCIIPicture.cpp
        src/main.cpp
)

target_include_directories(yet_another_educational_cowsay PRIVATE ${PROJECT_SOURCE_DIR}/include)

file(COPY ${PROJECT_SOURCE_DIR}/cows DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/clouds DESTINATION ${CMAKE_BINARY_DIR})
