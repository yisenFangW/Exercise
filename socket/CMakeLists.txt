cmake_minimum_required(VERSION 3.14)
project(socket)

set(CMAKE_CXX_STANDARD 14)

add_executable(socket main.cpp epollEcho.cpp epollEcho.h)