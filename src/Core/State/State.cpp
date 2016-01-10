// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"
#include "Core/Camera/Camera.h"
#include "Core/Basic/Plane.h"
#include "Core/Controller/Controller.h"
#include "Core/UI/IMGUI.h"
#include "Core/Util/Intersect.h"

State* State::statePool[STATE_ID_MAX];
State* State::currState = NULL;

State::State() {
    mCamera = &Camera::getInstance();
    stateName = "default";
    if (luaL_dofile(Controller::luaState, getLuaInitFile().c_str())) {
        printf("%s\n", lua_tostring(Controller::luaState, -1));
    }
}

void State::update(float timeDelta) {
    if (luaL_dofile(Controller::luaState, getLuaUIFile().c_str())) {
        printf("%s\n", lua_tostring(Controller::luaState, -1));
    }
}

void State::enterState(State* state) {
    if (currState != NULL)
        currState->postState();
    currState = state;
    currState->prepareState();
    std::cout << state << " - ";
    std::cout << "enterState: [" << state->stateID << "] " << state->stateName
              << std::endl;
    IMGUI::getState().setActiveItem(0);
    IMGUI::getState().setHotItem(0);
}

Vector3 State::calcMoveCenterVector(int dx, int dy, const Plane& activePlane) {
    Ray rayCurrent = mCamera->getRay(Controller::mouseX, Controller::mouseY);
    Ray rayPrevious =
        mCamera->getRay(Controller::mouseX - dx, Controller::mouseY - dy);
    return intersect(rayPrevious, activePlane) -
           intersect(rayCurrent, activePlane);
}