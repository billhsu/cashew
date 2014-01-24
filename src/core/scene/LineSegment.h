/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <vector>
#include "../math/Vectors.h"

class LineSegment
{
public:
    LineSegment(){};
    LineSegment(Vector3 a, Vector3 b)
    {
        points[0] = a;
        points[1] = b;
    };
    void render(float r=0, float g=0, float b=1);

    Vector3 points[2];

};
