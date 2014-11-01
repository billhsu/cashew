#pragma once
// base class for states
// here is a simple FSM
#include <iostream>
#include "glut.h"
#include <vector>
#include <assert.h>
#include "Vectors.h"
#include "LineSegment.h"

class Controller;
class Camera;
class UI;
class UIButton;
class UINode;

class State
{
public:
    State();
    virtual ~State(){};
    virtual void MouseButton(int button, int state, int x, int y){};
    virtual void MouseMotion(int x, int y){};
    virtual void PassiveMotion(int x, int y){};
    virtual void Keyboard(unsigned char key, int x, int y){};
    virtual void UIEvent(UINode* sender, int event){};
    virtual void prepareState(){};
    virtual void render(float timeDelta){};

    static void enterState(State* state)
    {
        currState = state;
        currState->prepareState();
        std::cout<<"enterState: "<<state->stateID<<std::endl;
    }
    enum {CTRL_IDLE, CTRL_DEL_LINE, CTRL_SELECT_CUR_PLANE, CTRL_DRAW, STATE_ID_MAX};
    static State* currState;
    Controller *ctrl;
    Camera *camera;

    int stateID;
    std::vector<Vector3> selectedPoints;
    Vector3 vCenter;
    Vector3 startPoint, endPoint;
    int internalState;
    static State* statePool[STATE_ID_MAX];
};