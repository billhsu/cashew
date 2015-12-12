// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core
uniform vec3 color;
out vec4 outColor;

void main() {
    outColor = vec4(color, 1.0);
}
