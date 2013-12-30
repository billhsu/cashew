#include "State.h"
#include "Controller.h"
#include "Camera.h"

State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
}

// State Idle

void StateIdle::MouseButton(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        State::currState = stateSelectPlane;
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        ctrl->lastMouseX=x;
        ctrl->lastMouseY=y;
    }
}

void StateIdle::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - ctrl->lastMouseX;
    dy = y - ctrl->lastMouseY;
    ctrl->lastMouseX = x;
    ctrl->lastMouseY = y;

    if(ctrl->mouseButton==GLUT_RIGHT_BUTTON && ctrl->mouseState==GLUT_DOWN)
    {

    }
}

void StateIdle::PassiveMotion(int x, int y)
{

}

void StateIdle::Keyboard(unsigned char key, int x, int y)
{

}

void StateIdle::render(float timeDelta)
{

}

// State Select Plane
void StateSelectPlane::MouseButton(int button, int state, int x, int y)
{

}

void StateSelectPlane::MouseMotion(int x, int y)
{

}

void StateSelectPlane::PassiveMotion(int x, int y)
{

}

void StateSelectPlane::Keyboard(unsigned char key, int x, int y)
{

}

void StateSelectPlane::render(float timeDelta)
{
    
}

// State Draw
void StateDraw::MouseButton(int button, int state, int x, int y)
{

}

void StateDraw::MouseMotion(int x, int y)
{

}

void StateDraw::PassiveMotion(int x, int y)
{

}

void StateDraw::Keyboard(unsigned char key, int x, int y)
{

}

void StateDraw::render(float timeDelta)
{
    
}
