#pragma once


#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "box2d/box2d.h"
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
#include <algorithm>

#include "tools/colors.hpp"
//#include "Rendering/TextureManager/TextureManager.hpp"


class Game
{
private:
   SDL_Window* Window;
   SDL_Renderer* R;
   SDL_GLContext GL;
   SDL_Event Event;
   glm::ivec2 WindowLogicalSize; // Actual window size, used for mostly everything
   glm::ivec2 WindowPixelSize; // HIDPI window size (scaled up) , used for pixel perfect render and some opengl stuff
   bool *Close; // Close the window
   double& DT; // DeltaTime
   
   //TextureManager TM;
   //SDL_Texture* Square = TM.LoadTexture("grass", ASSETS_PATH"test.png");
   
   
public:
   std::string Title = "Game";
   Color BackgroundColor = GRAY;
   
   
   Game(SDL_Window* Window_, SDL_Renderer* R_, SDL_GLContext GL_, SDL_Event Event_, double& DT_, bool *Close_);
   ~Game();
   
   void Update();
   void Render();
   void RenderGui();
   void ShouldClose();
   void AfterClose();
};