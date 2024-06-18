cmake_minimum_required(VERSION 3.28)
project(FastLOB)

set(CMAKE_CXX_STANDARD 26)

add_library(FastLOB SHARED library.cpp
        Order.h)
