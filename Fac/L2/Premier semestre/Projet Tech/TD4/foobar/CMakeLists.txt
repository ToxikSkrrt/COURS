cmake_minimum_required(VERSION 2.6)
project(foobar C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
add_executable(foobar foobar.c bar.c foo.c)
