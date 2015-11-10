// Shipeng Xu
// billhsu.x@gmail.com

#include "SketchLine.h"
#include "LineSegment.h"

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
    SketchLineOperation lineOp;
    lineOp.sketchLineID = sketchLine.ID;
    lineOp.operation = OPERATION_ADD_LINE;
    lineOperations.push_back(lineOp);
    sketchLines.push_back(sketchLine);
    updateGlobalLineSegments();
    std::cout << getGlobalLineSegments().size() << std::endl;
}

std::vector<LineSegment>& SketchLine::getGlobalLineSegments() {
    return globalLineSegments;
}

std::vector<LineSegment> SketchLine::getLineSegments() {
    return lineSegments;
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
            LineSegment lineSegment = sketchLines[i].lineSegments[j];
            lineSegment.ID = ++count;
            lineSegIdTOSketchLineId[lineSegment.ID] = sketchLines[i].ID;
            globalLineSegments.push_back(lineSegment);
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