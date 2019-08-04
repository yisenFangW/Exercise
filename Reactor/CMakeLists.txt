cmake_minimum_required(VERSION 3.14)
project(Reactor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Reactor main.cpp thread_pool.cpp thread_pool.h raector.cpp)