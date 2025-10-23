cmake_minimum_required(VERSION 3.20)
project(advent_of_code)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Enable clang-tidy (always enabled)
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
    message(WARNING "clang-tidy not found. Please install it for code quality checks.")
endif()

# Options to restrict which tests are collected
set(AOC_TEST_YEAR "" CACHE STRING "Limit tests to a single year (e.g. 2025)")
set(AOC_TEST_DAY "" CACHE STRING "Limit tests to a single day (requires AOC_TEST_YEAR, e.g. 01)")

# Fetch GoogleTest and enable testing
include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "Disable gmock")
set(INSTALL_GTEST OFF CACHE BOOL "Disable gtest install")
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Shared headers
add_subdirectory(shared)

# Automatically discover and add all year/day directories
file(GLOB YEAR_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "[0-9][0-9][0-9][0-9]")
set(SOLUTION_LIBS)
set(TEST_SOURCES)
set(TEST_DAY_ENTRIES)  # for ctest per-day registration

foreach(YEAR_DIR ${YEAR_DIRS})
    file(GLOB DAY_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "${YEAR_DIR}/[0-9][0-9]")
    foreach(DAY_DIR ${DAY_DIRS})
        if(EXISTS "${CMAKE_SOURCE_DIR}/${DAY_DIR}/CMakeLists.txt")
            # Respect filter options
            string(SUBSTRING ${DAY_DIR} 0 4 CURRENT_YEAR)
            string(SUBSTRING ${DAY_DIR} 5 2 CURRENT_DAY)
            if(AOC_TEST_YEAR AND NOT CURRENT_YEAR STREQUAL AOC_TEST_YEAR)
                add_subdirectory(${DAY_DIR})
                continue()
            endif()
            if(AOC_TEST_DAY AND (NOT AOC_TEST_YEAR OR NOT CURRENT_DAY STREQUAL AOC_TEST_DAY))
                add_subdirectory(${DAY_DIR})
                continue()
            endif()

            add_subdirectory(${DAY_DIR})
            string(REPLACE "/" "_" LIB_NAME ${DAY_DIR})
            list(APPEND SOLUTION_LIBS aoc_${LIB_NAME})

            # Collect *Tests.cpp files in this day directory
            file(GLOB DAY_TESTS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/${DAY_DIR}/*Tests.cpp")
            if(DAY_TESTS)
                list(APPEND TEST_SOURCES ${DAY_TESTS})
                # Register a ctest entry for this day using gtest filter prefix convention
                # Suites should be prefixed with Y<year>D<day>
                list(APPEND TEST_DAY_ENTRIES ${DAY_DIR})
            endif()
        endif()
    endforeach()
endforeach()

# Create the main executable
add_executable(aoc main.cpp)

# Link all solution libraries with WHOLE_ARCHIVE to ensure static initializers are called
if(SOLUTION_LIBS)
    if(APPLE)
        target_link_libraries(aoc PRIVATE ${SOLUTION_LIBS})
        foreach(LIB ${SOLUTION_LIBS})
            target_link_options(aoc PRIVATE "LINKER:-force_load,$<TARGET_FILE:${LIB}>")
        endforeach()
    else()
        target_link_libraries(aoc PRIVATE -Wl,--whole-archive ${SOLUTION_LIBS} -Wl,--no-whole-archive)
    endif()
endif()

# Aggregated test executable (only if tests were found)
if(TEST_SOURCES)
    add_executable(aoc_tests ${TEST_SOURCES})
    # Disable clang-tidy for test target to avoid noisy system-header issues
    set_target_properties(aoc_tests PROPERTIES CXX_CLANG_TIDY "")
    target_include_directories(aoc_tests PRIVATE ${CMAKE_SOURCE_DIR})
    if(SOLUTION_LIBS)
        target_link_libraries(aoc_tests PRIVATE ${SOLUTION_LIBS} GTest::gtest_main)
    else()
        target_link_libraries(aoc_tests PRIVATE GTest::gtest_main)
    endif()

    # Master test (all)
    add_test(NAME all COMMAND aoc_tests)

    # Per-day focused tests using gtest filter prefix (Y<year>D<day>*)
    foreach(DAY_PATH ${TEST_DAY_ENTRIES})
        string(SUBSTRING ${DAY_PATH} 0 4 T_YEAR)
        string(SUBSTRING ${DAY_PATH} 5 2 T_DAY)
        set(TEST_NAME "${T_YEAR}_${T_DAY}")
        add_test(NAME ${TEST_NAME} COMMAND aoc_tests --gtest_filter=Y${T_YEAR}D${T_DAY}*)
        set_tests_properties(${TEST_NAME} PROPERTIES LABELS "aoc;year=${T_YEAR};day=${T_DAY}")
    endforeach()

    # Label the all test
    set_tests_properties(all PROPERTIES LABELS "aoc")
endif()
