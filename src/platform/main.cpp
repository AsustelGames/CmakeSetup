#include "main.hpp"

void error_callback(int error, const char* description)
{
   fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char *argv[]) {
   if (!glfwInit()) { std::cerr << "CmakeSetup: GLFW initialization failed" << '\n'; glfwTerminate(); return 1; }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(0, 480, "window", NULL, NULL);
   if (!window) { std::cerr << "CmakeSetup: GLFW window initialization failed" << '\n'; glfwTerminate(); return 1; }

   glfwSetWindowCloseCallback(window, onCloseWindowRequest);
   glfwSetErrorCallback(error_callback);

   glfwMakeContextCurrent(window);

   if (!gladLoadGL(glfwGetProcAddress)) { std::cout << "gl" << '\n'; }

   glClearColor(0.5, 0.3, 0.6, 1.0);

   while (!glfwWindowShouldClose(window)) {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      glViewport(0, 0, width, height);
      glClear(GL_COLOR_BUFFER_BIT);
      

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);

   return 0;
}

void onCloseWindowRequest(GLFWwindow* window) {
   glfwSetWindowShouldClose(window, GLFW_TRUE);
}
