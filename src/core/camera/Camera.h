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

    void rotateCam(Vector3 rot) {rotateCam(rot.x, rot.y, rot.z);}
    void rotateCam(float rotx, float roty, float rotz)
    {
        if(anim) return;

        if(rotx>=360.0f) rotx-=360.0f;
        else if (rotx<=-360.0f) rotx+=360.0f;
        if(roty>=360.0f) roty-=360.0f;
        else if (roty<=-360.0f) roty+=360.0f;
        if(rotz>=360.0f) rotz-=360.0f;
        else if (rotz<=-360.0f) rotz+=360.0f;

        rotate.x = rotx;
        rotate.y = roty;
        rotate.z = rotz;

        rotateTo = rotate;
    }
    void setCamDist(float dist)
    {
        if (dist<=0) return;
        if(anim) return;
        distance = dist;
        distanceTo=dist;
    }
    // rotate with animation
    void rotateCamTo(Vector3 rot) {rotateCamTo(rot.x, rot.y, rot.z);}
    void rotateCamTo(float rotx, float roty, float rotz)
    {
        if(rotx>=360.0f) rotx-=360.0f;
        else if (rotx<=-360.0f) rotx+=360.0f;
        if(roty>=360.0f) roty-=360.0f;
        else if (roty<=-360.0f) roty+=360.0f;
        if(rotz>=360.0f) rotz-=360.0f;
        else if (rotz<=-360.0f) rotz+=360.0f;

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
    int width,height;

private:
    Camera();
    ~Camera();
    Camera(Camera const&);
    void operator=(Camera const&);
    float ANIM_TIME_MS;
    float animTime;

    void drawFPS(float timeDelta);
    long lastTimeMS;
    int FPS;
    int lastFPS;
    char FPSchar[64];
};
