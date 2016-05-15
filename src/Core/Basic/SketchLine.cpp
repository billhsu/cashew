// Shipeng Xu
// billhsu.x@gmail.com

#include "SketchLine.h"

std::vector<SketchLine> SketchLine::sketchLines;
std::map<int, int> SketchLine::lineSegIdTOSketchLineId;
std::vector<LineSegment> SketchLine::globalLineSegments;

std::vector<SketchLine> SketchLine::deletedLines;
std::vector<SketchLine> SketchLine::redoLines;
std::vector<SketchLine::SketchLineOperation> SketchLine::lineOperations;
std::vector<SketchLine::SketchLineOperation> SketchLine::redoOperations;

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
            SketchLineOperation lineOp;
            lineOp.sketchLineID = sketchLine.ID;
            lineOp.operation = OPERATION_DELETE_LINE;
            lineOperations.push_back(lineOp);
            deletedLines.push_back(sketchLines[i]);
            sketchLines.erase(sketchLines.begin() + i);
            updateGlobalLineSegments();
            return;
        }
    }
}

void SketchLine::addSketchLine(SketchLine& sketchLine) {
    static int IDCounter = 0;
    sketchLine.ID = IDCounter++;
    std::cout << "SketchLine::addSketchLine " << IDCounter << std::endl;
    SketchLineOperation lineOp;
    lineOp.sketchLineID = sketchLine.ID;
    lineOp.operation = OPERATION_ADD_LINE;
    lineOperations.push_back(lineOp);
    sketchLines.push_back(sketchLine);
    updateGlobalLineSegments();
}

std::vector<LineSegment>& SketchLine::getGlobalLineSegments() {
    return globalLineSegments;
}

const LineSegment SketchLine::getLineSegment(const size_t index) {
    return lineSegments[index];
}

void SketchLine::setLineSegmentPoint(const size_t index, const int whichPoint,
                                     const Vector3 point) {
    lineSegments[index].points[whichPoint] = point;
}

void SketchLine::setLineSegment(const size_t index,
                                const LineSegment lineSegment) {
    lineSegments[index] = lineSegment;
}
size_t SketchLine::getLineSegmentsSize() {
    return lineSegments.size();
}
void SketchLine::clearLineSegments() {
    lineSegments.clear();
}
void SketchLine::addLineSegment(const LineSegment& line) {
    lineSegments.push_back(line);
    updateGlobalLineSegments();
}

void SketchLine::updateGlobalLineSegments() {
    globalLineSegments.clear();
    lineSegIdTOSketchLineId.clear();
    int count = 0;
    for (int i = 0; i < sketchLines.size(); ++i) {
        for (int j = 0; j < sketchLines[i].lineSegments.size(); ++j) {
            LineSegment* lineSegment = &sketchLines[i].lineSegments[j];
            lineSegment->ID = ++count;
            lineSegIdTOSketchLineId[lineSegment->ID] = sketchLines[i].ID;
            globalLineSegments.push_back(*lineSegment);
        }
    }
}

void SketchLine::undoLastOperation() {
    if (lineOperations.size() > 0) {
        SketchLineOperation lineOp = lineOperations.back();
        redoOperations.push_back(lineOp);
        lineOperations.pop_back();
        if (lineOp.operation == OPERATION_ADD_LINE) {
            for (int i = 0; i < sketchLines.size(); ++i) {
                if (lineOp.sketchLineID == sketchLines[i].ID) {
                    redoLines.push_back(sketchLines[i]);
                    sketchLines.erase(sketchLines.begin() + i);
                    break;
                }
            }
        } else if (lineOp.operation == OPERATION_DELETE_LINE) {
            for (int i = 0; i < deletedLines.size(); ++i) {
                if (lineOp.sketchLineID == deletedLines[i].ID) {
                    sketchLines.push_back(deletedLines[i]);
                    redoLines.push_back(deletedLines[i]);
                    deletedLines.erase(deletedLines.begin() + i);
                    break;
                }
            }
        }
        updateGlobalLineSegments();
    }
}

void SketchLine::redoLastOperation() {
    if (redoOperations.size() > 0) {
        SketchLineOperation lineOp = redoOperations.back();
        redoOperations.pop_back();
        bool idFound = false;
        int idPos = 0;
        for (int i = 0; i < redoLines.size(); ++i) {
            if (lineOp.sketchLineID == redoLines[i].ID) {
                idFound = true;
                idPos = i;
                break;
            }
        }
        if (!idFound)
            return;
        if (lineOp.operation == OPERATION_ADD_LINE) {
            addSketchLine(redoLines[idPos]);
        } else if (lineOp.operation == OPERATION_DELETE_LINE) {
            deleteSketchLine(redoLines[idPos]);
        }
        redoLines.erase(redoLines.begin() + idPos);
        updateGlobalLineSegments();
    }
}