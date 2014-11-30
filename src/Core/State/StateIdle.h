// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"

class StateIdle : public State
{
public:
    StateIdle()
    {
        stateID = STATE_IDLE;
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void prepareState();
};
