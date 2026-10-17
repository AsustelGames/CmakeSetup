cmake_minimum_required(VERSION 3.16)

set(lib_name "imgui")
project(${lib_name})

set(${lib_name}_sources
    ${lib_name}/imgui.cpp
    ${lib_name}/imgui_draw.cpp
    ${lib_name}/imgui_widgets.cpp
    ${lib_name}/imgui_tables.cpp
    ${lib_name}/imgui_demo.cpp

    ${lib_name}/backends/imgui_impl_glfw.cpp
    ${lib_name}/backends/imgui_impl_opengl3.cpp
)
add_library(${lib_name} INTERFACE ${${lib_name}_sources})
target_include_directories(${lib_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
