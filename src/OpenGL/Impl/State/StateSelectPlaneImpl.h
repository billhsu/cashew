// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateSelectPlane.h"
#include "Core/Basic/Plane.h"

class DepthPeeling;
class StateSelectPlaneImpl : public StateSelectPlane
{
public:
    StateSelectPlaneImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    static void renderCurrentPlane();
    static Vector3 renderCurrentPlaneCenter;
    static Vector4 renderCurrentPlaneColor;
    static Plane currentPlane;
};