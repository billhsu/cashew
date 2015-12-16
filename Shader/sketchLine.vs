// Shipeng Xu
// billhsu.x@gmail.com
// Thanks for the below links:
// http://mattdesl.svbtle.com/drawing-lines-is-hard
// https://github.com/mattdesl/webgl-lines

#version 330 core

uniform mat4 modelView;
uniform mat4 projection;
uniform float aspect;
uniform float thickness;

layout (location = 0) in vec3  position;
layout (location = 1) in vec3  lineInfo;
layout (location = 2) in vec3  previous;
layout (location = 3) in vec3  next;


void main() {
    vec2 aspectVec = vec2(aspect, 1.0);
    mat4 projViewModel = projection * modelView;
    vec4 previousProjected = projViewModel * vec4(previous, 1.0);
    vec4 currentProjected = projViewModel * vec4(position, 1.0);
    vec4 nextProjected = projViewModel * vec4(next, 1.0);
    vec4 nonProjected = modelView * vec4(position, 1.0);
    
    
    //get 2D screen space with W divide and aspect correction
    vec2 currentScreen = currentProjected.xy / currentProjected.w * aspectVec;
    vec2 previousScreen = previousProjected.xy / previousProjected.w * aspectVec;
    vec2 nextScreen = nextProjected.xy / nextProjected.w * aspectVec;
    float len = thickness;
    float orientation = lineInfo.x;
    
    //starting point uses (next - current)
    vec2 dir = vec2(0.0);
    if (currentScreen == previousScreen) {
        dir = normalize(nextScreen - currentScreen);
    } else if (currentScreen == nextScreen) {
        //ending point uses (current - previous)
        dir = normalize(currentScreen - previousScreen);
    } else {
        vec2 dirA = normalize((currentScreen - previousScreen));
        vec2 dirB = normalize((nextScreen - currentScreen));
        dir = dirA;
    }
    vec2 normal = vec2(-dir.y, dir.x);
    normal *= len/2.0;
    normal.x /= aspect;
    
    vec4 offset = vec4(normal * orientation, 0.0, 1.0);
    gl_Position = projection * (nonProjected + offset);
    gl_PointSize = 1.0;
}
