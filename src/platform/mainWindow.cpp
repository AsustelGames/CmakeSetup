#include "mainWindow.hpp"


int main()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Window* Window = SDL_CreateWindow("CmakeSetup - Window", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    SDL_GLContext GL = SDL_GL_CreateContext(Window);
    SDL_SetWindowMinimumSize(Window, 640, 480);
    
    SDL_GL_SetSwapInterval(1);
    
    SDL_Event Event;
    glm::ivec2 WindowSize;
    bool ShouldWindowClose = false;
    
    Uint64 LastFrame = SDL_GetPerformanceCounter();
    double DeltaTime = 0.0; // Calculate DeltaTime // 1.0 / DeltaTime = FPS
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize glad" << '\n';
        ImGui_ImplOpenGL3_Shutdown(); ImGui_ImplSDL3_Shutdown(); ImGui::DestroyContext();
        SDL_GL_DestroyContext(GL); SDL_DestroyWindow(Window); SDL_Quit();
        return 1;
    }
        
    enableReportGlErrors();
    
    Game MainGame(Window, GL, Event, DeltaTime, &ShouldWindowClose);
    SDL_SetWindowTitle(Window, MainGame.Title.c_str());
    
    ImGui::CreateContext();
    ImGuiIO IO = ImGui::GetIO(); (void)IO;

    ImGui_ImplSDL3_InitForOpenGL(Window, GL);
    ImGui_ImplOpenGL3_Init();
    
    while (!ShouldWindowClose)
    {
        SDL_GetWindowSizeInPixels(Window, &WindowSize.x, &WindowSize.y);
        
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL3_ProcessEvent(&Event);
            if (Event.type == SDL_EVENT_QUIT)
            {
                MainGame.ShouldClose();
            }
        }
        
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        //-- Render Imgui --//
        MainGame.RenderGui();
        
        ImGui::Render();
        SDL_GL_MakeCurrent(Window, GL);
        glViewport(0, 0, WindowSize.x, WindowSize.y);
        
        // Fill window with color
        Tool_glClearColor(MainGame.BackgroundColor);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Calculate DeltaTime
        Uint64 CurrentFrame = SDL_GetPerformanceCounter();
        DeltaTime = double(CurrentFrame - LastFrame) / SDL_GetPerformanceFrequency();
        LastFrame = CurrentFrame;
        
        //-- Render & Update --//
        MainGame.Update();
        MainGame.Render();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(Window);
    } 
    MainGame.AfterClose();
    std::cout << MainGame.Title << " Window Closed" << '\n';
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(GL);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    
    MainGame.~Game();
    std::cout << MainGame.Title << " Destroyed" << '\n';
    
    return 0;
}