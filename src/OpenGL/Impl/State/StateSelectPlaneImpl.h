// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateSelectPlane.h"
#include "Core/Basic/Plane.h"

class DepthPeeling;
class TextureManager;
class StateSelectPlaneImpl : public StateSelectPlane
{
public:
    StateSelectPlaneImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    static void renderCurrentPlane(void* data);
    static void renderCurrentPoints(void* data);
    static Vector3 renderCurrentPlaneCenter;
    static Vector4 renderCurrentPlaneColor;
    static Plane currentPlane;
    static TextureManager* textureManager;
};