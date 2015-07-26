// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "Core/State/State.h"

class UIButton;
class StateDraw : public State
{
public:
    StateDraw();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void MouseLeftDrag(int dx, int dy);
    void Keyboard(unsigned char key, unsigned char status);
    void prepareState();
    void postState();
    Vector3 vCenter;
    std::vector<Vector3> selectedPoints;
    Vector3 startPoint, endPoint;
    
    int internalState;
    enum {STATE_DRAW_IDLE, STATE_DRAW_START_POINT_SELECTED};
    enum{BTN_ID_DRAW_PLANE_DONE};
protected:
    UIButton *btnDrawPlaneDone;
    static void btnDrawPlaneDoneEvent(void* data);
};
