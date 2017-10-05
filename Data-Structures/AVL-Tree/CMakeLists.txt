cmake_minimum_required(VERSION 3.8)
project(RedBlackTree)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")

set(SRC BinaryNode.h
        AVL-Tree.h AVL-Tree.cpp
        test-AVL.cpp)

add_executable(test-tree ${SRC})