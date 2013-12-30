/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include <iostream>
#include "Vectors.h"
#include "Ray.h"

class Camera
{
public:
    static Camera& getInstance()
    {
        static Camera instance;
        std::cout <<"Camera getInstance()"<<std::endl;
        return instance;
    }

    void update();

    float distance;
    Vector3 rotate, rotateDest;
    void setCamera();
    Ray getRay(int mx, int my);

private:
    Camera() {};
    Camera(Camera const&);
    void operator=(Camera const&);
};
