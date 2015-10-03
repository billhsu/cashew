// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "State.h"
class UIButton;
class StateIdle : public State {
   public:
    StateIdle();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void prepareState();
    void postState();
    void UIEvent(int event);
};
