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
std::vector<LineSegment> Controller::redoLines;
std::vector<Controller::LineOperation> Controller::lineOperations;
std::vector<Controller::LineOperation> Controller::redoOperations;

Vector3 Controller::currPoint = Vector3(0, 0, 0);
bool Controller::bCurrPoint = false;

Vector3 Controller::rotate = Vector3(-30, 0, 0);

lua_State* Controller::luaState = NULL;

State* Controller::state_idle = NULL;
State* Controller::state_select_plane = NULL;
State* Controller::state_draw = NULL;
State* Controller::state_delete = NULL;
State* Controller::state_mirror = NULL;

int Controller::mirrorMode = MIRROR_MODE_NONE;

UI* Controller::GUI = NULL;
UIButton *Controller::btnDocNew = NULL, *Controller::btnDocOpen = NULL,
         *Controller::btnDocSave = NULL, *Controller::btnStandardView = NULL,
         *Controller::btnUndo = NULL, *Controller::btnRedo = NULL,
         *Controller::btnDeleteLine = NULL, *Controller::btnMirror = NULL;

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

void Controller::init() {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);

    GUI->resize(originWidth, originHeight);

    camera = &Camera::getInstance();
    camera->rotateCam(rotate);

    // Add buttons
    btnDocNew = GUI->addButton(BTN_ID_DOC_NEW, "BTN_ID_DOC_NEW", NULL, NULL);
    btnDocOpen = GUI->addButton(BTN_ID_DOC_OPEN, "BTN_ID_DOC_OPEN", NULL, NULL);
    btnDocSave = GUI->addButton(BTN_ID_DOC_SAVE, "BTN_ID_DOC_SAVE", NULL, NULL);
    btnStandardView =
        GUI->addButton(BTN_ID_STANDARD_VIEW, "BTN_ID_STANDARD_VIEW",
                       btnStandardViewEvent, NULL);
    btnUndo = GUI->addButton(BTN_ID_UNDO, "BTN_ID_UNDO", btnUndoEvent, NULL);
    btnRedo = GUI->addButton(BTN_ID_UNDO, "BTN_ID_REDO", btnRedoEvent, NULL);
    btnDeleteLine = GUI->addButton(BTN_ID_DELETE_LINE, "BTN_ID_DELETE_LINE",
                                   btnDeleteLineEvent, NULL);
    btnMirror =
        GUI->addButton(BTN_ID_MIRROR, "BTN_ID_MIRROR", btnMirrorEvent, NULL);
}
void Controller::MouseButton(int button, int state, int x, int y) {
    Controller::mouseButton = button;
    Controller::mouseState = state;
    Controller::mouseX = x;
    Controller::mouseY = y;
    UINode* node = GUI->MouseButton(button, state, x, y);
    if (node != NULL) {
        uiHold = 1;
        if (state == Mouse::MOUSE_ACTION_UP)
            uiHold = 0;
    } else {
        if (uiHold == 0)
            State::currState->MouseButton(button, state, x, y);
        uiHold = 0;
    }
}

void Controller::MouseRightDrag(int x, int y, int dx, int dy) {
    Controller::mouseX = x;
    Controller::mouseY = y;
    if (uiHold == 0)
        State::currState->MouseRightDrag(dx, dy);
}

void Controller::MouseLeftDrag(int x, int y, int dx, int dy) {
    Controller::mouseX = x;
    Controller::mouseY = y;
    if (uiHold == 0)
        State::currState->MouseLeftDrag(dx, dy);
}
void Controller::PassiveMotion(int x, int y) {
    // std::cout<<x<<" "<<y<<std::endl;
    Controller::mouseX = x;
    Controller::mouseY = y;
    Vector3 p;
    GUI->PassiveMotion(x, y);
    if (camera->getPoint(x, y, sketchLines, p)) {
        currPoint = p;
        bCurrPoint = true;
    } else
        bCurrPoint = false;
    if (uiHold == 0)
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
    GUI->update(timeDelta);
}

void Controller::render() {
    State::currState->render();
}

void Controller::resize(int _width, int _height) {
    windowWidth = _width;
    windowHeight = _height;
    GUI->resize(_width, _height);
    projection = cashew::gluPerspective(
        45.0f, windowWidth / (float)windowHeight, 0.1f, 10000.f);
    camera->setWindowWidth(windowWidth);
    camera->setWindowHeight(windowHeight);
    camera->setProjection(projection);
}

bool Controller::getCameraPoint(Vector3& p, const Plane& plane) {
    return camera->getPoint(mouseX, mouseY, sketchLines, p, plane);
}

Ray Controller::getCameraRay() {
    return camera->getRay(mouseX, mouseY);
}

void Controller::undoLastOperation() {
    if (lineOperations.size() > 0) {
        LineOperation lineOp = lineOperations.back();
        redoOperations.push_back(lineOp);
        lineOperations.pop_back();
        if (lineOp.operation == OPERATION_ADD_LINE) {
            for (int i = 0; i < sketchLines.size(); ++i) {
                if (lineOp.lineID == sketchLines[i].ID) {
                    redoLines.push_back(sketchLines[i]);
                    sketchLines.erase(sketchLines.begin() + i);
                    break;
                }
            }
        } else if (lineOp.operation == OPERATION_DELETE_LINE) {
            for (int i = 0; i < deletedLines.size(); ++i) {
                if (lineOp.lineID == deletedLines[i].ID) {
                    sketchLines.push_back(deletedLines[i]);
                    redoLines.push_back(deletedLines[i]);
                    deletedLines.erase(deletedLines.begin() + i);
                    break;
                }
            }
        }
    }
}

void Controller::redoLastOperation() {
    if (redoOperations.size() > 0) {
        LineOperation lineOp = redoOperations.back();
        redoOperations.pop_back();
        bool idFound = false;
        int idPos = 0;
        for (int i = 0; i < redoLines.size(); ++i) {
            if (lineOp.lineID == redoLines[i].ID) {
                idFound = true;
                idPos = i;
                break;
            }
        }
        if (!idFound)
            return;
        if (lineOp.operation == OPERATION_ADD_LINE) {
            addLine(redoLines[idPos]);
        } else if (lineOp.operation == OPERATION_DELETE_LINE) {
            delLine(redoLines[idPos]);
        }
        redoLines.erase(redoLines.begin() + idPos);
    }
}
void Controller::btnStandardViewEvent(void* data) {
    State::currState->UIEvent(btnStandardView, 0);
}
void Controller::btnUndoEvent(void* data) {
    undoLastOperation();
}

void Controller::btnRedoEvent(void* data) {
    redoLastOperation();
}

void Controller::btnDeleteLineEvent(void* data) {
    State::currState->UIEvent(btnDeleteLine, 0);
}

void Controller::btnMirrorEvent(void* data) {
    State::enterState(state_mirror);
}