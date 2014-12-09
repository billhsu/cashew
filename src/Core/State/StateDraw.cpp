// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"

void StateDraw::MouseButton(int button, int state, int x, int y)
{
    if(state == Controller::MOUSE_DOWN)
    {
        if(button == Controller::MOUSE_LEFT)
        {
            if(internalState==STATE_DRAW_IDLE)
            {
                Controller::getInstance().getCameraPoint(startPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                Controller::getInstance().getCameraPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                internalState = STATE_DRAW_START_POINT_SELECTED;
            }
        }
    }
    if(state == Controller::MOUSE_UP)
    {
        if(button == Controller::MOUSE_LEFT)
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
                internalState = STATE_DRAW_IDLE;
            }
        }
    }

}

void StateDraw::MouseLeftDrag(int dx, int dy)
{
    if(internalState == STATE_DRAW_START_POINT_SELECTED)
        Controller::getInstance().getCameraPoint(endPoint, Controller::currPlane, Camera::GETPOINT_3D);
}

void StateDraw::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateDraw::Keyboard(unsigned char key)
{

}

void StateDraw::prepareState()
{
}
