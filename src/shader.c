#include "shader.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

static GLuint
load_shader(const char* path, GLenum kind) {
  FILE* file = fopen(path, "rb");
  assert_fatalf(file != NULL, "Could not read shader file from path %s!", path_file_name(path));

  fseek(file, 0, SEEK_END);
  int file_len = ftell(file);
  char* file_buf = malloc(file_len + 1);
  assert_fatalf(file_buf != NULL, "Failed to allocate file_buf!", NULL);
  fseek(file, 0, SEEK_SET);

  fread(file_buf, 1, file_len, file);
  file_buf[file_len] = '\0'; // just in case

  GLuint id = glCreateShader(kind);
  glShaderSource(id, 1, &file_buf, NULL);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetShaderInfoLog(id, 512, NULL, info_log);
    info_log[511] = '\0';
    log_fatalf("Error compiling shader %s:\n%s", path_file_name(path), info_log);
  }

  free(file_buf);
  fclose(file);

  log_infof("Successfully compiled shader %s", path_file_name(path));

  return id;
}


void
init_shader_program(Shader_Program* program, const char* vs_path, const char* fs_path) {
  GLuint vs_id = load_shader(vs_path, GL_VERTEX_SHADER);
  GLuint fs_id = load_shader(fs_path, GL_FRAGMENT_SHADER);

  program->id = glCreateProgram();
  glAttachShader(program->id, vs_id);
  glAttachShader(program->id, fs_id);
  glLinkProgram(program->id);

  int success;
  glGetProgramiv(program->id, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program->id, 512, NULL, info_log);
    info_log[511] = '\0';
    log_fatalf("Error linking shaders %s and %s:\n%s", path_file_name(vs_path), path_file_name(fs_path), info_log);
  }

  log_infof("Successfully linked shaders %s and %s", path_file_name(vs_path), path_file_name(fs_path));

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);
}