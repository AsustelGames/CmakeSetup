cmake_minimum_required (VERSION 3.16)
project (SDLProjectTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(PRODUCTION_BUILD "Make this a production build" False)

if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION False)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Libraries as static libraries" FORCE)

# Add SDL3
include_directories(Libs/SDL3/include)
add_subdirectory(Libs/SDL3)


# Add Box2D
include_directories(Libs/Box2D/include)
add_subdirectory(Libs/Box2D)


# Add SDL_Mixer
include_directories(Libs/SDL_Mixer/include)
add_subdirectory(Libs/SDL_Mixer)


# Add STB_Image
include_directories(Libs/STB_Image)


# Add FastNoiseLite
include_directories(Libs/FastNoiseLite)


# Add Imgui
include_directories(Libs/Imgui)
include_directories(Libs/Imgui/backends)


set(Imgui_SOURCES
    Libs/Imgui/imgui.cpp
    Libs/Imgui/imgui_draw.cpp
    Libs/Imgui/imgui_widgets.cpp
    Libs/Imgui/imgui_tables.cpp
    Libs/Imgui/imgui_demo.cpp
	Libs/Imgui/backends/imgui_impl_sdl3.cpp
	Libs/Imgui/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(Imgui ${Imgui_SOURCES} )


# Add ENet
include_directories(Libs/ENet/include)
add_subdirectory(Libs/ENet)



# Link all of the source files, add an executable and link the required libraries for your platform  
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${MY_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE box2d::box2d SDL3_mixer::SDL3_mixer SDL3::SDL3 Imgui)


if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="./Assets/") 

	# remove the option to debug asserts.
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Assets/")
	#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=3)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 
endif()

if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()
