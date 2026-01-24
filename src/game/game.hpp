#pragma once


#include "SDL3/SDL.h"
#include "miniaudio.h"
#include "stb_image.h"
#include "stb_truetype.h"
#include "imgui.h"
#include "enet.h"
#include "SDL3_net/SDL_net.h"
#include "fastnoiselite.h"
#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

#include "rendering/colors.hpp"
//#include "Rendering/TextureManager/TextureManager.hpp"


class Game
{
private:
   SDL_Window* Window;
   SDL_GLContext GL;
   SDL_Event Event;
   glm::ivec2 WindowSize;
   bool *Close;
   double DT;
   
   //TextureManager TM;
   //SDL_Texture* Square = TM.LoadTexture("grass", ASSETS_PATH"test.png");
   
   
public:
   Color BackgroundColor = GRAY;
   
   
   Game(SDL_Window* Window_, SDL_GLContext GL_, SDL_Event Event_, double DT_, bool *Close_);
   ~Game();
   
   void Update();
   void Render();
   void RenderGui();
   void ShouldClose();
   void AfterClose();
};