// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core
uniform sampler2D image0;
in vec2 uv_vs;
out vec4 color;

void main() {
    color = texture( image0, uv_vs );
}