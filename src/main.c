#define GLFW_INCLUDE_NONE
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "state.h"
#include "shader.h"

void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main() {
  if (!glfwInit()) {
    printf("GLFW Initialization failed!\n");
    return -1;
  }
  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MeuMC", NULL, NULL);
  if (!window) {
    printf("GLFW Window Initialization failed!\n");
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to initialize OpenGL context\n");
    return -1;
  }

  int glob_width = WINDOW_WIDTH, glob_height = WINDOW_HEIGHT;
  glfwGetFramebufferSize(window, &glob_width, &glob_height);
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, game_state_key_callback);

  Game_State state;
  game_state_setup(&state);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    state.time = glfwGetTime();
    game_state_render(&state);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}