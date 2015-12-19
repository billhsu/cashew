// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
class LineSegment;
class SketchLine;
class Vector3;
class Vector4;

namespace Scene {
    void renderSketchLines(void* data);
    void renderLineSegmentsEndpoints(void* data);
    void renderSingleLineSegment(LineSegment line, Vector4 color,
                                 float thickness);
    void renderSingleSketchLine(SketchLine& sketchLine, const Vector3& color,
                                float thickness);
}
