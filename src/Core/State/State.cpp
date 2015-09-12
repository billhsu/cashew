// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"

State* State::statePool[STATE_ID_MAX];
State* State::currState = NULL;

State::State() {
    mCamera = &Camera::getInstance();
    stateName = "default";
    luaL_dofile(Controller::luaState, getLuaInitFile());
}