#if !defined(STATE_H)
#define STATE_H

#include "common.h"
#include "shader.h"
#include "chunk.h"
#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
  double time;
  Chunk chunk;

  Camera camera;
} Game_State;

void
game_state_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void
game_state_render(Game_State* state);

void
game_state_setup(Game_State* state);

#endif