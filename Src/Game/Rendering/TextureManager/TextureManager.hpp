#pragma once


#include <iostream>
#include <vector>
#include <string>

#include "SDL3/SDL.h"
#include "stb/stb_image.h"


class TextureManager
{
private:
   SDL_Renderer *Renderer;
   
   struct TM_Texture
   {
      std::string Name;
      SDL_Texture* Texture;
      
      TM_Texture(std::string Name_, SDL_Texture* Texture_) : Name(Name_), Texture(Texture_) {}
   };
   
   std::vector<TM_Texture> Textures;
   
public:
   TextureManager(SDL_Renderer *Renderer_);
   ~TextureManager();
   
   SDL_Texture *LoadTexture(std::string Name, const std::string &FilePath);
};