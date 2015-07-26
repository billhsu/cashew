// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMirror.h"
#include "Core/Controller/Controller.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateMirror::StateMirror()
{
    stateID = STATE_MIRRPR;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    btnMirrorX = Controller::GUI->addButton(stateID*100 + 100 + BTN_ID_MIRROR_X, "BTN_ID_MIRROR_X", NULL, this);
    btnMirrorX->setVisibility(false);
    btnMirrorY = Controller::GUI->addButton(stateID*100 + 100 + BTN_ID_MIRROR_Y, "BTN_ID_MIRROR_Y", NULL, this);
    btnMirrorY->setVisibility(false);
    btnMirrorZ = Controller::GUI->addButton(stateID*100 + 100 + BTN_ID_MIRROR_Z, "BTN_ID_MIRROR_Z", NULL, this);
    btnMirrorZ->setVisibility(false);
    btnMirrorNone = Controller::GUI->addButton(stateID*100 + 100 + BTN_ID_MIRROR_NONE, "BTN_ID_MIRROR_NONE", NULL, this);
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