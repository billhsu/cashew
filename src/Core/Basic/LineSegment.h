// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include <vector>
#include "Core/Math/Vectors.h"
#include <iostream>

class LineSegment
{
public:
    LineSegment(){};
    LineSegment(Vector3 a, Vector3 b)
    {
        points[0] = a;
        points[1] = b;
    };
    static float distSegmentSegment( LineSegment S1, LineSegment S2);
    int ID;
    Vector3 points[2];
};
