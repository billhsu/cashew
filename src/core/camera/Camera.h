/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include <iostream>
#include "Vectors.h"
#include "Ray.h"
#include "Quaternion.h"

class Camera
{
public:
    static Camera& getInstance()
    {
        static Camera instance;
        std::cout <<"Camera getInstance()"<<std::endl;
        return instance;
    }

    void rotateCam(Quaternion rot)
    {
        rotate = rot;
    }
    void setCamDist(float dist)
    {
        if (dist<=0) return;
        if(anim) return;
        distance = dist;
        distanceTo=dist;
    }
    // rotate with animation
    void rotateCamTo(Quaternion rot)
    {
        rotateTo = rot;
        anim = true;
    }
    void setCamDistTo(float dist)
    {
        distanceTo = dist;
        distanceDelta = distanceTo-distance;
        anim = true;
    }

    void update(float timeDelta);
    Ray getRay();
    bool getPoint(Vector3& p);
    Quaternion getQuaternion() {return rotate;}


    float distance,distanceTo,distanceDelta;
    bool anim;
    int width,height;

private:
    Camera();
    ~Camera();
    Camera(Camera const&);
    void operator=(Camera const&);
    float ANIM_TIME_MS;
    float animTime;
    Quaternion rotate, rotateTo;

    void drawFPS(float timeDelta);
    long lastTimeMS;
    int FPS;
    int lastFPS;
    char FPSchar[64];
};
