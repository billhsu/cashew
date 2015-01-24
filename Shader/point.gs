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
    mat4 MV = modelView;
    
    vec3 right = vec3(MV[0][0],
                      MV[1][0],
                      MV[2][0]);
    
    vec3 up = vec3(MV[0][1],
                   MV[1][1],
                   MV[2][1]);
    
    vec3 P = gl_in[0].gl_Position.xyz;
    
    mat4 VP = projection * modelView;
    
    vec3 va = P - (right + up) * point_size;
    gl_Position = VP * vec4(va, 1.0);
    vertexUV = vec2(0.0, 0.0);
    EmitVertex();
    
    vec3 vb = P - (right - up) * point_size;
    gl_Position = VP * vec4(vb, 1.0);
    vertexUV = vec2(0.0, 1.0);
    EmitVertex();
    
    vec3 vd = P + (right - up) * point_size;
    gl_Position = VP * vec4(vd, 1.0);
    vertexUV = vec2(1.0, 0.0);
    EmitVertex();
    
    vec3 vc = P + (right + up) * point_size;
    gl_Position = VP * vec4(vc, 1.0);
    vertexUV = vec2(1.0, 1.0);
    EmitVertex();
    
    EndPrimitive();  
}