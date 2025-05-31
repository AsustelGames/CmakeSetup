#include "Includer.h"

int main()
{
    SDL_Window* Window = SDL_CreateWindow("SDLProjectTemplate - Window", 640, 480, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, NULL);
    bool ShouldWindowClose = false;

    ImGui::CreateContext();
    ImGuiIO IO = ImGui::GetIO(); (void)IO;

    ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer);
    ImGui_ImplSDLRenderer3_Init(Renderer);
    
    while (!ShouldWindowClose)
    {
        SDL_Event Event;
        
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL3_ProcessEvent(&Event);
            if (Event.type == SDL_EVENT_QUIT)
            {
                ShouldWindowClose = true;
            }
        }

        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test", NULL);
        if (ImGui::Button("Click me", { 100, 100 }))
        {
            std::cout << "you've clicked on me!" << '\n';
        }
        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 255);
        SDL_RenderClear(Renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);
        SDL_RenderPresent(Renderer);
    }
    std::cout << "hello" << '\n';

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}