#pragma once
// base class for states
// here is a simple FSM
#include <iostream>
#include <GL/glut.h>

class Controller;
class Camera;
class State
{
public:
    State();
    virtual void MouseButton(int button, int state, int x, int y){};
    virtual void MouseMotion(int x, int y){};
    virtual void PassiveMotion(int x, int y){};
    virtual void Keyboard(unsigned char key, int x, int y){};
    virtual void render(float timeDelta){};

    static void enterState(State* state)
    {
        currState = state;
        std::cout<<"enterState: "<<state->stateID<<std::endl;
    }
    enum {CTRL_IDLE, CTRL_SELECT_CUR_PLANE, CTRL_DRAW};
    static State* currState;
    Controller *ctrl;
    Camera *camera;

protected:
    int stateID;

};

// idle state
class StateIdle:public State
{
public:
    StateIdle(){stateID = CTRL_IDLE;}
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);

    void render(float timeDelta);
    State* stateSelectPlane;
};

// select drawing plane state
class StateSelectPlane:public State
{
public:
    StateSelectPlane(){stateID = CTRL_SELECT_CUR_PLANE;}
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);

    void render(float timeDelta);
    State* stateDraw;
};


// draw state
class StateDraw:public State
{
public:
    StateDraw(){stateID = CTRL_DRAW;}
    void MouseButton(int button, int state, int x, int y);
    void MouseMotion(int x, int y);
    void PassiveMotion(int x, int y);
    void Keyboard(unsigned char key, int x, int y);

    void render(float timeDelta);
    State* stateIdle;
};
