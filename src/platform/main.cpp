#include "main.hpp"


int main(int argc, char* argv[])
{
   std::cout << '\n' << "(INFO) -> Launching" << '\n';

   #ifdef LOGGING_ENABLED
      std::cout << "(INFO) -> Logging enabled" << '\n';
      std::cout << "(INFO) -> Logging path: " << LOGGING_PATH << '\n';
   #else
      std::cout << "(INFO) -> Logging disabled" << '\n';
   #endif

   #ifdef DEBUG_BUILD
      std::cout << "(INFO) -> This is a debug build" << '\n';
   #endif
    

   //-- Renderer Setup --//
   SDL_Window* Window = nullptr;
   Game::GraphicsRenderer Renderer;

   #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
      std::cout << "(INFO) -> Using OpenGL 4.6" << '\n';
      if (!InitWindow("CmakeSetup - Window", Window)) {SDL_Quit(); return 1;}
      if (!InitOpenGL(Window, Renderer.GL)) {SDL_DestroyWindow(Window); SDL_Quit(); return 1;}
      std::cout << "(INFO) -> OpenGL 4.6 loaded" << '\n';
   #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
      // todo
   #elif CURRENT_GRAPHICS_RENDERER == USING_SDL_RENDERING
      std::cout << "(INFO) -> Using SDL_Renderer" << '\n';
      if (!InitWindow("CmakeSetup - Window", Window)) {SDL_Quit(); return 1;}
      if (!InitSDLRenderer(Window, Renderer.SDL)) {SDL_DestroyWindow(Window); SDL_Quit(); return 1;}
      std::cout << "(INFO) -> SDL_Renderer loaded" << '\n';
   #else
      std::cout << "(WARNING) -> Unknown renderer selected" << '\n';
      std::cout << "(INFO) -> Using SDL_Renderer instead" << '\n';
      if (!InitWindow("CmakeSetup - Window", Window)) {SDL_Quit(); return 1;}
      if (!InitSDLRenderer(Window, Renderer.SDL)) {SDL_DestroyWindow(Window); SDL_Quit(); return 1;}
      std::cout << "(INFO) -> SDL_Renderer loaded" << '\n';
   #endif
    
    
   SDL_SetWindowMinimumSize(Window, 640, 480);

   SDL_Event Event;
   glm::ivec2 WindowLogicalSize;
   glm::ivec2 WindowPixelSize;
   glm::vec2 DisplayScale;
   
   bool ShouldWindowClose = false;
    
   Uint64 LastFrame = SDL_GetPerformanceCounter();
   double DeltaTime = 0.0; // Calculate DeltaTime // 1.0 / DeltaTime = FPS
    
   Game::Window = Window;
   Game::Renderer = Renderer;
   Game::Event = &Event;
   Game::DT = &DeltaTime;
   Game::CloseWindow = &ShouldWindowClose;
   Game::Init(argc, argv);
    
   if (!Game::Title.empty()) {SDL_SetWindowTitle(Window, Game::Title.c_str());}
   else {Game::Title = SDL_GetWindowTitle(Window);}
    
   //-- Imgui Setup --//
   ImGui::CreateContext();
   ImGuiIO& IO = ImGui::GetIO(); (void)IO;
   #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
      ImGui_ImplSDL3_InitForOpenGL(Window, Renderer.GL);
      ImGui_ImplOpenGL3_Init();
   #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
      // todo
   #else
      ImGui_ImplSDL3_InitForSDLRenderer(Window, Renderer.SDL);
      ImGui_ImplSDLRenderer3_Init(Renderer.SDL);
   #endif


   //-- Main Loop --//
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
            Game::ShouldClose();
         }
      }
       
      // Calculate DeltaTime
      Uint64 CurrentFrame = SDL_GetPerformanceCounter();
      DeltaTime = double(CurrentFrame - LastFrame) / SDL_GetPerformanceFrequency();
      LastFrame = CurrentFrame;
       
      ImGui_ImplSDL3_NewFrame();
      #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
          ImGui_ImplOpenGL3_NewFrame();
      #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
          // todo
      #else
          ImGui_ImplSDLRenderer3_NewFrame();
      #endif
      ImGui::NewFrame();
        
      // Fill window with color
      #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
          glViewport(0, 0, WindowLogicalSize.x, WindowLogicalSize.y);
           
          Tool::glClearColor(Game::BackgroundColor);
          glClear(GL_COLOR_BUFFER_BIT);
      #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
          // todo
      #else
          Tool::SDL_SetRenderDrawColor(Renderer.SDL, Game::BackgroundColor);
          SDL_RenderClear(Renderer.SDL);
      #endif
        
      //-- Render Imgui --//
      Game::RenderGui();
      ImGui::Render();
        
      //-- Render & Update --//
      Game::Update();
      Game::Render();
        
      #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
          SDL_GL_SwapWindow(Window);
      #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
          // todo
      #else
          SDL_SetRenderScale(Renderer.SDL, DisplayScale.x, DisplayScale.y); // This is to fix HIDPI issue with imgui while using the SDL_Renderer
          ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Renderer.SDL);
          SDL_RenderPresent(Renderer.SDL);
      #endif
   }
   //-- End Of Main Loop --//
   Game::AfterClosed();
   std::cout << "(INFO) -> '" << Game::Title << "' window closed successfully" << '\n';
    
   ImGui_ImplSDL3_Shutdown();
   #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
       ImGui_ImplOpenGL3_Shutdown();
       ImGui::DestroyContext();
       SDL_GL_DestroyContext(Renderer.GL);
   #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
       // todo
   #else
       ImGui_ImplSDLRenderer3_Shutdown();
       ImGui::DestroyContext();
       SDL_DestroyRenderer(Renderer.SDL);
   #endif
    
   SDL_DestroyWindow(Window);
   SDL_Quit();
    
   std::cout << "(INFO) -> '" << Game::Title << "' window destroyed successfully" << '\n';
    
   return 0;
}



static bool InitWindow(const std::string& Title, SDL_Window*& Window)
{
   #if CURRENT_GRAPHICS_RENDERER == USING_OPENGL_RENDERING
       Window = SDL_CreateWindow((Title + " (OpenGL)").c_str(), 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
   #elif CURRENT_GRAPHICS_RENDERER == USING_VULKAN_RENDERING
      // todo
   #else
       Window = SDL_CreateWindow((Title + " (SDL_Renderer)").c_str(), 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
   #endif
   
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
   
   SDL_GL_MakeCurrent(Window, GL);

   if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
   {
       std::cerr << "(FATAL ERROR) -> Failed to initialize glad" << '\n';
       SDL_GL_DestroyContext(GL);
       return false;
   }
   enableReportGlErrors();
   
   return true;
}

