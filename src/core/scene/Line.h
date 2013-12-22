/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include <vector>
#include "Vectors.h"

class Line
{
public:
    Line(){};
    void addVec(Vector3 vec);
    void render();
private:
    std::vector<Vector3> vectorList;

};
