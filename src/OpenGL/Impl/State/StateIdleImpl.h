// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateIdle.h"
class DepthPeeling;
class TextureManager;
class StateIdleImpl : public StateIdle
{
public:
    StateIdleImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    TextureManager* textureManager;
};