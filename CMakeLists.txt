# 
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
add_library(glad STATIC ${glad_sources})
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
   #libs/imgui/backends/imgui_impl_vulkan.cpp
   )
   add_library(imgui STATIC ${imgui_sources})
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
option(production_build "Make this a production build" False)


# Only 1 graphics renderer can be active at a time.
# If you leave this option empty or select an invalid graphics renderer it will default to the SDL_Renderer
set(graphics_renderer "OpenGL" CACHE STRING "Available options: Sdl, OpenGL or Vulkan")
set_property(CACHE graphics_renderer PROPERTY STRINGS Sdl OpenGL Vulkan)



# Get all .c, .h .cpp and .hpp files
set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE my_sources CONFIGURE_DEPENDS ${src_path}/*.cpp ${src_path}/*.hpp ${src_path}/*.c ${src_path}/*.h)

add_executable (${CMAKE_PROJECT_NAME} ${my_sources})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Add macro if this is a debug build
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG_BUILD>)
set(debug_build $<CONFIG:Debug>)

if(MSVC) 
   set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:>")
   target_compile_options(${PROJECT_NAME} PRIVATE /arch:AVX2) # make sure SIMD optimizations take place
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3 stb imgui miniaudio glm glad)


# Renderer macros
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC USING_SDL_RENDERING=1)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC USING_OPENGL_RENDERING=2)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC USING_VULKAN_RENDERING=3)

if(graphics_renderer STREQUAL "Sdl")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_GRAPHICS_RENDERER=1)
elseif(graphics_renderer STREQUAL "OpenGL")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_GRAPHICS_RENDERER=2)
elseif(graphics_renderer STREQUAL "Vulkan")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_GRAPHICS_RENDERER=3)
else()
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_GRAPHICS_RENDERER=1)
   message(WARNING "==> Option current_graphics_renderer is empty or invalid")
   message(WARNING "==> Using SDL_Renderer instead")
   set(graphics_renderer "Sdl")
endif()


# Device system variables
set(device_system_web 1)
set(device_system_android 2)
set(device_system_ios 3)
set(device_system_windows 4)
set(device_system_macos 5)
set(device_system_linux 6)
set(device_system_unknown 7)

# Device system macros
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_WEB=${device_system_web})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_ANDROID=${device_system_android})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_IOS=${device_system_ios})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_WINDOWS=${device_system_windows})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_MACOS=${device_system_macos})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_LINUX=${device_system_linux})
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM_UNKNOWN=${device_system_unknown})

if(EMSCRIPTEN)
   set(device_system "WEB")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_web})
   
elseif(ANDROID)
   set(device_system "ANDROID")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_android})
   
elseif(IOS)
   set(device_system "IOS")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_ios})
   
elseif(WIN32)
   set(device_system "WINDOWS")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_windows})
   
elseif(APPLE)
   set(device_system "MACOS")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_macos})
   
elseif(UNIX)
   set(device_system "LINUX")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_linux})
   
else()
   set(device_system "UNKNOWN")
   target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC CURRENT_DEVICE_SYSTEM=${device_system_unknown})
endif()

# Current device system string macro
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC CURRENT_DEVICE_SYSTEM_STRING="${device_system}")


# Change and define ASSETS_PATH and PRODUCTION_BUILD depending on production_build option
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
message(NOTICE "|==> CURRENT_GRAPHICS_RENDERER = ${graphics_renderer}")
message(NOTICE "|==> CURRENT_DEVICE_SYSTEM = ${device_system}")
message(NOTICE "|==> PRODUCTION_BUILD = ${production_build}")
message(NOTICE "|==> DEBUG_BUILD = ${debug_build}")
message(NOTICE "+==")



# Preprocessor definitions in cpp


# Graphics
#
# USING_SDL_RENDERING=3 -> [INT] Always 1
# USING_OPENGL_RENDERING=1 -> [INT] Always 2
# USING_VULKAN_RENDERING=2 -> [INT] Always 3
#
# CURRENT_GRAPHICS_RENDERER -> [INT] Can be either 1, 2 or 3 depending on what you're using


# Devices & Oses
#
# CURRENT_DEVICE_SYSTEM -> [STRING] Can be either WEB, ANDROID, IOS, WINDOWS, MACOS, LINUX or UNKNOWN
#
#
#
#

