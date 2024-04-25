cmake_minimum_required(VERSION 3.28)
project(RedBlackTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(RedBlackTree
        main.cpp
        redBlackTree.cpp
        redBlackTree.h
        util.hpp
)
