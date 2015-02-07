// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateSelectPlane.h"
class DepthPeeling;
class StateSelectPlaneImpl : public StateSelectPlane
{
public:
    StateSelectPlaneImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
};