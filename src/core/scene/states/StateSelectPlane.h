#include "State.h"

class StateSelectPlane:public State
{
public:
    StateSelectPlane()
    {
        stateID = CTRL_SELECT_CUR_PLANE;
        selectedPoints.clear();
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);
    void prepareState();
    void UIEvent(UINode* sender, int event);

    void render(float timeDelta);
};