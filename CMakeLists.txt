cmake_minimum_required(VERSION 3.6)
project(Project2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES project2.cc project2.h)
add_executable(Project2 ${SOURCE_FILES})