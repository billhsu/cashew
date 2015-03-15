// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D PeelLayerDepthMap;
uniform sampler2D pointTexture;

in vec2 vertexUV;

out vec4 color;
void main (void)
{
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z){
        discard;
    }
    vec4 texColor = texture(pointTexture, vertexUV);
    if (texColor.a<0.1) {
        discard;
    }
    color = texColor;
}
