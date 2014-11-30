/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "Core/State/State.h"
#include "Impl/State/StateIdleImpl.h"
//#include "Core/State/StateDeleteLine.h"
//#include "Core/State/StateSelectPlane.h"
//#include "Core/State/StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Impl/Scene/Scene.h"
#include "Core/Scripting/luaUtility.h"
#include "Core/Graphics/Project.h"
#include <iostream>
#include <fstream>
#include <stdint.h>

int Controller::windowWidth = 800;
int Controller::windowHeight = 600;

Matrix4 Controller::modelView;
Matrix4 Controller::projection;

int Controller::originWidth = 800;
int Controller::originHeight = 600;
int Controller::mouseX = 0;
int Controller::mouseY = 0;
int Controller::mouseButton;
int Controller::mouseState;
int Controller::lastMouseX = 0;
int Controller::lastMouseY = 0;

int Controller::uiHold = 0;

Plane Controller::currPlane = Plane();
bool Controller::enableLight = false;

std::vector<LineSegment> Controller::sketchLines;
std::vector<LineSegment> Controller::deletedLines;
std::vector<Controller::LineOperation> Controller::lineOperations;

Vector3 Controller::currPoint = Vector3(0,0,0);
bool Controller::bCurrPoint = false;

Vector3 Controller::rotate = Vector3(-30,0,0);

lua_State *Controller::luaState = NULL;

Controller::Controller()
{
    init();
    std::cout <<"Controller Controller()"<<std::endl;
}

Controller::~Controller()
{
    delete state_idle;
    lua_close(luaState);
    std::cout <<"Controller ~Controller()"<<std::endl;
}


void Controller::init()
{
    luaState = luaL_newstate();
    luaL_openlibs( luaState );

    for(int i=0; i < State::STATE_ID_MAX; ++i)
    {
        State::statePool[i] = NULL;
    }
    state_idle = new StateIdleImpl();
    camera = &Camera::getInstance();
    
    State::enterState(state_idle);

}
void Controller::MouseButton(int button, int state, int x, int y)
{
    Controller::mouseButton = button;
    Controller::mouseState = state;
    Controller::mouseX = x;
    Controller::mouseY = y;
//    if(node!=NULL)
    if(false)
    {
        uiHold = 1;
    }
    else
    {
        uiHold = 0;
        State::currState->MouseButton(button, state, x, y);
    }
}

void Controller::MouseMotion(int x, int y)
{
    Controller::mouseX = x;
    Controller::mouseY = y;
    if(uiHold==0) State::currState->MouseMotion(x, y);
}
void Controller::PassiveMotion(int x, int y)
{
    Controller::mouseX = x;
    Controller::mouseY = y;
    Vector3 p;
    
    if(camera->getPoint(x, y, sketchLines, p))
    {
        currPoint = p;
        bCurrPoint = true;
    }
    else bCurrPoint = false;
    if(uiHold==0) State::currState->PassiveMotion(x, y);
}
void Controller::Keyboard(unsigned char key)
{
    State::currState->Keyboard(key);
}

void Controller::update(float timeDelta)
{
    State::currState->update(timeDelta);
    modelView.identity();
    camera->rotateCam(rotate);
    camera->update(timeDelta);
    modelView = camera->getMatrix();
}

void Controller::render()
{
    State::currState->render();
}

void Controller::resize(int _width, int _heigth)
{
    windowWidth = _width;
    windowHeight = _heigth;
    projection = cashew::gluPerspective(45.0f, windowWidth / (float)windowHeight, 0.1f, 10000.f);
}
