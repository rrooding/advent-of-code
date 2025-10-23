cmake_minimum_required(VERSION 3.20)

# Create a library for this day's solution
add_library(aoc_2015_01 STATIC
    solution.cpp
)

target_include_directories(aoc_2015_01 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(aoc_2015_01 PUBLIC aoc_shared)
