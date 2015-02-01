// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core
uniform sampler2D image0;
in vec2 uv_vs;
out vec4 color;

void main() {
    vec4 _color = texture( image0, uv_vs );
    color = vec4(_color.x,_color.x,_color.x,1);
}