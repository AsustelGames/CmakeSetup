#include "MainWindow.hpp"


int main()
{
    SDL_Window* Window = SDL_CreateWindow("SDLProjectTemplate - Window", 640, 480, SDL_WINDOW_RESIZABLE);
    SDL_SetWindowMinimumSize(Window, 640, 480);
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, NULL);
    
    SDL_Event Event;
    
    SDL_SetRenderVSync(Renderer, 1);
    
    bool ShouldWindowClose = false;
    
    // Calculate DeltaTime // 1.0 / DeltaTime = FPS
    Uint64 LastFrame = SDL_GetPerformanceCounter();
    double DeltaTime = 0.0;
    
    Game MainGame(Window, Renderer, Event, DeltaTime, &ShouldWindowClose);
    
    ImGui::CreateContext();
    ImGuiIO IO = ImGui::GetIO(); (void)IO;

    ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer);
    ImGui_ImplSDLRenderer3_Init(Renderer);
    
    while (!ShouldWindowClose)
    {
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL3_ProcessEvent(&Event);
            if (Event.type == SDL_EVENT_QUIT)
            {
                MainGame.ShouldClose();
            }
        }
        
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        
        // Render Imgui //
        MainGame.RenderGui();

        ImGui::Render();
        COL_SetRenderDrawColor(Renderer, MainGame.BackgroundColor);
        
        SDL_RenderClear(Renderer);
        
        // Calculate DeltaTime
        Uint64 CurrentFrame = SDL_GetPerformanceCounter();
        DeltaTime = double(CurrentFrame - LastFrame) / SDL_GetPerformanceFrequency();
        LastFrame = CurrentFrame;
        
        // Render/Update //
        MainGame.Update();
        MainGame.Render();
        
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);
        SDL_RenderPresent(Renderer);
    } 
    MainGame.AfterClose();
    
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    
    MainGame.~Game();
    
    return 0;
}