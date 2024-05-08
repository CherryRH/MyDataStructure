cmake_minimum_required(VERSION 3.28)
project(SkipList)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SkipList
        main.cpp
        skiplist.cpp
        skiplist.h)
