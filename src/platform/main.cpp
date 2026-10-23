#include "main.hpp"

void error_callback(int error, const char* description)
{
   fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char *argv[]) {
   glfwSetErrorCallback(error_callback);

   if (!glfwInit()) {
      std::cerr << "CmakeSetup: GLFW initialization failed" << '\n';
      return 1;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   float windowScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
   GLFWwindow* window = glfwCreateWindow((int)(windowScale * 640), (int)(windowScale * 480), "window", NULL, NULL);
   if (!window) {
      std::cerr << "CmakeSetup: GLFW window initialization failed" << '\n';
      glfwTerminate();
      return 1;
   }
   glfwMakeContextCurrent(window);

   if (!gladLoadGL(glfwGetProcAddress)) {
      std::cout << "CmakeSetup: glad failed to load OpenGL" << '\n';
      glfwDestroyWindow(window);
      glfwTerminate();
      return 1;
   }
   glfwSwapInterval(1);

   // IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

   ImGuiStyle& style = ImGui::GetStyle();
   ImGui::StyleColorsDark();
   //style.FontSizeBase = 16.0f;           // Default to 13.0f when unspecified, which allows crisp legacy font for non-4K screens.
   style.FrameRounding = 3.0f;
   style.GrabRounding = 3.0f;

   // Setup scaling
   style.ScaleAllSizes(windowScale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
   style.FontScaleDpi = windowScale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init();

   glClearColor(0.5, 0.3, 0.6, 1.0);

   glfwSetWindowCloseCallback(window, onCloseWindowRequest);

   while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      ImGui::ShowDemoWindow(nullptr);

      ImGui::Render();
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}

void onCloseWindowRequest(GLFWwindow* window) {
   glfwSetWindowShouldClose(window, GLFW_TRUE);
}
