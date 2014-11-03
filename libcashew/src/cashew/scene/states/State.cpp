#include "core/scene/states/State.h"
#include "core/scene/Controller.h"
#include "core/camera/Camera.h"
#include "core/scene/Scene.h"
#include "core/scene/Plane.h"
#include "core/math/Quaternion.h"
#include "core/scene/LineSegment.h"
#include "core/UI/UI.h"
#include "core/UI/UIButton.h"

State* State::statePool[STATE_ID_MAX];

State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}