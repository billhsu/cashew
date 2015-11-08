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
    static SketchLine* lineSegmentToSkectLine(int lineSegmentID) {
        if (lineSegIdTOSketchLineId.find(lineSegmentID) !=
            lineSegIdTOSketchLineId.end()) {
            return sketchLineFromID(lineSegIdTOSketchLineId[lineSegmentID]);
        } else {
            return NULL;
        }
    }

    static SketchLine* sketchLineFromID(int sketchLineID) {
        for (int i = 0; i < sketchLines.size(); ++i) {
            if (sketchLines[i].ID == sketchLineID) {
                return &sketchLines[i];
            }
        }
        return NULL;
    }
    static void addSketchLine(SketchLine& sketchLine) {
        sketchLines.push_back(sketchLine);
    }

    static void deleteSketchLine(SketchLine& sketchLine) {
        for (int i = 0; i < sketchLines.size(); ++i) {
            if (sketchLines[i].ID == sketchLine.ID) {
                for (int j = 0; j < sketchLines[i].lineSegments.size(); ++j) {
                    // TODO: delete the line segments
                }
                sketchLines.erase(sketchLines.begin() + i);
                return;
            }
        }
    }

    static std::map<int, int> lineSegIdTOSketchLineId;

   private:
    static std::vector<SketchLine> sketchLines;
    int ID;
};