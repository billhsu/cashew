#include "cashew/scene/states/StateDeleteLine.h"
#include "cashew/scene/Controller.h"
#include "cashew/camera/Camera.h"
#include "cashew/UI/UI.h"
#include "cashew/UI/UINode.h"
#include "cashew/UI/UIButton.h"

// State Delete Line
void StateDeleteLine::UIEvent(UINode* sender, int event)
{
    if(sender->nodeID == Controller::BTN_ID_DELETE_LINE_DONE && event == Controller::EVENT_BTN_CLICKED)
    {
        Controller::btnDeleteLineDone->appearOut();
        enterState(State::statePool[CTRL_IDLE]);
    }
}
void StateDeleteLine::MouseButton(int button, int state, int x, int y)
{    
    if(state==UI::CASHEW_MOUSE_DOWN)
    {
        if(button == UI::CASHEW_LEFT_BUTTON)
        {
            bCurLine = camera->getLine(line);
            if(bCurLine!=-1)
            {
                Controller::delLine(Controller::sketchLines[bCurLine]);
                bCurLine = -1;
            }
        }
        if(button==UI::CASHEW_RIGHT_BUTTON)
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

void StateDeleteLine::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==UI::CASHEW_MOUSE_DOWN)
    {
        if(Controller::mouseButton==UI::CASHEW_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateDeleteLine::PassiveMotion(int x, int y)
{
    bCurLine = camera->getLine(line);
}

void StateDeleteLine::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'b')
    {
        Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
        camera->setCamCenter(Vector3(0,0,0));
        camera->rotateCamTo(q);
    }
    if(key == 'x')
    {
        enterState(stateIdle);
    }
}

void StateDeleteLine::prepareState()
{
    Controller::btnDeleteLineDone->appearIn();
}