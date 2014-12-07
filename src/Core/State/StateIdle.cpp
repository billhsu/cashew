// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "StateSelectPlane.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Basic/Plane.h"

void StateIdle::MouseButton(int button, int state, int x, int y)
{
    if(button == Controller::MOUSE_SCROLL)
    {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    else if(button == Controller::MOUSE_LEFT && state == Controller::MOUSE_UP)
    {
        Vector3 v;
        mCamera->getPoint(x, y, Controller::sketchLines, v);
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints.clear();
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints.push_back(v);
        Plane::buildPlane(
                          static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints, Controller::currPlane);
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N,
                                              Quaternion::Z_NEG_AXIS);
        mCamera->setCamCenterTo(v);
        mCamera->rotateCamTo(q);
        enterState(State::statePool[STATE_SELECT_PLANE]);
    }
}

void StateIdle::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
}

void StateIdle::prepareState()
{
}