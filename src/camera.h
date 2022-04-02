#if !defined(CAMERA_H)
#define CAMERA_H
#include "shader.h"
#include <cglm/cglm.h>

#define VEC3_SIZE sizeof(float) * 3

typedef struct {
  vec3 position;
  float yaw;
  float pitch;

  vec3 up;
  vec3 front;
  vec3 right;

  mat4 view;
} Camera;

static const vec3 WORLD_UP = { 0.0f, 1.0f, 0.0f };

void
init_camera(Camera* camera);

void
camera_update(Camera* camera);

// generates 'projection' and 'view' transforms for use in shader programs
void
camera_perspective_gen_uniforms(Camera* camera, Shader_Program* program);

#endif // CAMERA_H
