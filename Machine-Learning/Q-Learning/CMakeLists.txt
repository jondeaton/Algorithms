cmake_minimum_required(VERSION 3.9)
project(Q_Learning)

set(CMAKE_CXX_STANDARD 17)

include_directories(include src)

set (SRC
        include/actor.hpp
        include/environment.hpp
        include/learner.hpp
        include/maze.hpp)

add_executable(Q_Learning ${SRC} main.cpp)