#include "state.h"
#include "chunk.h"

void
game_state_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void
game_state_setup(Game_State* state) {
  init_chunk(&state->chunk);
  init_chunk_arrays();

  init_camera(&state->camera);
}

void
game_state_render(Game_State* state) {
  glClearColor(0.1f, 0.2f, 0.4f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  state->camera.position[0] += sinf(state->time) / 10.0f;
  state->camera.position[2] += cosf(state->time) / 10.0f;
  glm_lookat(state->camera.position, GLM_VEC3_ZERO, state->camera.up, state->camera.view);

  render_chunk(&state->chunk, &state->camera);
}