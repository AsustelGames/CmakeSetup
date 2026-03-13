#pragma once


#include "SDL3/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#ifdef USE_OPENGL
   #include "glad/glad.h"
   #include "backends/imgui_impl_opengl3.h"
#else
   #include "imgui_impl_sdlrenderer3.h"
#endif
#include "glm/glm.hpp"

#include <iostream>
#include <string>

#include "errorReportingOpenGL.hpp"

#include "../game/game.hpp"
#include "../game/tools/colors.hpp"


static bool InitWindow(const std::string& Title, SDL_Window*& Window, bool OpenGL);
static bool InitSDLRenderer(SDL_Window* Window, SDL_Renderer*& Renderer);
static bool InitOpenGL(SDL_Window* Window, SDL_GLContext& GL);