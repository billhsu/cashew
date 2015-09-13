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
    if (luaL_dofile(Controller::luaState, getLuaInitFile().c_str())) {
        printf("%s\n", lua_tostring(Controller::luaState, -1));
    }
}

void State::update(float timeDelta) {
    if (luaL_dofile(Controller::luaState, getLuaUIFile().c_str())) {
        printf("%s\n", lua_tostring(Controller::luaState, -1));
    }
}