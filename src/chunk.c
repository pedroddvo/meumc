#include "chunk.h"
#include "shader.h"
#include <string.h>

void
init_chunk(Chunk* chunk) {
  memset(chunk->blocks, BLOCK_AIR, CHUNK_SIZE);
}

const float Block_Vertices[] = {
  // front
  -1.0f,  1.0f, 0.0f,
  -1.0f, -1.0f, 0.0f,
   1.0f,  1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,

   // right
   1.0f,  1.0f, 1.0f,
   1.0f, -1.0f, 1.0f,

   // back
  -1.0f,  1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,

  // left/up/down reserved for ebo
  // due to all vertices being reused
};

const GLuint Block_Indices[] = {
  // front
  0, 1, 2,
  1, 2, 3,

  // right
  2, 3, 4,
  3, 4, 5,

  // back
  4, 5, 6,
  5, 6, 7,

  // left
  6, 7, 0,
  7, 0, 1,

  // up
  0, 2, 4,
  4, 6, 0,

  // down
  1, 3, 5,
  5, 7, 1,
};

static GLuint Block_VAO, Block_VBO, Block_EBO;
static Shader_Program Block_Programs[BLOCK_COUNT];

void
init_chunk_arrays() {
  glGenVertexArrays(1, &Block_VAO);
  glGenBuffers(1, &Block_VBO);
  glGenBuffers(1, &Block_EBO);

  glBindVertexArray(Block_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, Block_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Block_Vertices), Block_Vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Block_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Block_Indices), Block_Indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  Shader_Program program;
  init_shader_program(&program, SHADER_PATH("block.vs"), SHADER_PATH("block.fs"));
  Block_Programs[BLOCK_WHITE] = program;
}

void
render_chunk(Chunk* chunk, Camera* camera) {
  camera_perspective_gen_uniforms(camera, &Block_Programs[BLOCK_WHITE]);

  // generate model matrix
  mat4 model;
  glm_mat4_identity(model);
  GLuint model_location = glGetUniformLocation(Block_Programs[BLOCK_WHITE].id, "model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, model);

  glUseProgram(Block_Programs[BLOCK_WHITE].id);
  glBindVertexArray(Block_VAO);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}