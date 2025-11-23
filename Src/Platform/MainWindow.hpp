#pragma once


#include "SDL3/SDL.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl3.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

#ifndef USING_GLES
   #include "ErrorReportingOpenGL.hpp"
#endif

#include "../Game/Game.hpp"
#include "../Game/Rendering/Colors.hpp"