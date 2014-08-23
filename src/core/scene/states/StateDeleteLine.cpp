#include "StateDeleteLine.h"
#include "Controller.h"
#include "Camera.h"
#include "UINode.h"
#include "UIButton.h"

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
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            bCurLine = camera->getLine(line);
            if(bCurLine!=-1)
            {
                Controller::sketchLines.erase(Controller::sketchLines.begin()+bCurLine);
                bCurLine = -1;
                enterState(stateIdle);
            }
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

void StateDeleteLine::MouseMotion(int x, int y)
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

void StateDeleteLine::render(float timeDelta)
{
    if(bCurLine!=-1)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        //line.points[0]*=2.0f;
        line.render(1,0,0);
        glLineWidth(1);
    }
}

void StateDeleteLine::prepareState()
{
    Controller::btnDeleteLineDone->appearIn();
}