// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D image0;
in vec2 vertexUV;

out vec4 color;
void main (void)
{
    color = texture(image0, vertexUV);
}