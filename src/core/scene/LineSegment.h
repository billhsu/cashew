/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <vector>
#include "Vectors.h"

class LineSegment
{
public:
    LineSegment(){};
    LineSegment(Vector3 a, Vector3 b)
    {
        points[0] = a;
        points[1] = b;
    };
    void render();

    Vector3 points[2];

};
