cmake_minimum_required(VERSION 3.28)
project(RadixTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RadixTree
        main.cpp
        radix_tree.cpp
        radix_tree.hpp)
