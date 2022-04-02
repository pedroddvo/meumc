#include "camera.h"
#include "common.h"
#include <glad/glad.h>
#include <string.h>

void
init_camera(Camera* camera) {
  camera->pitch = 0.0f;
  camera->yaw = -90.0f;
  memcpy(camera->position, (vec3){ 0.0f, 0.0f, 5.0f, }, VEC3_SIZE);
  memcpy(camera->front, (vec3){ 0.0f, 0.0f, -1.0f }, VEC3_SIZE);

  camera_update(camera);
}

void
camera_update(Camera* camera) {
  // calculate front vector
  vec3 front = {
    cosf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch)),
    sinf(glm_rad(camera->pitch)),
    sinf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch)),
  };
  glm_normalize(front);
  memcpy(camera->front, front, VEC3_SIZE);

  glm_cross(front, (vec3){ 0.0f, 1.0f, 0.0f }, camera->right);
  glm_cross(camera->right, front, camera->up);

  glm_normalize(camera->right);
  glm_normalize(camera->up);

  // recalculate view matrix
  vec3 dist;
  glm_vec3_add(camera->position, front, dist);
  glm_lookat(camera->position, dist, camera->up, camera->view);
}

void
camera_perspective_gen_uniforms(Camera* camera, Shader_Program* program) {
  GLint projection_id = glGetUniformLocation(program->id, "projection");
  GLint view_id = glGetUniformLocation(program->id, "view");

  mat4 projection;
  glm_perspective(glm_rad(90.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f, projection);

  glUniformMatrix4fv(projection_id, 1, GL_FALSE, (const GLfloat *)projection);
  glUniformMatrix4fv(view_id, 1, GL_FALSE, (const GLfloat *)camera->view);
}