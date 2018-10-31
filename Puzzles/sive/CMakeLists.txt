cmake_minimum_required(VERSION 2.6)
project(sive)

find_package(gtest)
add_executable(sive-test sive.hpp test.cpp)
set(test_flags -std=c++14 -g -O0 -Wall -Wextra -pedantic -DDEBUG)
target_compile_options(sive-test PUBLIC ${test_flags})
target_link_libraries(sive-test gtest)

find_package(benchmark)
add_executable(sive-bench sive.hpp bench.cpp)
set(bench_flags -std=c++14 -Ofast -fno-omit-frame-pointer -DNDEBUG)
target_compile_options(sive-bench PUBLIC ${bench_flags})
target_link_libraries(sive-bench benchmark)


