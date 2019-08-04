cmake_minimum_required(VERSION 3.14)
project(7_27)

set(CMAKE_CXX_STANDARD 14)

add_executable(7_27 main.cpp cal.cpp cal.h timestamp.cpp timestamp.h ThreadTest.h MessageQueue.h MutexLockGuard.h ThreadPool.cpp ThreadPool.h Thread.h)