#include "Game.hpp"


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
   // update Sdlprojecttemplate non opengl edition
   // x add gl error reporting
   // add the rotating grass block
   // add aiso
   // add invert color
   // x set correct version of gl in main
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