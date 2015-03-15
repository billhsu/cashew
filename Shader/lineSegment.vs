// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vPosition
out vec4 color_vs;
void main() {
    vPosition =  modelView * vec4(position, 1.0);
    color_vs = color;
}