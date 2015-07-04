// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core
uniform sampler2D image0;
in vec2 uv_vs;
in vec3 color_vs;

out vec4 color;

void main() {
    float alpha = texture(image0, uv_vs).r;
    color = vec4(color_vs, alpha);
}
