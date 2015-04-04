// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"
class UIButton;
class StateIdle : public State
{
public:
    StateIdle();
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void prepareState();
    void postState();
    enum{BTN_ID_STANDARD_VIEW, BTN_ID_UNDO, BTN_ID_DELETE_LINE};
protected:
    UIButton *btnStandardView, *btnUndo, *btnDeleteLine;
private:
    static void btnStandardViewEvent(void* data);
    static void btnUndoEvent(void* data);
    static void btnDeleteLineEvent(void* data);
};
