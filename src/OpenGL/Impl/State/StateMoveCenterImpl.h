// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/State/StateMoveCenter.h"
class DepthPeeling;
class TextureManager;
class StateMoveCenterImpl : public StateMoveCenter {
   public:
    StateMoveCenterImpl();
    void render();

   private:
    DepthPeeling* depthPeeling;
    TextureManager* textureManager;
};