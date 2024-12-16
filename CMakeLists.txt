cmake_minimum_required(VERSION 3.30)
project(CQueue)

set(CMAKE_CXX_STANDARD 14)

# Header-only library
add_library(CQueue INTERFACE)

# Specify the header files for the interface library
target_include_directories(CQueue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
