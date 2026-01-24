#include "textureManager.hpp"


TextureManager::TextureManager(SDL_Renderer *Renderer_) : Renderer(Renderer_) {}
TextureManager::~TextureManager()
{
   for (auto &T : Textures)
   {
      if (T.Texture) {SDL_DestroyTexture(T.Texture);}
   }
   Textures.clear();
}

SDL_Texture *TextureManager::LoadTexture(const std::string Name, const std::string &FilePath)
{
   int Width = 0; int Height = 0; int Channels = 0;
   
   
   if (Name.empty()) { std::cerr << "TextureManager/LoadTexture(): Error invalid name: " << '\n'; return nullptr;}
   for (int I = 0; I < Textures.size(); I++)
   {
      if (Textures[I].Name == Name) {std::cerr << "TextureManager/LoadTexture(): Error texture with the same name already exists: " << Name << '\n'; return nullptr;}
   }
   
   stbi_uc *PixelData = stbi_load(FilePath.c_str(), &Width, &Height, &Channels, 4);
   if (!PixelData) {std::cerr << "TextureManager/LoadTexture(): Error invalid filepath: " << FilePath << '\n'; return nullptr;}
   
   SDL_Surface *Surface = SDL_CreateSurfaceFrom(Width, Height, SDL_PIXELFORMAT_RGBA32, PixelData, Width * 4);
   if (!Surface) {std::cerr << "TextureManager/LoadTexture(): Error failed to create Surface" << '\n'; stbi_image_free(PixelData); return nullptr;}
   
   SDL_Texture *Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
   if (!Texture) {std::cerr << "TextureManager/LoadTexture(): Error failed to create Texture" << '\n'; stbi_image_free(PixelData); return nullptr;}
   
   Textures.push_back({Name, Texture});
   SDL_SetTextureScaleMode(Texture, SDL_SCALEMODE_NEAREST);
   
   
   SDL_DestroySurface(Surface);
   stbi_image_free(PixelData);
   
   return Texture;
}