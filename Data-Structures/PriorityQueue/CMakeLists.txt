cmake_minimum_required(VERSION 3.9)
project(PriorityQueue C)

set(CMAKE_C_STANDARD 99)

add_executable(test-pq test.c priority_queue.h priority_queue.c)
