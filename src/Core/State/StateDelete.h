// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"
class UIButton;
class StateDelete : public State
{
public:
    StateDelete();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void prepareState();
    void postState();
    void UIEvent(UINode* sender, int event);
};
