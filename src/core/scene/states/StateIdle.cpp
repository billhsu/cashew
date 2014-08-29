#include "StateIdle.h"
#include "Controller.h"
#include "Camera.h"
#include "UINode.h"
#include "UIButton.h"

// State Idle
void StateIdle::UIEvent(UINode* sender, int event)
{
    if(sender->nodeID == Controller::BTN_ID_STANDARD_VIEW && event == Controller::EVENT_BTN_CLICKED)
    {
        Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
        camera->setCamCenter(Vector3(0,0,0));
        camera->rotateCamTo(q);
    }
    if(sender->nodeID == Controller::BTN_ID_DELETE_LINE && event == Controller::EVENT_BTN_CLICKED)
    {
        Controller::btnDeleteLine->appearOut();
        Controller::btnStandardView->appearOut();
        Controller::btnUndo->appearOut();
        Controller::btnMirror->appearOut();
        enterState(State::statePool[CTRL_DEL_LINE]);
    }
    if(sender->nodeID == Controller::BTN_ID_UNDO && event == Controller::EVENT_BTN_CLICKED)
    {
        // TODO: implement undo
    }
}
void StateIdle::MouseButton(int button, int state, int x, int y)
{    
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            State::statePool[CTRL_SELECT_CUR_PLANE]->selectedPoints.clear();
            Vector3 v;
            camera->getPoint(v);
            std::cout<<v<<std::endl;
            State::statePool[CTRL_SELECT_CUR_PLANE]->selectedPoints.push_back(v);
            Plane::buildPlane(
                State::statePool[CTRL_SELECT_CUR_PLANE]->selectedPoints, Controller::currPlane);
            Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                Quaternion::Z_NEG_AXIS);
            camera->setCamCenterTo(v);
            camera->rotateCamTo(q);
            enterState(State::statePool[CTRL_SELECT_CUR_PLANE]);
        }

        if(button==GLUT_RIGHT_BUTTON)
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

void StateIdle::MouseMotion(int x, int y)
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

void StateIdle::prepareState()
{
    Controller::btnDeleteLine->appearIn();
    Controller::btnStandardView->appearIn();
    Controller::btnUndo->appearIn();
    Controller::btnMirror->appearIn();
}

void StateIdle::Keyboard(unsigned char key, int x, int y)
{

}