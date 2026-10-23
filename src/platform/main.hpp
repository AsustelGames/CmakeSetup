#pragma once

#include <iostream>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"


#include "glm/glm.hpp"


void onCloseWindowRequest(GLFWwindow* window);
