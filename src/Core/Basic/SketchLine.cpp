// Shipeng Xu
// billhsu.x@gmail.com

#include "SketchLine.h"
#include "LineSegment.h"
std::vector<SketchLine> SketchLine::sketchLines;
std::map<int, int> SketchLine::lineSegIdTOSketchLineId;

SketchLine* SketchLine::lineSegmentToSkectLine(int lineSegmentID) {
    if (lineSegIdTOSketchLineId.find(lineSegmentID) !=
        lineSegIdTOSketchLineId.end()) {
        return sketchLineFromID(lineSegIdTOSketchLineId[lineSegmentID]);
    } else {
        return NULL;
    }
}

SketchLine* SketchLine::sketchLineFromID(int sketchLineID) {
    for (int i = 0; i < sketchLines.size(); ++i) {
        if (sketchLines[i].ID == sketchLineID) {
            return &sketchLines[i];
        }
    }
    return NULL;
}

void SketchLine::deleteSketchLine(SketchLine& sketchLine) {
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

void SketchLine::addSketchLine(SketchLine& sketchLine) {
    sketchLines.push_back(sketchLine);
}
