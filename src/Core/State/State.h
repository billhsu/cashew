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
    virtual void MouseRightDrag(int dx, int dy){};
    virtual void MouseLeftDrag(int dx, int dy){};
    virtual void PassiveMotion(int x, int y){};
    virtual void Keyboard(unsigned char key, unsigned char status){};
    virtual void UIEvent(UINode* sender, int event){};
    virtual void prepareState(){};
    virtual void postState(){};
    virtual void update(float timeDelta){};
    virtual void render(){};
    static State* currState;
    static void enterState(State* state)
    {
        if(currState!=NULL) currState->postState();
        currState = state;
        currState->prepareState();
        std::cout<<state<<" - ";
        std::cout<<"enterState: "<<state->stateID<<std::endl;
    }
    enum {STATE_IDLE, STATE_SELECT_PLANE, STATE_DRAW, STATE_ID_MAX};
    static State* statePool[STATE_ID_MAX];

protected:
    Camera *mCamera;

    int stateID;
};