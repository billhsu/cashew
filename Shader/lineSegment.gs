// Shipeng Xu
// billhsu.x@gmail.com

#version 330 core

layout (lines) in;
layout (triangle_strip) out;
layout (max_vertices = 24) out;

uniform mat4 modelView;
uniform mat4 projection;

uniform float thickness;
uniform vec4 lineColor;
out vec4 colorGs;

void vectorsToRect(vec4 vector1, vec4 vector2, vec4 vector3, vec4 vector4) {
    gl_Position = projection * vector1;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector2;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector3;
    colorGs = lineColor;
    EmitVertex();
    
    gl_Position = projection * vector4;
    colorGs = lineColor;
    EmitVertex();
    EndPrimitive();
}

void main (void)
{
    vec4 P = gl_in[0].gl_Position;
    vec4 Q = gl_in[1].gl_Position;
    vec3 PQ = Q.xyz - P.xyz;
    
    vec3 hBase = vec3(1, 0, 0) * thickness;
    vec3 vBase = vec3(0, 1, 0) * thickness;
    vec4 vector0 = P + vec4(hBase, 0);
    vec4 vector1 = P + vec4(vBase, 0);
    vec4 vector2 = P - vec4(hBase, 0);
    vec4 vector3 = P - vec4(vBase, 0);
    
    vec4 vector4 = Q + vec4(hBase, 0);
    vec4 vector5 = Q + vec4(vBase, 0);
    vec4 vector6 = Q - vec4(hBase, 0);
    vec4 vector7 = Q - vec4(vBase, 0);
    
    // up
    vectorsToRect(vector1, vector0, vector2, vector3);
    // bottom
    vectorsToRect(vector5, vector4, vector6, vector7);
    // front
    vectorsToRect(vector1, vector0, vector5, vector4);
    // back
    vectorsToRect(vector3, vector2, vector7, vector6);
    // left
    vectorsToRect(vector3, vector0, vector7, vector4);
    // right
    vectorsToRect(vector2, vector1, vector6, vector5);
}
