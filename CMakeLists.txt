cmake_minimum_required(VERSION 3.30)
project(CQueue)

set(CMAKE_CXX_STANDARD 14)

add_library(
        CQueue STATIC

        src/circular_queue.cpp
        src/circular_queue.hpp
)
