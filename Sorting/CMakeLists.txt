cmake_minimum_required(VERSION 3.9)
project(Sorting)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sorting
        partition.cpp
        sorter.cpp
        sorter.h)
