// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include <vector>
StateIdle::StateIdle() {
    stateID = STATE_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "idle";
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}
void StateIdle::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    } else if (button == Mouse::MOUSE_BUTTON_LEFT &&
               state == Mouse::MOUSE_ACTION_DOWN) {
        Vector3 planeVec = Vector3(0, 1, 0);
        Plane drawPlane;
        std::vector<Vector3> selectedPoints;
        if (Controller::bCurrLine && !Controller::bCurrPoint) {
            selectedPoints.push_back(Controller::currLine.points[0]);
            selectedPoints.push_back(Controller::currLine.points[1]);
            Plane::buildPlane(selectedPoints, Controller::currPlane, planeVec);
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
        } else {
            Vector3 v;
            mCamera->getPoint(x, y, Controller::sketchLines, v);
            selectedPoints.push_back(v);
            Plane::buildPlane(selectedPoints, Controller::currPlane, planeVec);
            if (Controller::currPlane.N.dot(mCamera->getDirection()) > 0) {
                Controller::currPlane = -Controller::currPlane;
            }
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                ->selectedPoints = selectedPoints;
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->startPoint =
                v;
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])->endPoint =
                v;
            dynamic_cast<StateDraw*>(State::statePool[STATE_DRAW])
                ->internalState = StateDraw::STATE_DRAW_START_POINT_SELECTED;
            enterState(State::statePool[STATE_DRAW]);
        }
    }
}

void StateIdle::MouseRightDrag(int dx, int dy) {
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateIdle::prepareState() {
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
