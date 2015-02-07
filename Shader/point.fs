// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

uniform sampler2D PeelLayerDepthMap;
uniform sampler2D point_texture;

in vec2 vertexUV;

out vec4 color;
void main (void)
{
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z){
        discard;
    }
    color = texture(point_texture, vertexUV);
}