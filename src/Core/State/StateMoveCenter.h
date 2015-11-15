// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "State.h"
class lua_State;
class StateMoveCenter : public State {
   public:
    StateMoveCenter();
    void MouseButton(int button, int state, int x, int y);
    void MouseLeftDrag(int dx, int dy);
    void MouseRightDrag(int dx, int dy);
    void prepareState() {
    }
    void postState() {
    }
    void UIEvent(int event) {
    }

   protected:
    static int btnMoveCenterDoneEvent(lua_State* L);
};
