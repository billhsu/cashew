#include "State.h"
#include "Controller.h"
#include "Camera.h"
#include "Scene.h"
#include "Plane.h"
#include "Quaternion.h"
#include "LineSegment.h"
#include "UI.h"
#include "UIButton.h"

State* State::statePool[STATE_ID_MAX];

State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}