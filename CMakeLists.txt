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
    add_subdirectory(libs/Sdl3)
endif()



# SDL_TTF
set(SDLTTF_VENDORED ON)
include_directories(libs/Sdl_ttf/include)
add_subdirectory(libs/Sdl_ttf)

# SDL_Image
include_directories(libs/Sdl_image/include)
add_subdirectory(libs/Sdl_image)

# Glad GL 4.6 Core
include_directories(libs/Glad/include)
set(glad_sources libs/Glad/src/glad.c)
add_library(glad ${glad_sources})

# GLM
include_directories(libs/Glm)
add_subdirectory(libs/Glm)

# Enet
include_directories(libs/Enet/include)
add_subdirectory(libs/Enet)

# SDL_Net
include_directories(libs/Sdl_net/include)
add_subdirectory(libs/Sdl_net)

# Imgui
include_directories(libs/Imgui)
set(imgui_sources
   libs/Imgui/imgui.cpp
   libs/Imgui/imgui_draw.cpp
   libs/Imgui/imgui_widgets.cpp
   libs/Imgui/imgui_tables.cpp
   libs/Imgui/imgui_demo.cpp
   libs/Imgui/backends/imgui_impl_sdl3.cpp
   libs/Imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui ${imgui_sources} )

# MiniAudio
include_directories(libs/Miniaudio)
add_subdirectory(libs/Miniaudio)

# FastNoiseLite
include_directories(libs/FNL)

# Box2D
include_directories(libs/Box2d/include)
add_subdirectory(libs/Box2d)

# Assimp
#include_directories(libs/assimp/include)
#add_subdirectory(libs/assimp)

# stb image, image_write, image_resize2 and stb_truetype
include_directories(libs/Stb)
set(stb_sources
	libs/Stb/stb_image.cpp
	libs/Stb/stb_image_resize2.cpp
	libs/Stb/stb_image_write.cpp
	libs/Stb/stb_truetype.cpp
)
add_library(stb ${stb_sources})


# Rebuild your project after changing these options
option(PRODUCTION_BUILD "Make this a production build" False)
option(USE_OPENGL "Use OpenGL instead of SDL Renderer" True)


# Get all .c, .h .cpp and .hpp files
set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE my_sources CONFIGURE_DEPENDS ${src_path}/*.cpp ${src_path}/*.hpp ${src_path}/*.c ${src_path}/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${my_sources})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf SDL3_net::SDL3_net SDL3::SDL3 stb imgui miniaudio enet glm glad box2d)


if(PRODUCTION_BUILD) # Change and define ASSETS_PATH and PRODUCTION_BUILD depending on PRODUCTION_BUILD option
	set(ASSETS_PATH "./Assets")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./Assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Assets")
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

if(USE_OPENGL) # Define USE_OPENGL depending on USE_OPENGL option
    set(using_opengl "TRUE")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC USE_OPENGL)
else()
    set(using_opengl "FALSE")
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

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEVICE_SYSTEM="${device_system}")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEVICE_TYPE="${device_type}")

message(NOTICE "+== ${CMAKE_PROJECT_NAME}")
message(NOTICE "|==> USE_OPENGL = ${using_opengl}")
message(NOTICE "|==> DEVICE_SYSTEM = ${device_system}")
message(NOTICE "|==> DEVICE_TYPE = ${device_type}")
message(NOTICE "|==> PRODUCTION_BUILD = ${PRODUCTION_BUILD}")
message(NOTICE "+== ")