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

    void rotateCam(Vector3 rot) {rotate = rot; rotateTo = rot; anim=false;}
    void rotateCam(float rotx, float roty, float rotz)
    {
        rotate.x = rotx;
        rotate.y = roty;
        rotate.z = rotz;
        rotateTo = rotate;
        anim = false;
    }
    void setCamDist(float dist){distance = dist; distanceTo=dist; anim = false;}

    // rotate with animation
    void rotateCamTo(Vector3 rot) {rotateTo = rot; anim=true;}
    void rotateCamTo(float rotx, float roty, float rotz)
    {
        rotateTo.x = rotx;
        rotateTo.y = roty;
        rotateTo.z = rotz;
        rotateDelta = rotateTo - rotate;
        anim = true;
    }
    void setCamDistTo(float dist)
    {
        distanceTo = dist;
        distanceDelta = distanceTo-distance;
        anim = true;
    }

    void update(float timeDelta);
    Ray getRay(int mx, int my);

    float distance,distanceTo,distanceDelta;
    Vector3 rotate, rotateTo, rotateDelta;
    bool anim;

private:
    Camera();
    ~Camera();
    Camera(Camera const&);
    void operator=(Camera const&);
};
