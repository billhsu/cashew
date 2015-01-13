// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include "Core/Basic/Plane.h"
#include "Core/Math/Vectors.h"

class PlaneImpl : public Plane
{
    void prepareRenderData();
    void render();
};