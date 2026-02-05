#pragma once


#include "SDL3/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#ifdef USE_OPENGL
   #include "backends/imgui_impl_opengl3.h"
#else
   #include "imgui_impl_sdlrenderer3.h"
#endif

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <iostream>

#include "errorReportingOpenGL.hpp"

#include "../game/game.hpp"
#include "../game/tools/colors.hpp"