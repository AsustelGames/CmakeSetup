cmake_minimum_required (VERSION 3.16)
project (CmakeSetup)


set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF)

if(MSVC) 
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/arch:AVX2) # make sure SIMD optimizations take place
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()


# SDL3
include_directories(libs/sdl3/include)
find_package(SDL3)
if(NOT SDL3_FOUND)
    add_subdirectory(libs/sdl3)
endif()


# Glad GL 4.6 Core
include_directories(libs/glad/include)
set(glad_sources libs/glad/src/glad.c)
add_library(glad ${glad_sources})

# GLM
include_directories(libs/glm)
add_subdirectory(libs/glm)

# Enet
include_directories(libs/enet/include)
add_subdirectory(libs/enet)

# SDL_Net
include_directories(libs/sdl_net/include)
add_subdirectory(libs/sdl_net)

# Imgui
include_directories(libs/imgui)
set(imgui_sources
   libs/imgui/imgui.cpp
   libs/imgui/imgui_draw.cpp
   libs/imgui/imgui_widgets.cpp
   libs/imgui/imgui_tables.cpp
   libs/imgui/imgui_demo.cpp
   libs/imgui/backends/imgui_impl_sdl3.cpp
   libs/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${imgui_sources} )

# MiniAudio
include_directories(libs/miniaudio)
add_subdirectory(libs/miniaudio)

# FastNoiseLite
include_directories(libs/fnl)

# Assimp
#include_directories(libs/assimp/include)
#add_subdirectory(libs/assimp)

# stb image, image_write, image_resize2 and stb_truetype
include_directories(libs/stb)
set(stb_sources
	libs/stb/stb_image.cpp
	libs/stb/stb_image_resize2.cpp
	libs/stb/stb_image_write.cpp
	libs/stb/stb_truetype.cpp
)
add_library(stb ${stb_sources})


option(PRODUCTION_BUILD "Make this a production build" False) # Clear cmake cache after editing

# Get all .c, .h .cpp and .hpp files
set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE my_sources CONFIGURE_DEPENDS ${src_path}/*.cpp ${src_path}/*.hpp ${src_path}/*.c ${src_path}/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${my_sources})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3_net::SDL3_net SDL3::SDL3 stb imgui miniaudio enet glm glad)


if(PRODUCTION_BUILD) # Change and define ASSETS_PATH and PRODUCTION_BUILD depending on PRODUCTION_BUILD option
	set(ASSETS_PATH "./Assets")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./Assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()


if(WIN32) # Windows
    set(device_system "WINDOWS")
    set(device_type "COMPUTER")
elseif(UNIX AND NOT APPLE) # Linux
    set(device_system "LINUX")
    set(device_type "COMPUTER")
elseif(APPLE) # MacOS
    set(device_system "MACOS")
    set(device_type "COMPUTER")
else() # Unknown
    set(device_system "UNKNOWN")
    set(device_type "UNKNOWN")
endif()

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEVICE_SYSTEM="${device_system}")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEVICE_TYPE="${device_type}")
message(NOTICE "+== ${CMAKE_PROJECT_NAME}")
message(NOTICE "|==> DEVICE_SYSTEM = ${device_system}")
message(NOTICE "|==> DEVICE_TYPE = ${device_type}")
message(NOTICE "|==> PRODUCTION_BUILD = ${PRODUCTION_BUILD}")
message(NOTICE "+== ")