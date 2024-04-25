cmake_minimum_required(VERSION 3.28)
project(CompressedRadixTree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CompressedRadixTree
        compressed_radix_tree.cpp
        compressed_radix_tree.hpp
        main.cpp)
