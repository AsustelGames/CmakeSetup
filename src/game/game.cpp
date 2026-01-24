#include "game.hpp"


Game::Game(SDL_Window* Window_, SDL_GLContext GL_, SDL_Event Event_, double DT_, bool *Close_) : Window(Window_),
GL(GL_), Event(Event_), DT(DT_), Close(Close_)
{
   
}

void Game::Update()
{
   SDL_GetWindowSizeInPixels(Window, &WindowSize.x, &WindowSize.y);
}

void Game::Render()
{
   // add assimp
   // update TextureManager
   // add the rotating grass block
   // add aiso
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
   std::cout << "Window Closed" << '\n';
}

Game::~Game()
{
   
}