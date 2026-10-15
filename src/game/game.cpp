#include "game.hpp"


/// Example code you can safely delete
double I = 0;
uint32_t Pixels[100*100];
SDL_Texture* Texture = nullptr;
/// Example code you can safely delete


void Game::Init(int argc, char* argv[])
{
   /// Example code you can safely delete
   Texture = SDL_CreateTexture(Game::Renderer.SDL, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 100, 100);
   std::fill_n(Pixels, 100 * 100, 0xFF0000FF); // Fill with colored pixels
   SDL_UpdateTexture(Texture, nullptr, Pixels, 100 * sizeof(uint32_t));
   /// Example code you can safely delete

   std::cout << "argc: " <<argc << ", argv: " << argv[1] << '\n';
}

void Game::Update()
{
   SDL_GetWindowSize(Window, &Game::CurrentWindowLogicalSize.x, &Game::CurrentWindowLogicalSize.y); // Actual window size, used for mostly everything
   SDL_GetWindowSizeInPixels(Window, &Game::CurrentWindowPixelSize.x, &Game::CurrentWindowPixelSize.y); // HIDPI window size (scaled up), used for pixel perfect rendering and some opengl stuff
   std::cout << "bruh" << '\n';
}

void Game::Render()
{
   /// Example code you can safely delete
   SDL_FRect Rect = {Tool::GetXInPercent(Game::CurrentWindowLogicalSize.x, 50) - 100, Tool::GetXInPercent(Game::CurrentWindowLogicalSize.y, 50) - 100, 200, 200};
   SDL_FPoint Point = {100.0f, 100.0f};
   I += 75 * *DT; // DT in action
   //std::cout << "FPS: " << 1.0 / DT << '\n'; // Print FPS
   SDL_RenderTextureRotated(Game::Renderer.SDL, Texture, nullptr, &Rect, I, &Point, SDL_FLIP_NONE);
   /// Example code you can safely delete
}

void Game::RenderGui()
{
   /// Example code you can safely delete
   ImGui::Begin("Test", nullptr);
   ImGui::Text("FPS: %.1f", 1.0 / *DT);
   if (ImGui::Button("Click me", { 100, 100 }))
   {
      std::cout << "you've clicked on me!" << '\n';
   }
   ImGui::End();

   std::cout << "you've clicked on me!" << '\n';
   /// Example code you can safely delete
}

void Game::ShouldClose() // Runs after you press the x on the window
{
   if (CloseWindow) {*CloseWindow = true;} // If pointer valid Close = true
}

void Game::AfterClosed() // Runs after the window is destroyed
{
   std::cout << "bro" << '\n';
}

void Game::AfterDestroyed() // Runs after everything is destroyed
{
   
}
