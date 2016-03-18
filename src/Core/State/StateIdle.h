// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "State.h"
class UIButton;
class StateIdle : public State {
   public:
    StateIdle();
    void MouseButton(int button, int state, int x, int y);
    void MouseLeftDrag(int dx, int dy);
    void MouseRightDrag(int dx, int dy);
    void prepareState();
    void postState();

   private:
    enum { INTERNAL_STATE_IDLE, INTERNAL_STATE_MOUSE_DOWN };
    int internalState;
    Vector3 selectedPoint;
};
