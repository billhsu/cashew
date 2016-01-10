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
                Controller::getInstance().getCameraPoint(startPoint,
                                                         Controller::currPlane);
                Controller::getInstance().getCameraPoint(endPoint,
                                                         Controller::currPlane);
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
                if (currentLine.getLineSegments().size() > 1) {
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
        endPoint = intersect(Controller::getInstance().getCameraRay(),
                             Controller::currPlane);
        if ((startPoint - endPoint).length() < 0.25f) {
            return;
        }
        addLineWithMirror();
        startPoint = endPoint;
    }
}

void StateDraw::MouseRightDrag(int dx, int dy) {
    static bool changeDirection = false;
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
    if (fabs(fabs(Controller::rotate.x) - 90) < 25) {
        if (!changeDirection) {
            changeDirection = true;
            Plane::buildPlane(selectedPoints, Controller::currPlane,
                              Vector3(0, 1, 0));
        }
    } else {
        if (changeDirection) {
            changeDirection = false;
            Plane::buildPlane(selectedPoints, Controller::currPlane,
                              Vector3(0, 0, 1));
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
}

void StateDraw::postState() {
}

int StateDraw::btnDrawPlaneDoneEvent(lua_State* L) {
    enterState(State::statePool[STATE_IDLE]);
    return 0;
}
