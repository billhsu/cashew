// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMoveCenter.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/UI/IMGUI.h"
#include "Core/Math/Matrices.h"

StateMoveCenter::StateMoveCenter() {
    stateID = STATE_MOVE_CENTER;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "move_center";
    lua_register(Controller::luaState, "moveCenterDone",
                 btnMoveCenterDoneEvent);
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}

void StateMoveCenter::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
}

void StateMoveCenter::MouseLeftDrag(int dx, int dy) {
    Vector3 moveVector =
        Vector3(-(float)dx / IMGUI::getBackingRatioX() / 20.0f, 0.0f,
                -(float)dy / IMGUI::getBackingRatioY() / 20.0f);
    Matrix4 modelView = mCamera->getModelView();
    modelView.invert();
    moveVector = modelView * moveVector;
    moveVector.y = 0;
    mCamera->setCamCenter(mCamera->getCamCenter() + moveVector);
}

void StateMoveCenter::MouseRightDrag(int dx, int dy) {
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}
int StateMoveCenter::btnMoveCenterDoneEvent(lua_State* L) {
    enterState(State::statePool[STATE_IDLE]);
    return 0;
}
