cmake_minimum_required(VERSION 3.14)
project(multiThread)

set(CMAKE_CXX_STANDARD 14)

add_executable(multiThread main.cpp Thread.h ThreadTest.cpp ThreadTest.h NewThread.h)