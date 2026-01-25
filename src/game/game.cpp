#include "game.hpp"


Game::Game(SDL_Window* Window_, SDL_GLContext GL_, SDL_Event Event_, double DT_, bool *Close_) : Window(Window_),
GL(GL_), Event(Event_), DT(DT_), Close(Close_)
{
   
}

void Game::Update()
{
   SDL_GetWindowSize(Window, &WindowLogicalSize.x, &WindowLogicalSize.y); // Actual window size, used for mostly everything
   SDL_GetWindowSizeInPixels(Window, &WindowPixelSize.x, &WindowPixelSize.y); // HIDPI window size (scaled up) , used for pixel perfect render and some opengl stuff
}

void Game::Render()
{
   // add assimp
   // update TextureManager
   // add the rotating grass block
   // add aiso
   // add more device detection in cmakelists.txt
   // set use opengl in cmakelists.txt
}

void Game::RenderGui()
{
   ImGui::Begin("Test", NULL);
   if (ImGui::Button("Click me", { 100, 100 }))
   {
      std::cout << "you've clicked on me!" << '\n';
   }
   ImGui::End();
}

void Game::ShouldClose()
{
   if (Close) {*Close = true;}
}

void Game::AfterClose()
{
   
}

Game::~Game()
{
   
}