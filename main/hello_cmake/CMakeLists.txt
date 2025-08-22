cmake_minimum_required(VERSION 3.16)

add_library(hello_cmake_lib STATIC hello_cmake_src.c)
target_include_directories(hello_cmake_lib PUBLIC "include")