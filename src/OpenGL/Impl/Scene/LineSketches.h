// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
class LineSegment;
class Vector4;
namespace Scene {
    void renderSketchLines(void* data);
    void renderSketchLinesEndpoints(void* data);
    void renderSingleSketchLine(LineSegment line, Vector4 color,
                                float thickness);
}