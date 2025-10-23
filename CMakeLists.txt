cmake_minimum_required(VERSION 3.20)
project(advent_of_code)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
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

# Add shared library
add_subdirectory(shared)

# Automatically discover and add all year/day directories
file(GLOB YEAR_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "[0-9][0-9][0-9][0-9]")
set(SOLUTION_LIBS)

foreach(YEAR_DIR ${YEAR_DIRS})
    file(GLOB DAY_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "${YEAR_DIR}/[0-9][0-9]")
    foreach(DAY_DIR ${DAY_DIRS})
        if(EXISTS "${CMAKE_SOURCE_DIR}/${DAY_DIR}/CMakeLists.txt")
            add_subdirectory(${DAY_DIR})

            # Extract year and day from path (e.g., "2015/01")
            string(REPLACE "/" "_" LIB_NAME ${DAY_DIR})
            list(APPEND SOLUTION_LIBS aoc_${LIB_NAME})
        endif()
    endforeach()
endforeach()

# Create the main executable
add_executable(aoc main.cpp)

# Link all solution libraries with WHOLE_ARCHIVE to ensure static initializers are called
if(SOLUTION_LIBS)
    if(APPLE)
        # macOS uses -force_load
        target_link_libraries(aoc PRIVATE ${SOLUTION_LIBS})
        foreach(LIB ${SOLUTION_LIBS})
            target_link_options(aoc PRIVATE "LINKER:-force_load,$<TARGET_FILE:${LIB}>")
        endforeach()
    else()
        # Linux uses --whole-archive
        target_link_libraries(aoc PRIVATE -Wl,--whole-archive ${SOLUTION_LIBS} -Wl,--no-whole-archive)
    endif()
endif()