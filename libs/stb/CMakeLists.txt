cmake_minimum_required(VERSION 3.16)

set(lib_name "stb")
project(${lib_name} LANGUAGES C)

set(${lib_name}_sources ${lib_name}/stb.c)
add_library(${lib_name} INTERFACE ${${lib_name}_sources})
target_include_directories(${lib_name} INTERFACE ${lib_name}/include)
