cmake_minimum_required(VERSION 3.16)

add_library(hello STATIC hello_src.c)
target_include_directories(hello PUBLIC ".")