#include "cashew/scene/states/StateDraw.h"
#include "cashew/scene/Controller.h"
#include "cashew/camera/Camera.h"
#include "cashew/UI/UI.h"
#include "cashew/UI/UINode.h"
#include "cashew/UI/UIButton.h"

// State Draw
void StateDraw::UIEvent(UINode* sender, int event)
{
    if(sender->nodeID == Controller::BTN_ID_STANDARD_VIEW && event == Controller::EVENT_BTN_CLICKED)
    {
        if(Controller::currPlane.N.dot(camera->getDirection())>0)
        {
            Controller::currPlane = - Controller::currPlane;
        }
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
            Quaternion::Z_NEG_AXIS);
        camera->rotateCamTo(q);
    }
    if(sender->nodeID == Controller::BTN_ID_DRAW_PLANE_DONE && event == Controller::EVENT_BTN_CLICKED)
    {
        Controller::btnDrawPlaneDone->appearOut();
        enterState(State::statePool[CTRL_IDLE]);
    }
}
void StateDraw::MouseButton(int button, int state, int x, int y)
{
    if(state==UI::CASHEW_MOUSE_DOWN)
    {
        if(button == UI::CASHEW_LEFT_BUTTON)
        {
            if(internalState==IDLE)
            {
                camera->getPoint(startPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                camera->getPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                internalState = START_POINT_SELECTED;
            }
        }
        if(button == UI::CASHEW_RIGHT_BUTTON)
        {
            Controller::lastMouseX=x;
            Controller::lastMouseY=y;
        }
        if(button == 3)
        {
            float dist = camera->distance;
            camera->setCamDist(dist-2);
        }
        if(button == 4)
        {
            float dist = camera->distance;
            camera->setCamDist(dist+2);
        }
    }
    if(state==UI::CASHEW_MOUSE_UP)
    {
        if(button == UI::CASHEW_LEFT_BUTTON)
        {
            if(internalState==START_POINT_SELECTED)
            {
                camera->getPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                LineSegment line = LineSegment(startPoint, endPoint);

                Vector3 startPointMirror = startPoint;
                Vector3 endPointMirror = endPoint;
                startPointMirror.x = -startPointMirror.x;
                endPointMirror.x   = -endPointMirror.x;
                LineSegment lineMirror = LineSegment(startPointMirror, endPointMirror);

                Controller::addLine(line);
                internalState = IDLE;
            }
        }
    }

}

void StateDraw::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==UI::CASHEW_MOUSE_DOWN)
    {
        if(Controller::mouseButton==UI::CASHEW_LEFT_BUTTON)
        {
            if(internalState == START_POINT_SELECTED)
                camera->getPoint(endPoint, Controller::currPlane);
        }
        if(Controller::mouseButton==UI::CASHEW_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateDraw::Keyboard(unsigned char key, int x, int y)
{

}

void StateDraw::prepareState()
{
    Controller::btnDrawPlaneDone->appearIn();
}
