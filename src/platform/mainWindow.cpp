#include "mainWindow.hpp"


int main()
{
    #ifdef USE_OPENGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        SDL_Window* Window = SDL_CreateWindow("CmakeSetup - Window", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
        SDL_GLContext GL = SDL_GL_CreateContext(Window);
        SDL_GL_SetSwapInterval(1);
        SDL_Renderer* Renderer = nullptr;
        std::cout << "Using OpenGL" << '\n';
        
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::cerr << "Failed to initialize glad" << '\n';
            ImGui_ImplOpenGL3_Shutdown(); ImGui_ImplSDL3_Shutdown(); ImGui::DestroyContext();
            SDL_GL_DestroyContext(GL); SDL_DestroyWindow(Window); SDL_Quit();
            return 1;
        }
        enableReportGlErrors();
    #else
        SDL_Window* Window = SDL_CreateWindow("CmakeSetup - Window", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
        SDL_GLContext GL = nullptr;
        SDL_Renderer* Renderer = SDL_CreateRenderer(Window, NULL);
        std::cout << "Using SDL_Renderer" << '\n';
    #endif
    
    SDL_SetWindowMinimumSize(Window, 640, 480);

    SDL_Event Event;
    glm::ivec2 WindowLogicalSize;
    glm::ivec2 WindowPixelSize;
    glm::vec2 DisplayScale;
    
    bool ShouldWindowClose = false;
    
    Uint64 LastFrame = SDL_GetPerformanceCounter();
    double DeltaTime = 0.0; // Calculate DeltaTime // 1.0 / DeltaTime = FPS
    
    Game MainGame(Window, Renderer, GL, Event, DeltaTime, &ShouldWindowClose);
    SDL_SetWindowTitle(Window, MainGame.Title.c_str());
    
    ImGui::CreateContext();
    ImGuiIO IO = ImGui::GetIO(); (void)IO;
    #ifdef USE_OPENGL
        ImGui_ImplSDL3_InitForOpenGL(Window, GL);
        ImGui_ImplOpenGL3_Init();
    #else
        ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer);
        ImGui_ImplSDLRenderer3_Init(Renderer);
    #endif

    while (!ShouldWindowClose)
    {
        SDL_GetWindowSize(Window, &WindowLogicalSize.x, &WindowLogicalSize.y);
        SDL_GetWindowSizeInPixels(Window, &WindowPixelSize.x, &WindowPixelSize.y);
        DisplayScale = {WindowPixelSize.x / (float)WindowLogicalSize.x, WindowPixelSize.y / (float)WindowLogicalSize.y};
        
        while (SDL_PollEvent(&Event))
        {
            ImGui_ImplSDL3_ProcessEvent(&Event);
            if (Event.type == SDL_EVENT_QUIT)
            {
                MainGame.ShouldClose();
            }
        }
        
        ImGui_ImplSDL3_NewFrame();
        #ifdef USE_OPENGL
            ImGui_ImplOpenGL3_NewFrame();
        #else
            ImGui_ImplSDLRenderer3_NewFrame();
        #endif
        ImGui::NewFrame();
        
        #ifdef USE_OPENGL
            SDL_GL_MakeCurrent(Window, GL);
            glViewport(0, 0, WindowLogicalSize.x, WindowLogicalSize.y);
            
            // Fill window with color
            Tool_glClearColor(MainGame.BackgroundColor);
            glClear(GL_COLOR_BUFFER_BIT);
        #else
            // Fill window with color
            Tool_SetRenderDrawColor(Renderer, MainGame.BackgroundColor);
            SDL_RenderClear(Renderer);
        #endif
        
        //-- Render Imgui --//
        MainGame.RenderGui();
        ImGui::Render();
        
        // Calculate DeltaTime
        Uint64 CurrentFrame = SDL_GetPerformanceCounter();
        DeltaTime = double(CurrentFrame - LastFrame) / SDL_GetPerformanceFrequency();
        LastFrame = CurrentFrame;
        
        //-- Render & Update --//
        MainGame.Update();
        MainGame.Render();
        
        #ifdef USE_OPENGL
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(Window);
        #else
            SDL_SetRenderScale(Renderer, DisplayScale.x, DisplayScale.y); // This is to fix HIDPI issue with imgui while using the SDL_Renderer
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer);
            SDL_RenderPresent(Renderer);
        #endif
    } 
    MainGame.AfterClose();
    std::cout << MainGame.Title << " Window Closed" << '\n';
    
    ImGui_ImplSDL3_Shutdown();
    #ifdef USE_OPENGL
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
        SDL_GL_DestroyContext(GL);
    #else
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui::DestroyContext();
        SDL_DestroyRenderer(Renderer);
    #endif
    
    SDL_DestroyWindow(Window);
    SDL_Quit();
    
    std::cout << MainGame.Title << " Destroyed" << '\n';
    
    return 0;
}