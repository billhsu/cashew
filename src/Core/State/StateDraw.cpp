// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Util/Intersect.h"

int StateDraw::internalState;
StateDraw::StateDraw() {
    stateID = STATE_DRAW;
    internalState = STATE_DRAW_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "draw";
    lua_register(Controller::luaState, "drawPlaneDone", btnDrawPlaneDoneEvent);
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}

void StateDraw::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    if (Controller::bMoveCenterMode) {
        return;
    }
    if (state == Mouse::MOUSE_ACTION_DOWN) {
        if (button == Mouse::MOUSE_BUTTON_LEFT) {
            if (internalState == STATE_DRAW_IDLE) {
                if (Controller::bPencilMode) {
                    startPoint =
                        intersect(Controller::getInstance().getCameraRay(),
                                  Controller::currPlane);
                } else {
                    Controller::getInstance().getCameraPoint(
                        startPoint, Controller::currPlane);
                }
                endPoint = startPoint;
                currentLine.getLineSegments().clear();
                currentLineMirrorX.getLineSegments().clear();
                currentLineMirrorY.getLineSegments().clear();
                currentLineMirrorZ.getLineSegments().clear();
                internalState = STATE_DRAW_START_POINT_SELECTED;
            }
        }
    }
    if (state == Mouse::MOUSE_ACTION_UP) {
        if (button == Mouse::MOUSE_BUTTON_LEFT) {
            if (internalState == STATE_DRAW_START_POINT_SELECTED) {
                Controller::getInstance().getCameraPoint(endPoint,
                                                         Controller::currPlane);
                if (currentLine.getLineSegments().size() >= 1) {
                    if (!Controller::bPencilMode) {
                        if ((startPoint - endPoint).length() < 0.25f) {
                            internalState = STATE_DRAW_IDLE;
                            return;
                        }
                    }
                    SketchLine::addSketchLine(currentLine);
                    if (Controller::mirrorMode & Controller::MIRROR_MODE_X) {
                        SketchLine::addSketchLine(currentLineMirrorX);
                    }
                    if (Controller::mirrorMode & Controller::MIRROR_MODE_Y) {
                        SketchLine::addSketchLine(currentLineMirrorY);
                    }
                    if (Controller::mirrorMode & Controller::MIRROR_MODE_Z) {
                        SketchLine::addSketchLine(currentLineMirrorZ);
                    }
                }
                internalState = STATE_DRAW_IDLE;
            }
        }
    }
}

void StateDraw::addLineWithMirror() {
    LineSegment line = LineSegment(startPoint, endPoint);
    currentLine.addLineSegment(line);

    if (Controller::mirrorMode & Controller::MIRROR_MODE_X) {
        Vector3 startPointMirror = startPoint;
        Vector3 endPointMirror = endPoint;
        startPointMirror.x = -startPointMirror.x;
        endPointMirror.x = -endPointMirror.x;
        line = LineSegment(startPointMirror, endPointMirror);
        currentLineMirrorX.getLineSegments().push_back(line);
    }
    if (Controller::mirrorMode & Controller::MIRROR_MODE_Y) {
        Vector3 startPointMirror = startPoint;
        Vector3 endPointMirror = endPoint;
        startPointMirror.y = -startPointMirror.y;
        endPointMirror.y = -endPointMirror.y;
        line = LineSegment(startPointMirror, endPointMirror);
        currentLineMirrorY.getLineSegments().push_back(line);
    }
    if (Controller::mirrorMode & Controller::MIRROR_MODE_Z) {
        Vector3 startPointMirror = startPoint;
        Vector3 endPointMirror = endPoint;
        startPointMirror.z = -startPointMirror.z;
        endPointMirror.z = -endPointMirror.z;
        line = LineSegment(startPointMirror, endPointMirror);
        currentLineMirrorZ.getLineSegments().push_back(line);
    }
}

void StateDraw::MouseLeftDrag(int dx, int dy) {
    if (Controller::bMoveCenterMode) {
        mCamera->setCamCenter(
            mCamera->getCamCenter() +
            calcMoveCenterVector(dx, dy, Controller::currPlane));
        return;
    }
    if (internalState == STATE_DRAW_START_POINT_SELECTED) {
        if (Controller::bPencilMode) {
            endPoint = intersect(Controller::getInstance().getCameraRay(),
                                 Controller::currPlane);
            if ((startPoint - endPoint).length() < 0.25f) {
                return;
            }
            addLineWithMirror();
            startPoint = endPoint;
        } else {
            Controller::getInstance().getCameraPoint(endPoint,
                                                     Controller::currPlane);
            if (currentLine.getLineSegments().size() == 0) {
                addLineWithMirror();
            }
            currentLine.getLineSegments()[0].points[1] = endPoint;
            if (Controller::mirrorMode & Controller::MIRROR_MODE_X) {
                Vector3 endPointMirror = endPoint;
                endPointMirror.x = -endPointMirror.x;
                currentLineMirrorX.getLineSegments()[0].points[1] =
                    endPointMirror;
            }
            if (Controller::mirrorMode & Controller::MIRROR_MODE_Y) {
                Vector3 endPointMirror = endPoint;
                endPointMirror.y = -endPointMirror.y;
                currentLineMirrorY.getLineSegments()[0].points[1] =
                    endPointMirror;
            }
            if (Controller::mirrorMode & Controller::MIRROR_MODE_Z) {
                Vector3 endPointMirror = endPoint;
                endPointMirror.z = -endPointMirror.z;
                currentLineMirrorZ.getLineSegments()[0].points[1] =
                    endPointMirror;
            }
        }
    }
}

void StateDraw::MouseRightDrag(int dx, int dy) {
    static bool changeDirection = false;
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
    if (selectedPoints.size() != 2) {
        return;
    }
    if (checkIfTwoPointsVertical(selectedPoints[0], selectedPoints[1])) {
        return;
    }

    if (fabs(fabs(Controller::rotate.x) - 90) < 25) {
        if (!changeDirection) {
            changeDirection = true;
            Vector3 vecXZ = (selectedPoints[0] - selectedPoints[1]);
            vecXZ.y = 0;
            Vector3 calcNormal = vecXZ.cross(Vector3(0, 0, 1));
            Plane::buildPlane(selectedPoints, Controller::currPlane,
                              calcNormal);
        }
    } else {
        if (changeDirection) {
            changeDirection = false;
            Vector3 vecXZ = (selectedPoints[0] - selectedPoints[1]);
            vecXZ.y = 0;
            Vector3 calcNormal = vecXZ.cross(Vector3(0, 1, 0));
            std::vector<Vector3> mappedPoints =
                mapSelectedPoints(selectedPoints[0], selectedPoints[1]);
            Plane::buildPlane(mappedPoints, Controller::currPlane, calcNormal);
        }
    }
}

void StateDraw::Keyboard(unsigned char key, unsigned char status) {
}

void StateDraw::prepareState() {
    currentLine.getLineSegments().clear();
    currentLineMirrorX.getLineSegments().clear();
    currentLineMirrorY.getLineSegments().clear();
    currentLineMirrorZ.getLineSegments().clear();
    if (selectedPoints.size() != 2) {
        return;
    }
    if (previousState == NULL || previousState->getStateID() != STATE_IDLE) {
        return;
    }
    Vector3 calcNormal = Vector3(0, 0, 1);
    std::vector<Vector3> selectedPointsMap;
    Matrix4 invertCameraMatrix = mCamera->getInvertMatrix();
    Vector3 vecXZ = (selectedPoints[0] - selectedPoints[1]);
    vecXZ.y = 0;
    if (checkIfTwoPointsVertical(selectedPoints[0], selectedPoints[1])) {
        Vector3 planeVec = invertCameraMatrix * Vector3(0, 0, 1);
        planeVec.y = 0;
        planeVec.normalize();
        calcNormal = planeVec;
    } else {
        calcNormal = vecXZ.cross(Vector3(0, 1, 0));
    }
    selectedPointsMap = mapSelectedPoints(selectedPoints[0], selectedPoints[1]);
    Plane::buildPlane(selectedPointsMap, Controller::currPlane, calcNormal);
    Controller::getInstance().correctCurrPlaneNormal();
    Quaternion q =
        Quaternion::fromVector(Controller::currPlane.N, Quaternion::Z_NEG_AXIS);

    mCamera->rotateCamTo(q);
    mCamera->setCamCenterTo(
        (Controller::currLine.points[0] + Controller::currLine.points[1]) /
        2.0f);
}

bool StateDraw::checkIfTwoPointsVertical(Vector3 p1, Vector3 p2) {
    Vector3 vecDiff = (p1 - p2);
    Vector3 vecXZ = vecDiff;
    vecXZ.y = 0;

    if (vecDiff.length() == 0) {
        return true;
    }
    if (vecDiff.y == 0 || vecXZ.length() / vecDiff.length() >= 0.1) {
        return false;
    }
    return true;
}

std::vector<Vector3> StateDraw::mapSelectedPoints(Vector3 p1, Vector3 p2) {
    std::vector<Vector3> mappedSelectedPoints;
    if (checkIfTwoPointsVertical(p1, p2)) {
        Vector3 middleVec = (p1 + p2) / 2.0f;
        Vector3 v1 = middleVec;
        v1.y = p1.y;
        Vector3 v2 = middleVec;
        v2.y = p2.y;
        mappedSelectedPoints.push_back(v1);
        mappedSelectedPoints.push_back(v2);
    } else {
        float middleVal = ((p1 + p2) / 2.0f).y;
        Vector3 v1 = p1;
        v1.y = middleVal;
        Vector3 v2 = p2;
        v2.y = middleVal;
        mappedSelectedPoints.push_back(v1);
        mappedSelectedPoints.push_back(v2);
    }
    return mappedSelectedPoints;
}
void StateDraw::postState() {
}

int StateDraw::btnDrawPlaneDoneEvent(lua_State* L) {
    enterState(State::statePool[STATE_IDLE]);
    return 0;
}
