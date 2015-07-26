// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "State.h"
class UIButton;
class StateMirror : public State {
public:
    StateMirror();
    void prepareState();
    void postState();
    enum {BTN_ID_MIRROR_X, BTN_ID_MIRROR_Y, BTN_ID_MIRROR_Z, BTN_ID_MIRROR_NONE};
protected:
    UIButton *btnMirrorX, *btnMirrorY, *btnMirrorZ, *btnMirrorNone;
};
