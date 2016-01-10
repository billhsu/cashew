// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMirror.h"
#include "Core/Controller/Controller.h"

StateMirror::StateMirror() {
    stateID = STATE_MIRROR;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "mirror";
    lua_register(Controller::luaState, "mirrorXAxis", btnMirrorXEvent);
    lua_register(Controller::luaState, "mirrorYAxis", btnMirrorYEvent);
    lua_register(Controller::luaState, "mirrorZAxis", btnMirrorZEvent);
    lua_register(Controller::luaState, "mirrorAxisSelectionDone",
                 btnMirrorDoneEvent);
    luaL_dofile(Controller::luaState, getLuaInitFile().c_str());
}

void StateMirror::prepareState() {
}

void StateMirror::postState() {
}
int StateMirror::btnMirrorXEvent(lua_State* L) {
    bool checked = lua_toboolean(L, 1);
    if (checked) {
        Controller::mirrorMode =
            Controller::mirrorMode | Controller::MIRROR_MODE_X;
    } else {
        Controller::mirrorMode =
            Controller::mirrorMode & (~Controller::MIRROR_MODE_X);
    }

    return 0;
}

int StateMirror::btnMirrorYEvent(lua_State* L) {
    bool checked = lua_toboolean(L, 1);
    if (checked) {
        Controller::mirrorMode =
            Controller::mirrorMode | Controller::MIRROR_MODE_Y;
    } else {
        Controller::mirrorMode =
            Controller::mirrorMode & (~Controller::MIRROR_MODE_Y);
    }
    return 0;
}

int StateMirror::btnMirrorZEvent(lua_State* L) {
    bool checked = lua_toboolean(L, 1);
    if (checked) {
        Controller::mirrorMode =
            Controller::mirrorMode | Controller::MIRROR_MODE_Z;
    } else {
        Controller::mirrorMode =
            Controller::mirrorMode & (~Controller::MIRROR_MODE_Z);
    }
    return 0;
}

int StateMirror::btnMirrorDoneEvent(lua_State* L) {
    if (previousState->getStateID() == STATE_DRAW) {
        returnPreviousState();
    } else {
        enterState(statePool[STATE_IDLE]);
    }
    return 0;
}
