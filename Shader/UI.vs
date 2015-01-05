// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

out vec4 color_vs;
out vec2 uv_vs;

void main() {
    gl_Position =  projection * modelView * vec4(position, 1.0);
    color_vs = color;
    uv_vs = uv;
}