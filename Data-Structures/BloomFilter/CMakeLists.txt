cmake_minimum_required(VERSION 2.6)
project(BloomFilter)
set(CMAKE_CXX_STANDARD 17)

# cmake -DCMAKE_BUILD_TYPE=Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Mode: Release")
    set(CMAKE_C_FLAGS  "-Ofast")
else()
    message(STATUS "Mode: Debug")
    set(CMAKE_C_FLAGS  "-g -O0 -Wall -Wextra -pedantic")
endif()

include_directories(include src test)

set(BloomFilterSRC
    include/bloom-filter.hpp)

add_executable(bf-test test/test-bloom-filter.cpp ${BloomFilterSRC})
