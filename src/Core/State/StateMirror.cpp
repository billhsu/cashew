// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMirror.h"
#include "Core/Controller/Controller.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateMirror::StateMirror() {
    stateID = STATE_MIRRPR;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    stateName = "mirror";
    luaL_dofile(Controller::luaState, getLuaInitFile());
    btnMirrorX =
        Controller::GUI->addButton(stateID * 100 + 100 + BTN_ID_MIRROR_X,
                                   "BTN_ID_MIRROR_X", btnMirrorXEvent, this);
    btnMirrorX->setVisibility(false);
    btnMirrorY =
        Controller::GUI->addButton(stateID * 100 + 100 + BTN_ID_MIRROR_Y,
                                   "BTN_ID_MIRROR_Y", btnMirrorYEvent, this);
    btnMirrorY->setVisibility(false);
    btnMirrorZ =
        Controller::GUI->addButton(stateID * 100 + 100 + BTN_ID_MIRROR_Z,
                                   "BTN_ID_MIRROR_Z", btnMirrorZEvent, this);
    btnMirrorZ->setVisibility(false);
    btnMirrorNone = Controller::GUI->addButton(
        stateID * 100 + 100 + BTN_ID_MIRROR_NONE, "BTN_ID_MIRROR_NONE",
        btnMirrorNoneEvent, this);
    btnMirrorNone->setVisibility(false);
}

void StateMirror::prepareState() {
    btnMirrorX->appearIn();
    btnMirrorY->appearIn();
    btnMirrorZ->appearIn();
    btnMirrorNone->appearIn();
}

void StateMirror::postState() {
    btnMirrorX->appearOut();
    btnMirrorY->appearOut();
    btnMirrorZ->appearOut();
    btnMirrorNone->appearOut();
}
void StateMirror::btnMirrorXEvent(void* data) {
    Controller::mirrorMode = Controller::MIRROR_MODE_X;
    enterState(State::statePool[STATE_IDLE]);
}

void StateMirror::btnMirrorYEvent(void* data) {
    Controller::mirrorMode = Controller::MIRROR_MODE_Y;
    enterState(State::statePool[STATE_IDLE]);
}

void StateMirror::btnMirrorZEvent(void* data) {
    Controller::mirrorMode = Controller::MIRROR_MODE_Z;
    enterState(State::statePool[STATE_IDLE]);
}

void StateMirror::btnMirrorNoneEvent(void* data) {
    Controller::mirrorMode = Controller::MIRROR_MODE_NONE;
    enterState(State::statePool[STATE_IDLE]);
}