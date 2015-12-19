// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateDraw.h"
#include "Core/Basic/Plane.h"

class DepthPeeling;
class TextureManager;

class StateDrawImpl : public StateDraw {
   public:
    StateDrawImpl();
    ~StateDrawImpl();
    void render();

   private:
    DepthPeeling* depthPeeling;
    static void renderCurrentPlane(void* data);
    static void renderCurrentPoints(void* data);
    void renderCurrentLine();
    Vector3 renderCurrentPlaneCenter;
    Vector4 renderCurrentPlaneColor;
    Plane currentPlane;
    TextureManager* textureManager;
};