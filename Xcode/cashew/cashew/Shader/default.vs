#version 330 core

uniform mat4 MVP;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 color_vs;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    color_vs = vec4(color, 1.0);
}