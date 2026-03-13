#include "mainWindow.hpp"


int main()
{
    #ifdef DEBUG_BUILD
        std::cout << "(INFO) -> This is a debug build" << '\n';
    #endif
    
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;
    SDL_GLContext GL = nullptr;
    
    #ifdef USE_OPENGL
        std::cout << "(INFO) -> Using OpenGL" << '\n';
        if (!InitWindow("CmakeSetup - Window", Window, true)) {SDL_Quit(); return 1;}
        if (!InitOpenGL(Window, GL)) {SDL_DestroyWindow(Window); SDL_Quit(); return 1;}
        std::cout << "(INFO) -> OpenGL 4.6 Loaded" << '\n';
    #else
        std::cout << "(INFO) -> Using SDL_Renderer" << '\n';
        if (!InitWindow("CmakeSetup - Window", Window, false)) {SDL_Quit(); return 1;}
        if (!InitSDLRenderer(Window, Renderer)) {SDL_DestroyWindow(Window); SDL_Quit(); return 1;}
        std::cout << "(INFO) -> SDL_Renderer Loaded" << '\n';
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
    if (!MainGame.Title.empty()) {SDL_SetWindowTitle(Window, MainGame.Title.c_str());}
    else {MainGame.Title = SDL_GetWindowTitle(Window);}
    
    ImGui::CreateContext();
    ImGuiIO& IO = ImGui::GetIO(); (void)IO;
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
        
        // Calculate DeltaTime
        Uint64 CurrentFrame = SDL_GetPerformanceCounter();
        DeltaTime = double(CurrentFrame - LastFrame) / SDL_GetPerformanceFrequency();
        LastFrame = CurrentFrame;
        
        ImGui_ImplSDL3_NewFrame();
        #ifdef USE_OPENGL
            ImGui_ImplOpenGL3_NewFrame();
        #else
            ImGui_ImplSDLRenderer3_NewFrame();
        #endif
        ImGui::NewFrame();
        
        #ifdef USE_OPENGL
            glViewport(0, 0, WindowLogicalSize.x, WindowLogicalSize.y);
            
            // Fill window with color
            Tool::glClearColor(MainGame.BackgroundColor);
            glClear(GL_COLOR_BUFFER_BIT);
        #else
            // Fill window with color
            Tool::SDL_SetRenderDrawColor(Renderer, MainGame.BackgroundColor);
            SDL_RenderClear(Renderer);
        #endif
        
        //-- Render Imgui --//
        MainGame.RenderGui();
        ImGui::Render();
        
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
    std::cout << "(INFO) -> '" << MainGame.Title << "' window closed successfully" << '\n';
    
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
    
    std::cout << "(INFO) -> '" << MainGame.Title << "' window destroyed successfully" << '\n';
    
    return 0;
}

static bool InitWindow(const std::string& Title, SDL_Window*& Window, bool OpenGL)
{
    if (OpenGL)
    {
        Window = SDL_CreateWindow((Title + " (OpenGL)").c_str(), 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    }
    else
    {
        Window = SDL_CreateWindow((Title + " (SDL_Renderer)").c_str(), 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    }
    
    if (!Window)
    {
        std::cerr << "(FATAL ERROR) -> Failed to create window: " << SDL_GetError() << '\n';
        return false;
    }
    
    return true;
}

static bool InitSDLRenderer(SDL_Window* Window, SDL_Renderer*& Renderer)
{
    Renderer = SDL_CreateRenderer(Window, nullptr);
    if (!Renderer)
    {
        std::cerr << "(FATAL ERROR) -> Failed to create SDL_Renderer: " << SDL_GetError() << '\n';
        return false;
    }
    
    if (SDL_SetRenderVSync(Renderer, 1) < 0) // Enable VSync
    {
        std::cerr << "(WARNING) -> Failed to enable VSync: " << SDL_GetError() << '\n';
    }
    
    return true;
}

static bool InitOpenGL(SDL_Window* Window, SDL_GLContext& GL)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    GL = SDL_GL_CreateContext(Window);
    if (!GL)
    {
        std::cerr << "(FATAL ERROR) -> Failed to create OpenGL context: " << SDL_GetError() << '\n';
        return false;
    }
    
    if (SDL_GL_SetSwapInterval(1) < 0) // Enable VSync
    {
        std::cerr << "(WARNING) -> Failed to enable VSync: " << SDL_GetError() << '\n';
    }
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "(FATAL ERROR) -> Failed to initialize glad" << '\n';
        SDL_GL_DestroyContext(GL);
        return false;
    }
    SDL_GL_MakeCurrent(Window, GL);
    enableReportGlErrors();
    
    return true;
}