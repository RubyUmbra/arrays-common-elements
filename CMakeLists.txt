cmake_minimum_required(VERSION 2.4)
project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test main.cpp avltree.cpp avltree.h arraycomparators.cpp arraycomparators.h radixsort.cpp radixsort.h)
