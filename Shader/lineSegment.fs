// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D PeelLayerDepthMap;
uniform sampler2D pointTexture;

in vec4 colorGs;

out vec4 color;
void main (void)
{
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z) {
        discard;
    }
    if (colorGs.a<0.1) {
        discard;
    }
    color = colorGs;
}
