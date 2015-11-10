// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "Core/State/State.h"
#include "Core/Basic/SketchLine.h"

class StateDraw : public State {
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

    static int internalState;
    enum { STATE_DRAW_IDLE, STATE_DRAW_START_POINT_SELECTED };
    enum { BTN_ID_DRAW_PLANE_DONE };

   private:
    void addLineWithMirror();
    static int btnDrawPlaneDoneEvent(lua_State* L);
    SketchLine currentLine, currentLineMirrorX, currentLineMirrorY,
        currentLineMirrorZ;
};
