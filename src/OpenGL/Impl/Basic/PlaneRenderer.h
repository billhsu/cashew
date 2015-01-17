// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/Basic/Plane.h"
#include "Core/Math/Vectors.h"
#include <OpenGL/gl3.h>

namespace PlaneRenderer
{
    void prepareRenderData();
    void render(Plane p, Vector4 color);
    
    GLfloat vertexBufferData[8];
    GLfloat colorBufferData[16];
    GLuint indexBufferData[6];
    
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint indexBuffer;
    GLuint vertexArrayObj;
}