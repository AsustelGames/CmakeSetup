#
cmake_minimum_required(VERSION 3.16)
project(CmakeSetup)


set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)


# GLFW
include_directories(libs/glfw/include)
find_package(glfw3 3.4)
if(NOT glfw3_FOUND)
   add_subdirectory(libs/glfw)
endif()

# Glad GL 4.6 Core (Custom CMakeLists.txt)
add_subdirectory(libs/glad)

# GLM
add_subdirectory(libs/glm)

# Imgui (Custom CMakeLists.txt)
add_subdirectory(libs/imgui)

# MiniAudio
add_subdirectory(libs/miniaudio)


# Assimp
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "")

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_EXPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_EXPORTER ON CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

# include_directories(libs/assimp/include)
add_subdirectory(libs/assimp)


# stb-image, image_write, image_resize2 and truetype (Custom CMakeLists.txt)
add_subdirectory(libs/stb)


# Reconfigure your project after changing these options
option(production_build "Make this a production build" False)



# Get all .c, .h .cpp and .hpp files
set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE my_sources CONFIGURE_DEPENDS ${src_path}/*.cpp ${src_path}/*.hpp ${src_path}/*.c ${src_path}/*.h)

add_executable (${CMAKE_PROJECT_NAME} ${my_sources})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Add macro if this is a debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
   target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEBUG_BUILD)
   set(CMAKE_BUILD_TYPE Debug)
endif()

if(MSVC) 
   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:>")
   target_compile_options(${PROJECT_NAME} PRIVATE /arch:AVX2) # make sure SIMD optimizations take place
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE assimp glad glfw stb imgui miniaudio glm)


# Make the ASSETS_PATH definition point to the correct folder
if(production_build)
   set(assets_path "./assets")
   target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD)
else()
   set(assets_path "${CMAKE_CURRENT_SOURCE_DIR}/assets")
   target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
endif()

# Print information
message(NOTICE "+== ${CMAKE_PROJECT_NAME}")
message(NOTICE "|==> PRODUCTION_BUILD = ${production_build}")
message(NOTICE "|==> BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(NOTICE "+==")
