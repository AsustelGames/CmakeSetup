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

set(BUILD_SHARED_LIBS OFF)


# Add SDL3
include_directories(Libs/SDL/include)
add_subdirectory(Libs/SDL)


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
	Libs/Imgui/imgui/backends/imgui_impl_sdlrenderer3.cpp
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
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Src/*.h)
add_executable (${CMAKE_PROJECT_NAME} ${MY_SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE STB_Image miniaudio SDL3::SDL3 box2d::box2d Imgui)


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
