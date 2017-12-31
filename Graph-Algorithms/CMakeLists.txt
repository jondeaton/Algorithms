set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required (VERSION 2.8)
project (Graph-Algorithms)
set (CMAKE_CXX_STANDARD 17)

# cmake -DCMAKE_BUILD_TYPE=Debug ..
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Mode: Debug")
    SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")
else()
    message(STATUS "Mode: Release")
    SET (CMAKE_CXX_FLAGS "-Ofast")
endif()

include_directories(include src)
set(SRC
        include/graph.hpp src/graph.cpp
        include/node.hpp src/node.cpp
        include/type-traits.hpp
        include/edge.hpp
        include/path.hpp
        include/coordinate.hpp
        include/path-finder.hpp
        include/priority-queue.hpp)

add_executable(path-finder src/main.cpp ${SRC})
add_executable(pq-test src/pq-test.cpp ${SRC})