#include "State.h"

class StateIdle:public State
{
public:
    StateIdle()
    {
        stateID = CTRL_IDLE;
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);
    void UIEvent(UINode* sender, int event);

    void render(float timeDelta);
};
