set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required (VERSION 2.8)
project (Graph-Algorithms)
set (CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    SET (CMAKE_CXX_FLAGS "-Ofast")
else()
    SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")
endif()

include_directories(include src)

set(SRC
        include/graph.hpp           src/graph.tpp
        include/node.hpp            src/node.tpp
        include/edge.hpp
        include/path.hpp
        include/dijkstra.hpp
        include/custom-priority-queue.hpp   src/custom-priority-queue.cpp
        src/dijkstra.cpp)

add_executable(dijkstra ${SRC})