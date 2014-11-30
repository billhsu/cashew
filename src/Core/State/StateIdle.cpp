// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/State/StateIdle.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"

void StateIdle::MouseButton(int button, int state, int x, int y)
{
}

void StateIdle::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
}

void StateIdle::prepareState()
{
}