// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#include "State.h"
class UIButton;
class StateDelete : public State {
   public:
    StateDelete();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void PassiveMotion(int x, int y);
    void prepareState();
    void postState();
    void UIEvent(int event);
    enum { BTN_ID_DELETE_LINE_DONE };

   protected:
    static int btnDeleteDoneEvent(lua_State* L);
};
