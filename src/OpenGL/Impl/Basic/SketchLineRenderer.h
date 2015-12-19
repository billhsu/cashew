// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include <OpenGL/gl3.h>
#include "Core/Math/Vectors.h"
#include "Core/Basic/SketchLine.h"

class GLSLShader;

namespace SketchLineRenderer {
    void init();
    void render(SketchLine& sketchLine, Vector3 color);
    GLSLShader* getShader();
    void release();
}
