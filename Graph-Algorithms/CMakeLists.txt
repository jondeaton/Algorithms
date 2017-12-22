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
        include/graph.hpp src/graph.cpp
        include/node.hpp src/node.cpp
        include/edge.hpp
        include/path.hpp
        include/path-finder.hpp src/path-finder.cpp
        include/priority-queue.hpp
        src/main.cpp)

add_executable(path-finding ${SRC})