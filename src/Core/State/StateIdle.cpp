// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "StateSelectPlane.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateIdle::StateIdle() {
    stateID = STATE_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
}
void StateIdle::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    } else if (button == Mouse::MOUSE_LEFT && state == Mouse::MOUSE_ACTION_UP) {
        Vector3 v;
        mCamera->getPoint(x, y, Controller::sketchLines, v);
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])
            ->selectedPoints.clear();
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])
            ->selectedPoints.push_back(v);
        Plane::buildPlane(
            static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])
                ->selectedPoints,
            Controller::currPlane);
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N,
                                              Quaternion::Z_NEG_AXIS);
        mCamera->setCamCenterTo(v);
        mCamera->rotateCamTo(q);
        enterState(State::statePool[STATE_SELECT_PLANE]);
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
void StateIdle::UIEvent(UINode* sender, int event) {
    if (sender->nodeID == Controller::BTN_ID_STANDARD_VIEW) {
        Quaternion q = Quaternion::fromEuler(Vector3(-90, 0, 0));
        mCamera->setCamCenterTo(Vector3(0, 0, 0));
        mCamera->rotateCamTo(q);
    } else if (sender->nodeID == Controller::BTN_ID_DELETE_LINE) {
        enterState(State::statePool[STATE_DELETE]);
    }
}
