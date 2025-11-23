cmake_minimum_required (VERSION 3.16)
project (SDLProjectTemplate)


set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(PRODUCTION_BUILD "Make this a production build" False) # Clear cmake cache after editing
option(OPENGL_DEBUGGING "Debug OpenGL" True) # Clear cmake cache after editing
set(OPENGL_PLATFORM "Windows" CACHE STRING "Target platform for OpenGL") # Clear cmake cache after editing
set_property(CACHE OPENGL_PLATFORM PROPERTY STRINGS Windows Linux MacOS Web Android Ios)

if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2) # make sure SIMD optimizations take place
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION False)

set(BUILD_SHARED_LIBS OFF)



# Add Glad
if(OPENGL_PLATFORM STREQUAL "Windows" OR OPENGL_PLATFORM STREQUAL "Linux")
	if(NOT OPENGL_DEBUGGING)
		set(GLAD_PATH Libs/Glad/Release/GL_4_6_Core)
	else()
		set(GLAD_PATH Libs/Glad/Debug/GL_4_6_Core)
	endif()

elseif(OPENGL_PLATFORM STREQUAL "MacOS")
	if(NOT OPENGL_DEBUGGING)
		set(GLAD_PATH Libs/Glad/Release/GL_4_1_Core)
	else()
		set(GLAD_PATH Libs/Glad/Debug/GL_4_1_Core)
	endif()

else()
	if(OPENGL_PLATFORM STREQUAL "Web")
		if(NOT OPENGL_DEBUGGING)
			set(GLAD_PATH Libs/Glad/Release/GLES_3_0_Core)
		else()
			set(GLAD_PATH Libs/Glad/Debug/GLES_3_0_Core)
		endif()

	else()
		if(NOT OPENGL_DEBUGGING)
			set(GLAD_PATH Libs/Glad/Release/GLES_3_2_Core)
		else()
			set(GLAD_PATH Libs/Glad/Debug/GLES_3_2_Core)
		endif()
	endif()
endif()

include_directories(${GLAD_PATH}/include)

set(Glad_SOURCES
	${GLAD_PATH}/src/glad.c
)

add_library(Glad ${Glad_SOURCES})


# Add SDL3
include_directories(Libs/SDL/include)
add_subdirectory(Libs/SDL)


# Add SDL3
include_directories(Libs/SDL_Net/include)
add_subdirectory(Libs/SDL_Net)


# Add Box2D
include_directories(Libs/Box2D/include)
add_subdirectory(Libs/Box2D)


# Add FastNoiseLite
include_directories(Libs/FastNoiseLite)


# Add STB
include_directories(Libs/STB)

set(STB_Image_SOURCES
	Libs/STB/stb_image.cpp
	Libs/STB/stb_image_resize2.cpp
	Libs/STB/stb_image_write.cpp
	Libs/STB/stb_truetype.cpp
)

add_library(STB_Image ${STB_Image_SOURCES})


# Add Imgui
include_directories(Libs/Imgui)
include_directories(Libs/Imgui/imgui)

set(Imgui_SOURCES
   Libs/Imgui/imgui/imgui.cpp
   Libs/Imgui/imgui/imgui_draw.cpp
   Libs/Imgui/imgui/imgui_widgets.cpp
   Libs/Imgui/imgui/imgui_tables.cpp
   Libs/Imgui/imgui/imgui_demo.cpp
	Libs/Imgui/imgui/backends/imgui_impl_sdl3.cpp
	Libs/Imgui/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(Imgui ${Imgui_SOURCES} )


# Add ENet
include_directories(Libs/ENet/include)
add_subdirectory(Libs/ENet)


# Add GLM
include_directories(Libs/GLM)
add_subdirectory(Libs/GLM)


# Add MiniAudio
include_directories(Libs/MiniAudio)
add_subdirectory(Libs/MiniAudio/miniaudio)



# Link all of the source files, add an executable and link the required libraries for your platform  
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${MY_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE STB_Image miniaudio SDL3_net::SDL3_net SDL3::SDL3 box2d::box2d Imgui Glad)


if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./Assets/")

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
	
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

# Defining USING_GL/GLES_VERSION_...
if(OPENGL_PLATFORM STREQUAL "Windows" OR OPENGL_PLATFORM STREQUAL "Linux")
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MAJOR_VERSION=4)
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MINOR_VERSION=6)
elseif(OPENGL_PLATFORM STREQUAL "MacOS")
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MAJOR_VERSION=4)
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MINOR_VERSION=1)
else()
	if(OPENGL_PLATFORM STREQUAL "Web")
		target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MAJOR_VERSION=3)
		target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MINOR_VERSION=0)
	else()
		target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MAJOR_VERSION=3)
		target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC USING_GL_GLES_MINOR_VERSION=2)
	endif()
endif()

message(STATUS "${CMAKE_PROJECT_NAME}: PRODUCTION_BUILD = '${PRODUCTION_BUILD}'")
message(STATUS "${CMAKE_PROJECT_NAME}: OPENGL_PLATFORM = '${OPENGL_PLATFORM}'")
message(STATUS "${CMAKE_PROJECT_NAME}: OPENGL_DEBUGGING = '${OPENGL_DEBUGGING}'")

