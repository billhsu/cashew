// Shipeng Xu
// billhsu.x@gmail.com
// http://www.geeks3d.com/20140815/particle-billboarding-with-the-geometry-shader-glsl/

#version 330 core

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

uniform mat4 modelView;
uniform mat4 projection;

uniform float pointSize;

out vec2 vertexUV;

void main (void)
{
    vec4 P = gl_in[0].gl_Position;
    
    vec2 va = P.xy + vec2(-0.5, -0.5) * pointSize;
    gl_Position = projection * vec4(va, P.zw);
    vertexUV = vec2(0.0, 0.0);
    EmitVertex();
    
    vec2 vb = P.xy + vec2(-0.5, 0.5) * pointSize;
    gl_Position = projection * vec4(vb, P.zw);
    vertexUV = vec2(0.0, 1.0);
    EmitVertex();
    
    vec2 vd = P.xy + vec2(0.5, -0.5) * pointSize;
    gl_Position = projection * vec4(vd, P.zw);
    vertexUV = vec2(1.0, 0.0);
    EmitVertex();
    
    vec2 vc = P.xy + vec2(0.5, 0.5) * pointSize;
    gl_Position = projection * vec4(vc, P.zw);
    vertexUV = vec2(1.0, 1.0);
    EmitVertex();
    
    EndPrimitive();
}