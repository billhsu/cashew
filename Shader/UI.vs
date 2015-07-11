// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

out vec2 uv_vs;
out vec4 color_vs;

void main() {
    gl_Position =  projection * modelView * vec4(position, 0.0, 1.0);
    uv_vs = uv;
    color_vs = color;
}