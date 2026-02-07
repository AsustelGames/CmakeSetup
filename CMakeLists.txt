cmake_minimum_required (VERSION 3.16)
project (CmakeSetup)


set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)


# SDL3
include_directories(libs/sdl3/include)
find_package(SDL3)
if(NOT SDL3_FOUND)
    add_subdirectory(libs/sdl3)
endif()

# Glad GL 4.6 Core
set(glad_sources libs/glad/src/glad.c)
add_library(glad ${glad_sources})
target_include_directories(glad PUBLIC libs/glad/include)

# GLM
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE libs/glm)

# Enet
include_directories(libs/enet/include)

# Imgui
set(imgui_sources
   libs/imgui/imgui.cpp
   libs/imgui/imgui_draw.cpp
   libs/imgui/imgui_widgets.cpp
   libs/imgui/imgui_tables.cpp
   libs/imgui/imgui_demo.cpp
   libs/imgui/backends/imgui_impl_sdl3.cpp
   libs/imgui/backends/imgui_impl_opengl3.cpp
   libs/imgui/backends/imgui_impl_sdlrenderer3.cpp
)
add_library(imgui ${imgui_sources})
target_include_directories(imgui PUBLIC libs/imgui libs/imgui/backends)

# MiniAudio
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE libs/miniaudio)

# FastNoiseLite
include_directories(libs/fnl)

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


include_directories(libs/assimp/include)
add_subdirectory(libs/assimp)

# stb image, image_write, image_resize2 and stb_truetype
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE libs/stb)


# Reconfigure your project after changing these options
option(PRODUCTION_BUILD "Make this a production build" False)
option(USE_OPENGL "Use OpenGL instead of SDL Renderer" False)


# Get all .c, .h .cpp and .hpp files
set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE my_sources CONFIGURE_DEPENDS ${src_path}/*.cpp ${src_path}/*.hpp ${src_path}/*.c ${src_path}/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${my_sources})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 stb imgui miniaudio glm glad)

if(USE_OPENGL)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC USE_OPENGL)
endif()

if(MSVC) 
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) # make sure SIMD optimizations take place
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()


if(EMSCRIPTEN)
    set(device_system "WEB")
    set(device_type "BROWSER")
    
elseif(ANDROID)
    set(device_system "ANDROID")
    set(device_type "MOBILE")
    
elseif(IOS)
    set(device_system "IOS")
    set(device_type "MOBILE")
    
elseif(WIN32)
    set(device_system "WINDOWS")
    set(device_type "COMPUTER")
    
elseif(APPLE)
    set(device_system "MACOS")
    set(device_type "COMPUTER")
    
elseif(UNIX)
    set(device_system "LINUX")
    set(device_type "COMPUTER")
    
else()
    set(device_system "UNKNOWN")
    set(device_type "UNKNOWN")
endif()


if(PRODUCTION_BUILD) # Change and define ASSETS_PATH and PRODUCTION_BUILD depending on PRODUCTION_BUILD option
	set(ASSETS_PATH "./assets")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD)
    
    if(device_system STREQUAL WINDOWS) # Disable windows console
        set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()
else()
    set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets")
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
endif()


target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CURRENT_DEVICE_SYSTEM="${device_system}")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CURRENT_DEVICE_TYPE="${device_type}")

message(NOTICE "+== ${CMAKE_PROJECT_NAME}")
message(NOTICE "|==> USE_OPENGL = ${USE_OPENGL}")
message(NOTICE "|==> CURRENT_DEVICE_SYSTEM = ${device_system}")
message(NOTICE "|==> CURRENT_DEVICE_TYPE = ${device_type}")
message(NOTICE "|==> PRODUCTION_BUILD = ${PRODUCTION_BUILD}")
message(NOTICE "+== ")
