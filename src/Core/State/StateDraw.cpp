// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateDraw::StateDraw()
{
    stateID = STATE_DRAW;
    internalState = STATE_DRAW_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    btnDrawPlaneDone = Controller::GUI->addButton(stateID*100 + BTN_ID_DRAW_PLANE_DONE, "BTN_ID_DRAW_PLANE_DONE", btnDrawPlaneDoneEvent, this);
    btnDrawPlaneDone->setVisibility(false);
}

void StateDraw::MouseButton(int button, int state, int x, int y)
{
    if(button == Mouse::MOUSE_SCROLL)
    {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    if(state == Mouse::MOUSE_DOWN)
    {
        if(button == Mouse::MOUSE_LEFT)
        {
            if(internalState==STATE_DRAW_IDLE)
            {
                Controller::getInstance().getCameraPoint(startPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                Controller::getInstance().getCameraPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                internalState = STATE_DRAW_START_POINT_SELECTED;
            }
        }
    }
    if(state == Mouse::MOUSE_UP)
    {
        if(button == Mouse::MOUSE_LEFT)
        {
            if(internalState == STATE_DRAW_START_POINT_SELECTED)
            {
                Controller::getInstance().getCameraPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                LineSegment line = LineSegment(startPoint, endPoint);
                
                Vector3 startPointMirror = startPoint;
                Vector3 endPointMirror = endPoint;
                startPointMirror.x = -startPointMirror.x;
                endPointMirror.x   = -endPointMirror.x;
                LineSegment lineMirror = LineSegment(startPointMirror, endPointMirror);
                
                Controller::addLine(line);
                Controller::addLine(lineMirror);
                internalState = STATE_DRAW_IDLE;
            }
        }
    }
    
}

void StateDraw::MouseLeftDrag(int dx, int dy)
{
    if(internalState == STATE_DRAW_START_POINT_SELECTED)
    {
        Controller::getInstance().getCameraPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
    }
}

void StateDraw::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateDraw::Keyboard(unsigned char key, unsigned char status)
{
    
}

void StateDraw::prepareState()
{
    btnDrawPlaneDone->appearIn();
}

void StateDraw::postState()
{
    btnDrawPlaneDone->appearOut();
}

void StateDraw::btnDrawPlaneDoneEvent(void* data)
{
    std::cout<<"btnDrawPlaneDoneEvent"<<std::endl;
    enterState(State::statePool[STATE_IDLE]);
}
