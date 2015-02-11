// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateDraw.h"
#include "Core/Basic/Plane.h"

class DepthPeeling;
class TextureManager;

class StateDrawImpl : public StateDraw
{
public:
    StateDrawImpl();
    ~StateDrawImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    static void renderCurrentPlane();
    static void renderCurrentPoints();
    static Vector3 renderCurrentPlaneCenter;
    static Vector4 renderCurrentPlaneColor;
    static Plane currentPlane;
    static std::vector<Vector3> referencePoints;
    static TextureManager* textureManager;
};