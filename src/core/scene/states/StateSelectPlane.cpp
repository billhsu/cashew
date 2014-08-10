#include "StateSelectPlane.h"
#include "Controller.h"
#include "Camera.h"
#include "UINode.h"
#include "UIButton.h"

// State Select Plane
void StateSelectPlane::MouseButton(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            Vector3 v;
            camera->getPoint(v);
            std::cout<<v<<std::endl;
            // three selected points should be different 
            for(int i=0; i<selectedPoints.size();++i) 
            {
                if(v==selectedPoints[i]) return;
            }
            selectedPoints.push_back(v);
            Plane::buildPlane(selectedPoints, Controller::currPlane);
            Controller::currPlane.printStatus();
            Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                Quaternion::Z_NEG_AXIS);
            Vector3 center(0,0,0);
            for(int i=0;i<selectedPoints.size();++i)
                center += selectedPoints[i];
            center /= selectedPoints.size();

            camera->setCamCenterTo(center);
            camera->rotateCamTo(q);
            if(selectedPoints.size()==3) 
            {
                State::statePool[CTRL_DRAW]->vCenter = center;
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
}

void StateSelectPlane::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateSelectPlane::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'x')
    {
        Vector3 center(0,0,0);
        for(int i=0;i<selectedPoints.size();++i)
            center += selectedPoints[i];
        center /= selectedPoints.size();
        
        State::statePool[CTRL_DRAW]->vCenter = center;
        State::statePool[CTRL_DRAW]->selectedPoints = selectedPoints;
        enterState(State::statePool[CTRL_DRAW]);
    }
    if(key =='b')
    {
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
        Quaternion::Z_NEG_AXIS);
        camera->rotateCamTo(q);
    }
}
void StateSelectPlane::prepareState()
{
    Controller::btnSelectVerticalPlane->appearIn();
    Controller::btnSelectHorizontalPlane->appearIn();
    Controller::btnConfirmPlane->appearIn();
    Controller::btnCancelPlane->appearIn();
}
void StateSelectPlane::render(float timeDelta)
{
    Vector3 center(0,0,0);
    for(int i=0;i<selectedPoints.size();++i)
        center += selectedPoints[i];
    center /= selectedPoints.size();
    float color[4] = {0.3,0.3,0.3,0.3};
    Controller::currPlane.drawPlane(center, 20, color);
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    for(int i = 0; i<selectedPoints.size(); ++i)
    {
        glVertex3fv(selectedPoints[i].cell);
    }
    glEnd();
    glPointSize(1);
}
