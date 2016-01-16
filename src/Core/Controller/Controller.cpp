/*
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "Mouse.h"

#include "Core/State/State.h"
#include "Core/State/StateIdle.h"
#include "Core/State/StateSelectPlane.h"
#include "Core/State/StateDelete.h"
#include "Core/State/StateDraw.h"
#include "Core/Camera/Camera.h"
#include "Core/Scripting/luaUtility.h"
#include "Core/Graphics/Project.h"
#include "Core/Math/Quaternion.h"
#include "Core/UI/IMGUI.h"
#include "Core/Basic/SketchLine.h"
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

Plane Controller::currPlane = Plane();
bool Controller::enableLight = false;

Vector3 Controller::currPoint = Vector3(0, 0, 0);
bool Controller::bCurrPoint = false;

LineSegment Controller::currLine;
bool Controller::bCurrLine = false;
bool Controller::bMoveCenterMode = false;
bool Controller::bPencilMode = true;

Vector3 Controller::rotate = Vector3(-30, 0, 0);

lua_State* Controller::luaState = NULL;

State* Controller::state_idle = NULL;
State* Controller::state_select_plane = NULL;
State* Controller::state_draw = NULL;
State* Controller::state_delete = NULL;
State* Controller::state_mirror = NULL;

int Controller::mirrorMode = MIRROR_MODE_NONE;

Controller::Controller() {
    std::cout << "Controller Controller()" << std::endl;
}

Controller::~Controller() {
    delete state_idle;
    delete state_select_plane;
    delete state_draw;
    delete state_delete;
    delete state_mirror;
    lua_close(luaState);
    std::cout << "Controller ~Controller()" << std::endl;
}

static int btnStandardViewEvent(lua_State* L);
static int btnMoveCenterEvent(lua_State* L);
static int btnPencilModeEvent(lua_State* L);
static int btnUndoEvent(lua_State* L);
static int btnRedoEvent(lua_State* L);
static int btnDeleteLineEvent(lua_State* L);
static int btnMirrorEvent(lua_State* L);

void Controller::init() {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);
    IMGUI::init(luaState);
    IMGUI::resize(originWidth, originHeight);

    camera = &Camera::getInstance();
    camera->rotateCam(rotate);
    lua_register(luaState, "standardView", btnStandardViewEvent);
    lua_register(luaState, "moveCenter", btnMoveCenterEvent);
    lua_register(luaState, "pencilMode", btnPencilModeEvent);
    lua_register(luaState, "undo", btnUndoEvent);
    lua_register(luaState, "redo", btnRedoEvent);
    lua_register(luaState, "deleteLine", btnDeleteLineEvent);
    lua_register(luaState, "mirrorMode", btnMirrorEvent);
}
void Controller::MouseButton(int button, int state, int x, int y) {
    Controller::mouseButton = button;
    Controller::mouseState = state;
    Controller::mouseX = x;
    Controller::mouseY = y;
    static bool UIHot = false;
    if (state == Mouse::MOUSE_ACTION_DOWN) {
        UIHot = IMGUI::isUIHot();
    } else if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        UIHot = false;
    }
    if (!UIHot) {
        State::currState->MouseButton(button, state, x, y);
    }
}

void Controller::MouseRightDrag(int x, int y, int dx, int dy) {
    Controller::mouseX = x;
    Controller::mouseY = y;
    if (!IMGUI::isUIHot()) {
        State::currState->MouseRightDrag(dx, dy);
    }
}

void Controller::MouseLeftDrag(int x, int y, int dx, int dy) {
    Controller::mouseX = x;
    Controller::mouseY = y;
    if (!IMGUI::isUIHot()) {
        State::currState->MouseLeftDrag(dx, dy);
    }
}
void Controller::PassiveMotion(int x, int y) {
    Controller::mouseX = x;
    Controller::mouseY = y;
    Vector3 p;
    if (camera->getPoint(x, y, SketchLine::getGlobalLineSegments(), p)) {
        currPoint = p;
        bCurrPoint = true;
    } else {
        bCurrPoint = false;
    }
    LineSegment line;
    if (camera->getLine(x, y, SketchLine::getGlobalLineSegments(), line) !=
        -1) {
        currLine = line;
        bCurrLine = true;
    } else {
        bCurrLine = false;
    }
    State::currState->PassiveMotion(x, y);
}
void Controller::Keyboard(unsigned char key, unsigned char status) {
    State::currState->Keyboard(key, status);
}

void Controller::update(float timeDelta) {
    modelView.identity();
    int result = camera->update(timeDelta);
    if (result == Camera::UPDATE_ANIM_DONE) {
        rotate = Quaternion::toEuler(camera->getRotateQuaternion());
    }
    State::currState->update(timeDelta);
    modelView = camera->getMatrix();
    IMGUI::update(timeDelta);
}

void Controller::render() {
    State::currState->render();
}

void Controller::resize(int _width, int _height) {
    windowWidth = _width;
    windowHeight = _height;
    IMGUI::resize(_width, _height);
    projection = cashew::gluPerspective(
        45.0f, windowWidth / (float)windowHeight, 0.1f, 10000.f);
    camera->setWindowWidth(windowWidth);
    camera->setWindowHeight(windowHeight);
    camera->setProjection(projection);
}

bool Controller::getCameraPoint(Vector3& p, const Plane& plane) {
    return camera->getPoint(mouseX, mouseY, SketchLine::getGlobalLineSegments(),
                            p, plane);
}

Ray Controller::getCameraRay() {
    return camera->getRay(mouseX, mouseY);
}

void Controller::undoLastOperation() {
    SketchLine::undoLastOperation();
}

void Controller::redoLastOperation() {
    SketchLine::redoLastOperation();
}
int btnStandardViewEvent(lua_State* L) {
    State::currState->UIEvent(Controller::BTN_ID_STANDARD_VIEW);
    return 0;
}
int btnMoveCenterEvent(lua_State* L) {
    bool checked = lua_toboolean(L, 1);
    Controller::bMoveCenterMode = !checked;
    return 0;
}

int btnPencilModeEvent(lua_State* L) {
    bool checked = lua_toboolean(L, 1);
    Controller::bPencilMode = checked;
    return 0;
}

int btnUndoEvent(lua_State* L) {
    Controller::undoLastOperation();
    return 0;
}

int btnRedoEvent(lua_State* L) {
    Controller::redoLastOperation();
    return 0;
}

int btnDeleteLineEvent(lua_State* L) {
    State::enterState(Controller::state_delete);
    return 0;
}

int btnMirrorEvent(lua_State* L) {
    State::enterState(Controller::state_mirror);
    return 0;
}