// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"

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