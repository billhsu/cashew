// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateDelete.h"

class DepthPeeling;
class TextureManager;

class StateDeleteImpl : public StateDelete
{
public:
    StateDeleteImpl();
    ~StateDeleteImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    TextureManager* textureManager;
};