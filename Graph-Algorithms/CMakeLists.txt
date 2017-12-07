cmake_minimum_required (VERSION 2.8)
project (Graph-Algorithms)
set (CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    SET (CMAKE_CXX_FLAGS "-Ofast")
else()
    SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")
endif()

set(SRC
        dijkstra.cpp
        graph.hpp       graph.cpp)

add_executable(dijkstra ${SRC})