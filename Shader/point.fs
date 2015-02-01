// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D image0;
uniform sampler2D PeelLayerDepthMap;

in vec2 vertexUV;

out vec4 color;
void main (void)
{
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z){
        discard;
    }
    color = texture(image0, vertexUV);
}