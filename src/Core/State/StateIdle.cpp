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
    if (Controller::bMoveCenterMode) {
        return;
    }
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    } else if (button == Mouse::MOUSE_BUTTON_LEFT) {
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
                Plane::buildPlane(selectedPoints, Controller::currPlane,
                                  Vector3(0, 0, 1));
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
        Vector3 moveVector;
        float sign = Controller::rotate.x > 0 ? 1.0f : -1.0f;
        if (fabs(Controller::rotate.x) <= 45) {
            moveVector =
                Vector3(-(float)dx / IMGUI::getBackingRatioX() / 20.0f, 0.0f,
                        sign * (float)dy / IMGUI::getBackingRatioY() / 20.0f);
        } else {
            moveVector =
                Vector3(-(float)dx / IMGUI::getBackingRatioX() / 20.0f,
                        (float)dy / IMGUI::getBackingRatioY() / 20.0f, 0.0f);
        }
        Matrix4 modelView = mCamera->getModelView();
        modelView.invert();
        moveVector = modelView * moveVector;
        moveVector.y = 0;
        mCamera->setCamCenter(mCamera->getCamCenter() + moveVector);
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
void StateIdle::UIEvent(int event) {
    if (event == Controller::BTN_ID_STANDARD_VIEW) {
        Quaternion q = Quaternion::fromEuler(Vector3(-90, 0, 0));
        mCamera->setCamCenterTo(Vector3(0, 0, 0));
        mCamera->rotateCamTo(q);
    } else if (event == Controller::BTN_ID_DELETE_LINE) {
        enterState(State::statePool[STATE_DELETE]);
    } else if (event == Controller::BTN_ID_MOVE_CENTER) {
        enterState(State::statePool[STATE_MOVE_CENTER]);
    }
}
