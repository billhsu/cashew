#version 330 core

in vec4 color_vs;
out vec4 color;

void main() {
    color = color_vs;
}