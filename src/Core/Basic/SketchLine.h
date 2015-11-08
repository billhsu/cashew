// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include <vector>
#include <map>
class LineSegment;
// Sketch line contains multiple line segments
class SketchLine {
   public:
    std::vector<LineSegment> lineSegments;
    // get the sketch line from a line segment
    static SketchLine* lineSegmentToSkectLine(int lineSegmentID);

    static SketchLine* sketchLineFromID(int sketchLineID);
    static void addSketchLine(SketchLine& sketchLine);
    static void deleteSketchLine(SketchLine& sketchLine);

    static std::map<int, int> lineSegIdTOSketchLineId;

   private:
    static std::vector<SketchLine> sketchLines;
    int ID;
};