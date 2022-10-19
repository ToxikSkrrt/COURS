cmake_minimum_required(VERSION 2.6)
project(foobar C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
set(CMAKE_C_LIBS "-fb")
add_executable(foobar foobar.c libfb.a)

target_link_libraries(foobar m)

add_library(fb foo.c bar.c)