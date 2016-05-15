// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/Basic/Plane.h"
#include "Core/Basic/SketchLine.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/UI/IMGUI.h"
#include "StateDraw.h"
#include "StateIdle.h"

#include <vector>
StateIdle::StateIdle() {
    stateID = STATE_IDLE;
    internalState = INTERNAL_STATE_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "idle";
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}
void StateIdle::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    if (Controller::bMoveCenterMode) {
        return;
    }
    if (button == Mouse::MOUSE_BUTTON_LEFT) {
        std::vector<Vector3> selectedPoints;
        if (state == Mouse::MOUSE_ACTION_DOWN) {
            internalState = INTERNAL_STATE_MOUSE_DOWN;
            Vector3 v;
            mCamera->getPoint(x, y, SketchLine::getGlobalLineSegments(), v);

            if (!Controller::bCurrLine) {
                selectedPoints.push_back(v);
                Plane::buildPlane(selectedPoints, Controller::currPlane,
                                  Vector3(0, 1, 0));
                if (Controller::currPlane.N.dot(mCamera->getDirection()) > 0) {
                    Controller::currPlane = -Controller::currPlane;
                }
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                    ->selectedPoints = selectedPoints;
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                    ->startPoint = v;
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                    ->endPoint = v;
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                    ->internalState =
                    StateDraw::STATE_DRAW_START_POINT_SELECTED;
                enterState(State::statePool[STATE_DRAW]);
                internalState = INTERNAL_STATE_IDLE;
            } else {
                selectedPoint = v;
            }
        } else if (state == Mouse::MOUSE_ACTION_UP) {
            if (Controller::bCurrLine) {
                SketchLine* sketchLine =
                    SketchLine::lineSegmentToSkectLine(Controller::currLine.ID);
                if (sketchLine == NULL) {
                    return;
                }
                size_t size = sketchLine->getLineSegmentsSize();
                selectedPoints.push_back(
                    sketchLine->getLineSegment(0).points[0]);
                selectedPoints.push_back(
                    sketchLine->getLineSegment(size - 1).points[1]);
                dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                    ->selectedPoints = selectedPoints;
                enterState(State::statePool[STATE_DRAW]);
                internalState = INTERNAL_STATE_IDLE;
            }
        }
    }
}

void StateIdle::MouseLeftDrag(int dx, int dy) {
    if (Controller::bMoveCenterMode) {
        mCamera->setCamCenter(mCamera->getCamCenter() +
                              calcMoveCenterVector(dx, dy, Plane()));
        return;
    }
    if (INTERNAL_STATE_MOUSE_DOWN == internalState) {
        std::vector<Vector3> selectedPoints;
        Vector3 planeVec = Vector3(0, 1, 0);
        selectedPoints.push_back(selectedPoint);
        Plane::buildPlane(selectedPoints, Controller::currPlane, planeVec);
        if (Controller::currPlane.N.dot(mCamera->getDirection()) > 0) {
            Controller::currPlane = -Controller::currPlane;
        }
        dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->selectedPoints =
            selectedPoints;
        dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->startPoint =
            selectedPoint;
        dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->endPoint =
            selectedPoint;
        dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->internalState =
            StateDraw::STATE_DRAW_START_POINT_SELECTED;
        enterState(State::statePool[STATE_DRAW]);
        internalState = INTERNAL_STATE_IDLE;
    }
}

void StateIdle::MouseRightDrag(int dx, int dy) {
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateIdle::prepareState() {
    internalState = INTERNAL_STATE_IDLE;
}

void StateIdle::postState() {
}
