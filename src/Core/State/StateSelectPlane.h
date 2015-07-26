// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "State.h"

class UIButton;
class UINode;

class StateSelectPlane : public State
{
public:
    StateSelectPlane();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void Keyboard(unsigned char key, unsigned char status);
    void prepareState();
    void postState();
    static std::vector<Vector3> selectedPoints;
    enum{BTN_ID_SELECT_VERTICAL, BTN_ID_SELECT_HORIZONTAL,
        BTN_ID_CONFIRM_PLANE, BTN_ID_CANCEL_PLANE};
private:
    void buildCurrentPlane();
    int selectPlaneMode;
    enum{SELECT_VERTICAL_PLANE, SELECT_HORIZONTAL_PLANE, SELECT_SLOPE};

protected:
    UIButton* btnSelectVerticalPlane, *btnSelectHorizontalPlane;
    UIButton *btnConfirmPlane, *btnCancelPlane;
    static void btnCancelPlaneEvent(void* data);
    static void btnConfirmPlaneEvent(void* data);
    static void btnSelectVerticalPlaneEvent(void* data);
    static void btnSelectHorizontalPlaneEvent(void* data);
};