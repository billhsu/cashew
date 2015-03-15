// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform mat4 modelView;
uniform mat4 projection;

layout (location = 0) in vec3 position;

void main() {
    gl_Position =  modelView * vec4(position, 1.0);
}