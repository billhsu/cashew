// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "State.h"
/*
 THIS CLASS IS DEPRECATED.
 PLEASE DO NOT USE THIS FILE OR ADD ANY NEW FEATURES.
 */

class UIButton;
class UINode;

class StateSelectPlane : public State {
   public:
    StateSelectPlane();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void Keyboard(unsigned char key, unsigned char status);
    void prepareState();
    void postState();
    static std::vector<Vector3> selectedPoints;

   private:
    void buildCurrentPlane();
    int selectPlaneMode;
    enum { SELECT_VERTICAL_PLANE, SELECT_HORIZONTAL_PLANE, SELECT_SLOPE };
    static int btnCancelPlaneEvent(lua_State* L);
    static int btnConfirmPlaneEvent(lua_State* L);
    static int btnSelectVerticalPlaneEvent(lua_State* L);
    static int btnSelectHorizontalPlaneEvent(lua_State* L);

   protected:
};