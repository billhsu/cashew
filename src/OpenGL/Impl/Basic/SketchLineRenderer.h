// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include <OpenGL/gl3.h>
#include "Core/Math/Vectors.h"
#include "Core/Basic/SketchLine.h"

namespace SketchLineRenderer {
    void init();
    void render(SketchLine sketchLine, Vector3 color);
    void release();
}
