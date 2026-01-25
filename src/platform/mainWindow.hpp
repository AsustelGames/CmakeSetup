#pragma once
#define USE_OPENGL

#include "SDL3/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#ifndef USE_OPENGL
   #include "imgui_impl_sdlrenderer3.h"
#else
   #include "backends/imgui_impl_opengl3.h"
#endif

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "errorReportingOpenGL.hpp"

#include "../game/game.hpp"
#include "../game/tools/colors.hpp"