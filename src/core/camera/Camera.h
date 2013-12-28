/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "Vectors.h"
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

    Vector3 eye,eyeDest;
    Vector3 lookat,lookatDest;
    Vector3 up,upDest;

private:
    Camera() {};
    Camera(Camera const&);
    void operator=(Camera const&);
};
