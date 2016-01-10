// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDelete.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include "Core/Basic/SketchLine.h"

StateDelete::StateDelete() {
    stateID = STATE_DELETE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "delete";
    lua_register(Controller::luaState, "deleteLinesDone", btnDeleteDoneEvent);
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}
void StateDelete::MouseButton(int button, int state, int x, int y) {
    if (button == Mouse::MOUSE_BUTTON_SCROLL) {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    if (Controller::bMoveCenterMode) {
        return;
    }
    if (button == Mouse::MOUSE_BUTTON_LEFT && state == Mouse::MOUSE_ACTION_UP) {
        if (Controller::bCurrLine) {
            SketchLine* sketchLine =
                SketchLine::lineSegmentToSkectLine(Controller::currLine.ID);
            if (sketchLine == NULL) {
                return;
            }
            SketchLine::deleteSketchLine(*sketchLine);
            Controller::bCurrLine = false;
        }
    }
}
void StateDelete::PassiveMotion(int x, int y) {
}
void StateDelete::MouseRightDrag(int dx, int dy) {
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateDelete::prepareState() {
}

void StateDelete::postState() {
}
void StateDelete::UIEvent(int event) {
    if (event == Controller::BTN_ID_STANDARD_VIEW) {
        Quaternion q = Quaternion::fromEuler(Vector3(-90, 0, 0));
        mCamera->setCamCenterTo(Vector3(0, 0, 0));
        mCamera->rotateCamTo(q);
    }
}

int StateDelete::btnDeleteDoneEvent(lua_State* L) {
    enterState(State::statePool[STATE_IDLE]);
    return 0;
}
