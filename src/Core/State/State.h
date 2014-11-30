// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
// base class for states
// here is a simple FSM
#include <iostream>
#include <vector>
#include <assert.h>
#include "Core/Math/Vectors.h"
#include "Core/Basic/LineSegment.h"
class Camera;
class UINode;

class State
{
public:
    State();
    virtual ~State(){};
    virtual void MouseButton(int button, int state, int x, int y){};
    virtual void MouseMotion(int x, int y){};
    virtual void PassiveMotion(int x, int y){};
    virtual void Keyboard(unsigned char key){};
    virtual void UIEvent(UINode* sender, int event){};
    virtual void prepareState(){};
    virtual void update(float timeDelta){};
    static State* currState;
    static void enterState(State* state)
    {
        currState = state;
        currState->prepareState();
        std::cout<<"enterState: "<<state->stateID<<std::endl;
    }
    enum {STATE_IDLE, STATE_ID_MAX};
    static State* statePool[STATE_ID_MAX];

protected:
    Camera *mCamera;

    int stateID;
};