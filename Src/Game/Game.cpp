#include "Game.hpp"


Game::Game(SDL_Window* Window_, SDL_Renderer* Renderer_, SDL_Event Event, double DT_, bool *Close_) : Window(Window_),
Renderer(Renderer_), DT(DT_), Close(Close_), TM(Renderer)
{
   
}


double Angle = 0;


void Game::Update()
{
   Angle++;
}

void Game::Render()
{
   COL_SetRenderDrawColor(Renderer, BackgroundColor);
   SDL_SetRenderTarget(Renderer, Square);
   COL_SetRenderDrawColor(Renderer, ORANGE);
   SDL_SetRenderTarget(Renderer, nullptr);
   
   int WindowWidth, WindowHeight;
   
   SDL_GetWindowSizeInPixels(Window, &WindowWidth, &WindowHeight);
   SDL_FRect Rect = {150, 50, float(WindowHeight) - 120, float(WindowHeight) - 120};
   SDL_RenderTextureRotated(Renderer, Square, nullptr, &Rect, Angle, nullptr, SDL_FLIP_NONE);   
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
   if (Square) {SDL_DestroyTexture(Square); Square = nullptr;}
}


