cmake_minimum_required(VERSION 3.14)
project(epollEcho)

set(CMAKE_CXX_STANDARD 14)

add_executable(epollEcho main.cpp pollServer.cpp pollServer.h)