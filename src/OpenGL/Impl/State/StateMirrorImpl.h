// Shipeng Xu
// billhsu.x@gmail.com

#pragma once

#include "Core/State/StateMirror.h"
class DepthPeeling;
class TextureManager;
class StateMirrorImpl : public StateMirror
{
public:
    StateMirrorImpl();
    ~StateMirrorImpl();
    void render();
private:
    DepthPeeling* depthPeeling;
    TextureManager* textureManager;
};