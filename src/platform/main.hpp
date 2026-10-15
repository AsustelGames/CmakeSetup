#pragma once


#include "SDL3/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
   #include "glad/glad.h"
   #include "backends/imgui_impl_opengl3.h"
#elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
   #include "SDL3/SDL_vulkan.h"
   #include "backends/imgui_impl_vulkan.h"
#elif CURRENT_GRAPHICS_RENDERER == USING_SDL_RENDERING
   #include "imgui_impl_sdlrenderer3.h"
#else
   #include "imgui_impl_sdlrenderer3.h"
#endif
#include "glm/glm.hpp"

#include <iostream>
#include <string>

#include "errorReportingOpenGL.hpp"

#include "../game/game.hpp"
#include "../game/tools/colors.hpp"


static bool InitWindow(const std::string& Title, SDL_Window*& Window);
static bool InitOpenGL(SDL_Window* Window, SDL_GLContext& GL);
//static bool InitVulkan(SDL_Window* Window, SDL_GLContext& GL);
static bool InitSDLRenderer(SDL_Window* Window, SDL_Renderer*& Renderer);
