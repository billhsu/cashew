// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/Math/Vectors.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include <vector>
#include <OpenGL/gl3.h>

class GLSLShader;
namespace PointRenderer
{
    void prepareRenderData();
    void render(uint textureId);
    void bindPointShader();
    void unbindPointShader();
    GLSLShader* getPointShader();
    std::vector<Vector3>& getPointList();
}