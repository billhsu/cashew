// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
class LineSegment;
class SketchLine;
class Vector4;
namespace Scene {
    void renderLineSegments(void* data);
    void renderLineSegmentsEndpoints(void* data);
    void renderSingleLineSegment(LineSegment line, Vector4 color,
                                 float thickness);
    void renderSingleSketchLine(SketchLine sketchLine, Vector4 color,
                                float thickness);
}
