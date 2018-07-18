cmake_minimum_required(VERSION 2.6)
project(clib)

macro(use_c99)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
        endif ()
    else ()
        set (CMAKE_C_STANDARD 99)
    endif ()
endmacro(use_c99)
use_c99()

# cmake -DCMAKE_BUILD_TYPE=Release
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Mode: Release")
    set(CMAKE_C_FLAGS  "-Ofast")
else()
    message(STATUS "Mode: Debug")
    set(CMAKE_C_FLAGS  "-g -O0 -Wall -Wextra -pedantic")
endif()

include_directories(include src test)

set(HASHTABLE_SRC
        include/murmur3.h       src/murmur3.c
        include/cmap.h          src/cmap.c
        include/hash.h          src/hash.c)

add_executable(test-pq test/test.c include/priority_queue.h src/priority_queue.c)

add_executable(test-cmap test/cmap_test.c ${HASHTABLE_SRC})
