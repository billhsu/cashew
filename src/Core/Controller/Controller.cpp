/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "Core/State/State.h"
#include "Core/State/StateIdle.h"
#include "Core/State/StateSelectPlane.h"
//#include "Core/State/StateDeleteLine.h"
#include "Core/State/StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Scripting/luaUtility.h"
#include "Core/Graphics/Project.h"
#include "Core/Math/Quaternion.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"
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

State* Controller::state_idle = NULL;
State* Controller::state_select_plane = NULL;
State* Controller::state_draw = NULL;

UI* Controller::GUI = NULL;
UIButton *Controller::btnDocNew  = NULL, *Controller::btnDocOpen = NULL,
*Controller::btnDocSave = NULL;


Controller::Controller()
{
    std::cout <<"Controller Controller()"<<std::endl;
}

Controller::~Controller()
{
    delete state_idle;
    delete state_select_plane;
    delete state_draw;
    lua_close(luaState);
    std::cout <<"Controller ~Controller()"<<std::endl;
}


void Controller::init()
{
    luaState = luaL_newstate();
    luaL_openlibs( luaState );

    GUI->resize(originWidth, originHeight);

    camera = &Camera::getInstance();
    camera->rotateCam(rotate);
}
void Controller::MouseButton(int button, int state, int x, int y)
{
    Controller::mouseButton = button;
    Controller::mouseState = state;
    Controller::mouseX = x;
    Controller::mouseY = y;
    UINode* node = GUI->MouseButton(button, state, x, y);
    if(node!=NULL)
    {
        uiHold = 1;
    }
    else
    {
        uiHold = 0;
        State::currState->MouseButton(button, state, x, y);
    }
}

void Controller::MouseRightDrag(int dx, int dy)
{
    if(uiHold==0) State::currState->MouseRightDrag(dx, dy);
}

void Controller::MouseLeftDrag(int dx, int dy)
{
    if(uiHold==0) State::currState->MouseLeftDrag(dx, dy);
}
void Controller::PassiveMotion(int x, int y)
{
    //std::cout<<x<<" "<<y<<std::endl;
    Controller::mouseX = x;
    Controller::mouseY = y;
    Vector3 p;
    GUI->PassiveMotion(x, y);
    if(camera->getPoint(x, y, sketchLines, p))
    {
        currPoint = p;
        bCurrPoint = true;
    }
    else bCurrPoint = false;
    if(uiHold==0) State::currState->PassiveMotion(x, y);
}
void Controller::Keyboard(unsigned char key, unsigned char status)
{
    State::currState->Keyboard(key, status);
}

void Controller::update(float timeDelta)
{
    State::currState->update(timeDelta);
    modelView.identity();
    int result = camera->update(timeDelta);
    if(result == Camera::UPDATE_ANIM_DONE)
    {
        rotate = Quaternion::toEuler(camera->getRotateQuaternion());
    }
    State::currState->update(timeDelta);
    modelView = camera->getMatrix();
    GUI->update(timeDelta);
}

void Controller::render()
{
    State::currState->render();
}

void Controller::resize(int _width, int _height)
{
    windowWidth = _width;
    windowHeight = _height;
    GUI->resize(_width, _height);
    projection = cashew::gluPerspective(45.0f, windowWidth / (float)windowHeight, 0.1f, 10000.f);
    camera->setWindowWidth(windowWidth);
    camera->setWindowHeight(windowHeight);
    camera->setProjection(projection);
}

bool Controller::getCameraPoint(Vector3& p, const Plane& plane, bool mode)
{
    return camera->getPoint(mouseX, mouseY, sketchLines, p, plane, mode);
}

Ray Controller::getCameraRay()
{
    return camera->getRay(mouseX, mouseY);
}