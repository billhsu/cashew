// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdle.h"
#include "StateSelectPlane.h"
#include "Core/Camera/Camera.h"
#include "Core/Controller/Controller.h"
#include "Core/Controller/Mouse.h"
#include "Core/Basic/Plane.h"
#include "Core/UI/UI.h"
#include "Core/UI/UIButton.h"

StateIdle::StateIdle()
{
    stateID = STATE_IDLE;
    assert(statePool[stateID] == NULL);
    statePool[stateID] = this;
    btnStandardView = Controller::GUI->addButton(stateID*100 + BTN_ID_STANDARD_VIEW, "BTN_ID_STANDARD_VIEW", btnStandardViewEvent, this);
    btnStandardView->setVisibility(false);
    btnUndo = Controller::GUI->addButton(stateID*100 + BTN_ID_UNDO, "BTN_ID_UNDO", btnUndoEvent, this);
    btnUndo->setVisibility(false);
    btnDeleteLine = Controller::GUI->addButton(stateID*100 + BTN_ID_DELETE_LINE, "BTN_ID_DELETE_LINE", btnDeleteLineEvent, this);
    btnDeleteLine->setVisibility(false);
}
void StateIdle::MouseButton(int button, int state, int x, int y)
{
    if(button == Mouse::MOUSE_SCROLL)
    {
        mCamera->setCamDist(mCamera->distance + 0.1f * state);
    }
    else if(button == Mouse::MOUSE_LEFT && state == Mouse::MOUSE_UP)
    {
        Vector3 v;
        mCamera->getPoint(x, y, Controller::sketchLines, v);
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints.clear();
        static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints.push_back(v);
        Plane::buildPlane(
                          static_cast<StateSelectPlane*>(State::statePool[STATE_SELECT_PLANE])->selectedPoints, Controller::currPlane);
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N,
                                              Quaternion::Z_NEG_AXIS);
        mCamera->setCamCenterTo(v);
        mCamera->rotateCamTo(q);
        enterState(State::statePool[STATE_SELECT_PLANE]);
    }
}

void StateIdle::MouseRightDrag(int dx, int dy)
{
    Controller::rotate.x -= dy;
    Controller::rotate.y += dx;
    mCamera->rotateCam(Controller::rotate);
}

void StateIdle::prepareState()
{
    btnStandardView->appearIn();
    btnUndo->appearIn();
    btnDeleteLine->appearIn();
}

void StateIdle::postState()
{
    btnStandardView->appearOut();
    btnUndo->appearOut();
    btnDeleteLine->appearOut();
}
void StateIdle::btnStandardViewEvent(void* data)
{
    StateIdle* self = static_cast<StateIdle*>(data);
    Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
    self->mCamera->setCamCenterTo(Vector3(0,0,0));
    self->mCamera->rotateCamTo(q);
}
void StateIdle::btnUndoEvent(void* data)
{
    Controller::undoLastOperation();
}
void StateIdle::btnDeleteLineEvent(void* data)
{
}