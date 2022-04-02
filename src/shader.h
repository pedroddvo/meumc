#if !defined(SHADER_H)
#define SHADER_H

#define SHADER_PATH(file) \
  "C:/Users/Poliveira/Desktop/DEV/C/meumc/src/shader/" file

typedef struct {
  int id;
} Shader_Program;

void
init_shader_program(Shader_Program* program, const char* vs_path, const char* fs_path);

#endif // SHADER_H
