#include "StateSelectPlane.h"
#include "Controller.h"
#include "Camera.h"
#include "UINode.h"
#include "UIButton.h"

// State Select Plane
void StateSelectPlane::buildCurrentPlane()
{
    Vector3 planeVec = Vector3(0, 1, 0);
    if(selectedPoints.size() == 1) 
    {
        if(selectPlaneMode == SELECT_VERTICAL_PLANE)
        {
            planeVec = camera->getRay().GetDirection();
            planeVec.y = 0;
            planeVec.normalize();
        }
        else if (selectPlaneMode == SELECT_HORIZONTAL_PLANE)
        {
            planeVec = Vector3(0, 1, 0);
        }
    }
    else if(selectedPoints.size() == 2)
    {
        if(selectPlaneMode == SELECT_VERTICAL_PLANE)
        {
            planeVec = Vector3(0, 1, 0);
        }
        else if (selectPlaneMode == SELECT_SLOPE)
        {
            // TODO
        }
    }
    Plane::buildPlane(selectedPoints, Controller::currPlane, planeVec);
    Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                                          Quaternion::Z_NEG_AXIS);
    camera->rotateCamTo(q);
}
void StateSelectPlane::UIEvent(UINode* sender, int event)
{
    std::cout<<sender->nodeID<<" "<<event<<std::endl;
    if(sender->nodeID == Controller::BTN_ID_CONFIRM_PLANE && event == Controller::EVENT_BTN_CLICKED)
    {
        Vector3 center(0,0,0);
        for(int i=0;i<selectedPoints.size();++i)
            center += selectedPoints[i];
        center /= selectedPoints.size();
        
        State::statePool[CTRL_DRAW]->vCenter = center;
        State::statePool[CTRL_DRAW]->selectedPoints = selectedPoints;
        Controller::btnSelectVerticalPlane->appearOut();
        Controller::btnSelectHorizontalPlane->appearOut();
        Controller::btnConfirmPlane->appearOut();
        Controller::btnCancelPlane->appearOut();
        enterState(State::statePool[CTRL_DRAW]);
    }
    if(sender->nodeID == Controller::BTN_ID_CANCEL_PLANE && event == Controller::EVENT_BTN_CLICKED)
    {
        Controller::btnSelectVerticalPlane->appearOut();
        Controller::btnSelectHorizontalPlane->appearOut();
        Controller::btnConfirmPlane->appearOut();
        Controller::btnCancelPlane->appearOut();
        enterState(State::statePool[CTRL_IDLE]);
    }
    if(sender->nodeID == Controller::BTN_ID_SELECT_VERTICAL && event == Controller::EVENT_BTN_CLICKED)
    {
        selectPlaneMode = SELECT_VERTICAL_PLANE;
        buildCurrentPlane();
    }
    if(sender->nodeID == Controller::BTN_ID_SELECT_HORIZONTAL && event == Controller::EVENT_BTN_CLICKED)
    {
        if(selectedPoints.size() == 1) selectPlaneMode = SELECT_HORIZONTAL_PLANE;
        else if(selectedPoints.size() == 2) selectPlaneMode = SELECT_SLOPE;
        buildCurrentPlane();
    }
}

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
            if(selectedPoints.size() == 2)
            {
                selectPlaneMode = SELECT_VERTICAL_PLANE;
            }
            buildCurrentPlane();
            Controller::currPlane.printStatus();
            
            Vector3 center(0,0,0);
            for(int i=0;i<selectedPoints.size();++i)
                center += selectedPoints[i];
            center /= selectedPoints.size();

            camera->setCamCenterTo(center);
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
