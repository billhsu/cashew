// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D PeelLayerDepthMap;

in vec4 color_vs;
out vec4 color;

void main() {
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z){
        discard;
    }
    color = color_vs;
}