#include "game.hpp"


Game::Game(SDL_Window* Window_, SDL_Renderer* R_,
SDL_GLContext GL_, SDL_Event& Event_, double& DT_,
bool *Close_) : Window(Window_), R(R_), GL(GL_), 
Event(Event_), DT(DT_), Close(Close_)
{
   /// Example code you can safely delete
   std::fill_n(Pixels, 100 * 100, 0xFF0000FF); // Fill with colored pixels
   SDL_UpdateTexture(Texture, nullptr, Pixels, 100 * sizeof(uint32_t));
   /// Example code you can safely delete
}

void Game::Update()
{
   SDL_GetWindowSize(Window, &WindowLogicalSize.x, &WindowLogicalSize.y); // Actual window size, used for mostly everything
   SDL_GetWindowSizeInPixels(Window, &WindowPixelSize.x, &WindowPixelSize.y); // HIDPI window size (scaled up), used for pixel perfect rendering and some opengl stuff
}

void Game::Render()
{
   /// Example code you can safely delete
   SDL_FRect Rect = {Tool_GetXInPercent(WindowLogicalSize.x, 50) - 100, Tool_GetXInPercent(WindowLogicalSize.y, 50) - 100, 200, 200};
   SDL_FPoint Point = {100.0f, 100.0f};
   I += 75 * DT; // DT in action
   //std::cout << "FPS: " << 1.0 / DT << '\n'; // Print FPS
   SDL_RenderTextureRotated(R, Texture, nullptr, &Rect, I, &Point, SDL_FLIP_NONE);
   /// Example code you can safely delete
}

void Game::RenderGui()
{
   /// Example code you can safely delete
   ImGui::Begin("Test", NULL);
   if (ImGui::Button("Click me", { 100, 100 }))
   {
      std::cout << "you've clicked on me!" << '\n';
   }
   ImGui::End();
   /// Example code you can safely delete
}

void Game::ShouldClose() // Runs after you press the x on the window
{
   if (Close) {*Close = true;} // If pointer valid Close = true
}

void Game::AfterClose() // Runs after the window is destroyed
{
   
}

Game::~Game() // Runs after everything is destroyed
{
   
}