/*
#pragma once


#include <iostream>
#include <vector>
#include <string>

#include "SDL3/SDL.h"
#include "stb_image.h"


class ImageManager
{
private:
   SDL_Renderer *Renderer;
   
   struct IM_SDL_Texture
   {
      std::string Name;
      SDL_Texture* Texture;
      
      IM_Texture(std::string Name_, SDL_Texture* Texture_) : Name(Name_), Texture(Texture_) {}
   };
   
   std::vector<IM_SDL_Texture> SDLTextures;
   
public:
   ImageManager(SDL_Renderer *Renderer_);
   ~ImageManager();
   
   SDL_Texture *LoadImageForSDLRenderer(std::string Name, const std::string &FilePath);
};*/