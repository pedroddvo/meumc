#version 330 core

layout (location = 0) in vec3 v_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(v_pos.xy, v_pos.z * 2.0, 1.0);
}