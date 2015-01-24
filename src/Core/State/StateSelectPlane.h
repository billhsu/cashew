// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"

class StateSelectPlane : public State
{
public:
    StateSelectPlane()
    {
        stateID = STATE_SELECT_PLANE;
        selectedPoints.clear();
        assert(statePool[stateID] == NULL);
        statePool[stateID] = this;
        selectPlaneMode = SELECT_HORIZONTAL_PLANE;
    }
    void MouseButton(int button, int state, int x, int y);
    void MouseRightDrag(int dx, int dy);
    void Keyboard(unsigned char key, unsigned char status);
    void prepareState();
    std::vector<Vector3> selectedPoints;

private:
    void buildCurrentPlane();
    int selectPlaneMode;
    enum{SELECT_VERTICAL_PLANE, SELECT_HORIZONTAL_PLANE, SELECT_SLOPE};
};