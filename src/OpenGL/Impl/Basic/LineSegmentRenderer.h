// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/Math/Vectors.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include <vector>
#include <OpenGL/gl3.h>

class GLSLShader;
class LineSegment;
namespace LineSegmentRenderer
{
    void prepareRenderData();
    void render(uint textureId);
    GLSLShader* getLineSegmentShader();
    std::vector<LineSegment>& getLineSegmentList();
    void release();
}