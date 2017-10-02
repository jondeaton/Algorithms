cmake_minimum_required(VERSION 3.8)
project(RedBlackTree)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -pedantic")

set(SRC AVL-Tree.h AVL-Tree.tpp test-AVL.cpp)

add_executable(test-tree ${SRC})