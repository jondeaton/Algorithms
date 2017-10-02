cmake_minimum_required(VERSION 3.8)
project(AVL-Tree)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")

set(SRC RedBlackTree.h.h RedBlackTree.tpp test-RedBlackTree.cpp)

add_executable(test-tree ${SRC})