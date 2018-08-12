cmake_minimum_required(VERSION 2.6)
project(PermIterator)
set(CMAKE_CXX_STANDARD 17)

# cmake -DCMAKE_BUILD_TYPE=Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Mode: Release")
    set(CMAKE_CXX_FLAGS  "-Ofast")
else()
    message(STATUS "Mode: Debug")
    set(CMAKE_CXX_FLAGS  "-g -O0 -Wall -Wextra -pedantic")
endif()

set(SRC PermIterator.hpp)
add_executable(test-perm main.cpp ${SRC})
