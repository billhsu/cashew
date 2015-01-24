// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/Basic/Plane.h"
#include "Core/Math/Vectors.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"

#include <OpenGL/gl3.h>
class GLSLShader;
namespace PlaneRenderer
{
    void prepareRenderData();
    void render(Plane p, Vector3 center, float size, Vector4 color);
    GLSLShader* getPlaneShader();
}