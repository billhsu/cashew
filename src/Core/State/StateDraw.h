// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/State/State.h"

class StateDraw : public State
{
public:
    StateDraw()
    {
        stateID = STATE_DRAW;
        internalState = STATE_DRAW_IDLE;
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void MouseLeftDrag(int dx, int dy);
    void Keyboard(unsigned char key);
    void prepareState();
    Vector3 vCenter;
    Vector3 startPoint, endPoint;
    
    int internalState;
    enum {STATE_DRAW_IDLE, STATE_DRAW_START_POINT_SELECTED};
};
