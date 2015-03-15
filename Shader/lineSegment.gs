// Shipeng Xu
// billhsu.x@gmail.com
// http://www.geeks3d.com/20140815/particle-billboarding-with-the-geometry-shader-glsl/

#version 330 core

varying in vec4 vPosition[2];
layout (triangle_strip) out;
layout (max_vertices = 4) out;

uniform mat4 modelView;
uniform mat4 projection;

uniform float thickness;
uniform vec4 lineColor;
out vec4 colorGs;

void main (void)
{
    vec4 P = vPosition[0];
    vec4 Q = vPosition[1];
    vec2 PQ = Q.xy - P.xy;
    vec2 normal = normalize(vec2(-PQ.y, PQ.x));
    
    vec2 va = P.xy - normal * thickness;
    gl_Position = projection * vec4(va, P.zw);
    colorGs = lineColor;
    EmitVertex();
    
    vec2 vb = P.xy + normal * thickness;
    gl_Position = projection * vec4(vb, P.zw);
    colorGs = lineColor;
    EmitVertex();
    
    vec2 vd = Q.xy - normal * thickness;
    gl_Position = projection * vec4(vd, Q.zw);
    colorGs = lineColor;
    EmitVertex();
    
    vec2 vc = Q.xy + normal * thickness;
    gl_Position = projection * vec4(vc, Q.zw);
    colorGs = lineColor;
    EmitVertex();
    
    EndPrimitive();
}