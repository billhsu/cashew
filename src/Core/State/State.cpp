// Shipeng Xu
// billhsu.x@gmail.com

#include "State.h"
#include "Core/Camera/Camera.h"

State* State::statePool[STATE_ID_MAX];
State* State::currState = NULL;

State::State()
{
    mCamera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}