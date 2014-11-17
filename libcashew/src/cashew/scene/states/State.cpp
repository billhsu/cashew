#include "cashew/scene/states/State.h"
#include "cashew/scene/Controller.h"
#include "cashew/camera/Camera.h"
#include "cashew/scene/Scene.h"
#include "cashew/scene/Plane.h"
#include "cashew/math/Quaternion.h"
#include "cashew/scene/LineSegment.h"
#include "cashew/UI/UI.h"
#include "cashew/UI/UIButton.h"

State* State::statePool[STATE_ID_MAX];

State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}