/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "Controller.h"
#include "State.h"
State* State::currState;

Controller::Controller():width(400),height(300)
{
    sidle = new StateIdle();
    sselectPlane = new StateSelectPlane();
    sdraw = new StateDraw();

    sidle->stateSelectPlane = sselectPlane;
    sselectPlane->stateDraw = sdraw;
    sdraw->stateIdle = sidle;
    State::enterState(sidle);
    std::cout <<"Controller Controller()"<<std::endl;
}

Controller::~Controller()
{
    delete sidle;
    delete sselectPlane;
    delete sdraw;

    std::cout <<"Controller ~Controller()"<<std::endl;
}

void Controller::MouseButton(int button, int state, int x, int y)
{
    mouseButton = button;
    mouseState = state;
    State::currState->MouseButton(button, state, x, y);
}

void Controller::MouseMotion(int x, int y)
{
    State::currState->MouseMotion(x, y);
}
void Controller::PassiveMotion(int x, int y)
{
    State::currState->PassiveMotion(x, y);
}
void Controller::Keyboard(unsigned char key, int x, int y)
{
    State::currState->Keyboard(key, x, y);
}

void Controller::render(float timeDelta)
{
    State::currState->render(timeDelta);
}