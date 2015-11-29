// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core
#define FOG_DENSITY 0.05

uniform sampler2D PeelLayerDepthMap;

in vec4 colorGs;

out vec4 color;

// https://github.com/hughsk/glsl-fog/blob/master/exp2.glsl
float fogFactorExp2(
                    const float dist,
                    const float density
                    ) {
    const float LOG2 = -1.442695;
    float d = density * dist;
    return 1.0 - clamp(exp2(d * d * LOG2), 0.0, 1.0);
}

void main (void)
{
    float z = texelFetch(PeelLayerDepthMap, ivec2(gl_FragCoord.xy), 0).x;
    if(gl_FragCoord.z <= z) {
        discard;
    }
    if (colorGs.a<0.1) {
        discard;
    }
    float fogDistance = gl_FragCoord.z / gl_FragCoord.w;
    float fogAmount = fogFactorExp2(fogDistance, FOG_DENSITY);
    vec4 fogColor = vec4(colorGs.xyz, 0.3f);
    color = mix(colorGs, fogColor, fogAmount);
}

