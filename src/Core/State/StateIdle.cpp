// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include "Core/Basic/SketchLine.h"
#include "Core/UI/IMGUI.h"

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
                unsigned long size = sketchLine->getLineSegments().size();
                selectedPoints.push_back(
                    sketchLine->getLineSegments()[0].points[0]);
                selectedPoints.push_back(
                    sketchLine->getLineSegments()[size - 1].points[1]);

                Vector3 vecDiff = (selectedPoints[0] - selectedPoints[1]);
                Vector3 vecXZ = vecDiff;
                vecXZ.y = 0;

                if (vecDiff.length() == 0) {
                    return;
                }
                Vector3 calcNormal = Vector3(0, 0, 1);
                std::cout << vecDiff << " - " << vecXZ << std::endl;
                std::vector<Vector3> selectedPointsMap;
                if (vecDiff.y == 0 ||
                    vecXZ.length() / vecDiff.length() >= 0.1) {
                    calcNormal = vecXZ.cross(Vector3(0, 1, 0));
                    float middleVal =
                        ((selectedPoints[0] + selectedPoints[1]) / 2.0f).y;
                    Vector3 v1 = selectedPoints[0];
                    v1.y = middleVal;
                    Vector3 v2 = selectedPoints[1];
                    v2.y = middleVal;
                    selectedPointsMap.push_back(v1);
                    selectedPointsMap.push_back(v2);
                } else {
                    Vector3 planeVec = mCamera->getDirection();
                    planeVec.y = 0;
                    //                    planeVec = planeVec.cross(Vector3(0,
                    //                    1, 0));
                    planeVec.normalize();
                    calcNormal = planeVec;
                    selectedPointsMap = selectedPoints;
                }

                Plane::buildPlane(selectedPointsMap, Controller::currPlane,
                                  calcNormal);

                if (Controller::currPlane.N.dot(mCamera->getDirection()) > 0) {
                    Controller::currPlane = -Controller::currPlane;
                }
                Quaternion q = Quaternion::fromVector(Controller::currPlane.N,
                                                      Quaternion::Z_NEG_AXIS);
                mCamera->rotateCamTo(q);
                mCamera->setCamCenterTo((Controller::currLine.points[0] +
                                         Controller::currLine.points[1]) /
                                        2.0f);
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
    std::cout << mCamera->getDirection() << std::endl;
}

void StateIdle::prepareState() {
    internalState = INTERNAL_STATE_IDLE;
}

void StateIdle::postState() {
}
void StateIdle::UIEvent(int event) {
    if (event == Controller::BTN_ID_STANDARD_VIEW) {
        Quaternion q = Quaternion::fromEuler(Vector3(-90, 0, 0));
        mCamera->setCamCenterTo(Vector3(0, 0, 0));
        mCamera->rotateCamTo(q);
    } else if (event == Controller::BTN_ID_DELETE_LINE) {
        enterState(State::statePool[STATE_DELETE]);
    }
}
