#include "State.h"

class StateDraw:public State
{
public:
    StateDraw()
    {
        stateID = CTRL_DRAW;
        internalState = IDLE;
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);
    void prepareState();
    void UIEvent(UINode* sender, int event);

    enum {IDLE, START_POINT_SELECTED};
};
