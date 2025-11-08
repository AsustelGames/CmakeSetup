#pragma once


#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_mixer/SDL_mixer.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "enet/enet.h"
#include "FastNoiseLite.h"
#include "box2d/box2d.h"
#include "glm/glm.hpp"

#include <iostream>
#include <cstdint>


struct Color
{
   uint8_t r, g, b, a;
   
   bool operator==(const Color& Other) const
   {
      return r == Other.r && g == Other.g && b == Other.b && a == Other.a;
   }

   bool operator!=(const Color& Other) const
   {
      return r != Other.r || g != Other.g || b != Other.b || a != Other.a;
   }
};

inline std::ostream& operator<<(std::ostream& OS5, const Color& V5)
{
   OS5 << "(" << V5.r << ", " << V5.g << ", " << V5.b << ", " << V5.a <<  ")"; return OS5;
}


class Game
{
private:

   
public:
   SDL_Window* Window;
   SDL_Renderer* Renderer;
   double DT;
   bool *Close;
   
   
   SDL_Texture* Square = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
   
   Game(SDL_Window* Window_, SDL_Renderer* Renderer_, double DT_, bool *Close_);
   ~Game();
   
   void Update();
   void Render();
   void RenderGui();
   void ShouldClose();
   void AfterClose();
};