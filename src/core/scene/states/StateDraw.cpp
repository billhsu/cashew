#include "StateDraw.h"
#include "Controller.h"
#include "Camera.h"
#include "UINode.h"
#include "UIButton.h"

// State Draw
void StateDraw::UIEvent(UINode* sender, int event)
{
    if(sender->nodeID == Controller::BTN_ID_DRAW_PLANE_DONE && event == Controller::EVENT_BTN_CLICKED)
    {
        Controller::btnDrawPlaneDone->appearOut();
        enterState(State::statePool[CTRL_IDLE]);
    }
}
void StateDraw::MouseButton(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if(internalState==IDLE)
            {
                camera->getPoint(startPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                camera->getPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                internalState = START_POINT_SELECTED;
            }
        }
        if(button == GLUT_RIGHT_BUTTON)
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
    if(state==GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
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

                Controller::sketchLines.push_back(line);
                //Controller::sketchLines.push_back(lineMirror);
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

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_LEFT_BUTTON)
        {
            if(internalState == START_POINT_SELECTED)
                camera->getPoint(endPoint, Controller::currPlane);
        }
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateDraw::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'b')
    {
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
        Quaternion::Z_NEG_AXIS);
        camera->rotateCamTo(q);
    }
}

void StateDraw::render(float timeDelta)
{
    float color[4] = {0.4,0.4,0.4,0.7};
    Controller::currPlane.drawPlane(vCenter, 20, color);

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1,1,0);
        glVertex3fv(vCenter.cell);
    glEnd();

    if(internalState == START_POINT_SELECTED)
    {
        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(1,0,1);
            glVertex3fv(startPoint.cell);
            glVertex3fv(endPoint.cell);
        glEnd();
        glLineWidth(3);
        glColor3f(1,1,0);
        glBegin(GL_LINES);
            glVertex3fv(startPoint.cell);
            glVertex3fv(endPoint.cell);
        glEnd();
    }
    
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    for(int i = 0; i<selectedPoints.size(); ++i)
    {
        glVertex3fv(selectedPoints[i].cell);
    }
    glEnd();
    glPointSize(1);

    glLineWidth(1);

}

void StateDraw::prepareState()
{
    Controller::btnDrawPlaneDone->appearIn();
}
