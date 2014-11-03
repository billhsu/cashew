/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include <iostream>
#include "../math/Vectors.h"
#include "../scene/Ray.h"
#include "../scene/Plane.h"
#include "../scene/LineSegment.h"
#include "../math/Quaternion.h"

class Camera
{
public:
    static Camera& getInstance()
    {
        static Camera instance;
        std::cout <<"Camera getInstance()"<<std::endl;
        return instance;
    }

    void rotateCam(float rotX, float rotY, float rotZ)
    {
        rotate = Quaternion::fromEuler(rotX, rotY, rotZ);
    }
    void rotateCam(Vector3 rot)
    {
        rotateCam(rot.x, rot.y, rot.z);
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
    void rotateCamTo(float rotX, float rotY, float rotZ)
    {
        rotateTo = Quaternion::fromEuler(rotX, rotY, rotZ);
        anim = true;
    }
    void rotateCamTo(Vector3 rot)
    {
        rotateCamTo(rot.x, rot.y, rot.z);
    }
    void rotateCamTo(Quaternion rot)
    {
        rotateTo = rot;
        anim = true;
        rotChange = true;
    }

    void setCamDistTo(float dist)
    {
        distanceTo = dist;
        distanceDelta = distanceTo-distance;
        anim = true;
        distChange =true;
    }

    void setCamCenter(Vector3 center)
    {
        camCenter = center;
    }
    void setCamCenterTo(Vector3 center)
    {
        camCenterTo = center;
        anim = true;
        centerChange = true;
    }

    void update(float timeDelta);
    Ray getRay();
    Vector3 getDirection();
    enum {GETPOINT_3D, GETPOINT_PLANE};
    bool getPoint(Vector3& p, const Plane& plane = Plane(Vector3(0,1,0),0), bool mode=GETPOINT_3D);
    int getLine(LineSegment& line);
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
    Vector3 camCenter, camCenterTo;
    bool rotChange, centerChange, distChange;

    void drawFPS(float timeDelta);
    long lastTimeMS;
    int FPS;
    int lastFPS;
    char FPSchar[64];
};
