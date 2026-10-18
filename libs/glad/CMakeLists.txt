cmake_minimum_required(VERSION 3.16)

set(lib_name "glad")
project(${lib_name} LANGUAGES C)

set(${lib_name}_sources ${lib_name}/src/gl.c)
add_library(${lib_name} STATIC ${${lib_name}_sources})
target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

