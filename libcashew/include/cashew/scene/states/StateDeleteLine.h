#include "State.h"

class StateDeleteLine:public State
{
public:
    StateDeleteLine()
    {
        stateID = CTRL_DEL_LINE;
        bCurLine = false;
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);
    void prepareState();
    void UIEvent(UINode* sender, int event);
    State* stateIdle;
    int bCurLine;
    LineSegment line;

};