// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 uv_vs;

void main() {
    gl_Position =  vec4(position, 1.0);
    uv_vs = uv;
}