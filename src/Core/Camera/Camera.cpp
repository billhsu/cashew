// Shipeng Xu
// billhsu.x@gmail.com

#include "Camera.h"
#include "Core/Util/Utility.h"
#include "Core/Math/Vectors.h"
#include "Core/Graphics/Project.h"
#include "Core/Util/Intersect.h"
#include "Core/Controller/Controller.h"
#include <iostream>

Camera::Camera() {
    anim = false;
    distance = 10.0f;
    distanceTo = distance;
    distanceDelta = 0.0f;
    rotate = Quaternion::fromEuler(0, 0, 0);
    camCenter = Vector3(0, 0, 0);
    lastTimeMS = getMilliSec();
    FPS = 0;
    lastFPS = 0;
    ANIM_TIME_MS = 300.0;
    animTime = 0.0f;
    rotChange = false;
    centerChange = false;
    distChange = false;
    std::cout << "Camera Camera()" << std::endl;
}

Camera::~Camera() {
    std::cout << "Camera ~Camera()" << std::endl;
}

int Camera::update(float timeDelta) {
    bool anim_done = false;
    cameraMatrix.identity();
    if (!anim) {
        Matrix4 lookMat = cashew::gluLookAt(0.0f, 0.0f, 0.0f - distance, 0.0f,
                                            0.0f, 0.0f, 0.0, 1.0, 0.0);
        Matrix4 trans;
        trans.translate(-camCenter.x, -camCenter.y, -camCenter.z);
        cameraMatrix = lookMat * rotate.getMatrix() * trans;
        animTime = 0;
    } else {
        animTime += timeDelta;
        float alpha = animTime / ANIM_TIME_MS;
        if (animTime >= ANIM_TIME_MS) {
            anim_done = true;
            animTime = 0;
            anim = false;
            if (rotChange)
                rotate = rotateTo;
            if (distChange)
                distance = distanceTo;
            if (centerChange)
                camCenter = camCenterTo;

            rotChange = false;
            centerChange = false;
            distChange = false;

            Controller::rotate = Quaternion::toEuler(rotate);

            Matrix4 lookMat = cashew::gluLookAt(
                0.0f, 0.0f, 0.0f - distance, 0.0f, 0.0f, 0.0f, 0.0, 1.0, 0.0);
            Matrix4 trans;
            trans.translate(-camCenter.x, -camCenter.y, -camCenter.z);
            cameraMatrix = lookMat * rotate.getMatrix() * trans;
        } else {
            float distanceTmp = distance * (1 - alpha) + distanceTo * alpha;
            rotate_slerp = Quaternion();
            if (rotChange)
                rotate_slerp = Quaternion::slerp(rotate, rotateTo, alpha);
            Vector3 camCenterTmp =
                camCenter * (1 - alpha) + camCenterTo * alpha;
            Matrix4 lookMat =
                cashew::gluLookAt(0.0f, 0.0f, 0.0f - distanceTmp, 0.0f, 0.0f,
                                  0.0f, 0.0, 1.0, 0.0);
            Matrix4 trans;
            trans.translate(-camCenterTmp.x, -camCenterTmp.y, -camCenterTmp.z);
            cameraMatrix = lookMat * rotate_slerp.getMatrix() * trans;
        }
    }
    modelView = cameraMatrix;
    updateFPS(timeDelta);
    if (anim_done)
        return UPDATE_ANIM_DONE;
    else
        return UPDATE_OK;
}

void Camera::updateFPS(float timeDelta) {
    FPS++;
    if (getMilliSec() - lastTimeMS >= 1000) {
        lastTimeMS = getMilliSec();
        lastFPS = FPS;
        FPS = 0;
    }
}

Ray Camera::getRay(int mx, int my) {
    int32_t viewport[4];
    float winX, winY;
    double posX1, posY1, posZ1;
    double posX2, posY2, posZ2;
    viewport[0] = 0;
    viewport[1] = 0;
    viewport[2] = windowWidth;
    viewport[3] = windowHeight;
    winX = (float)mx;
    winY = (float)viewport[3] - (float)my;

    cashew::gluUnProject(winX, winY, 0.0f, modelView.get(), projection.get(),
                         viewport, &posX1, &posY1, &posZ1);
    cashew::gluUnProject(winX, winY, 1.0f, modelView.get(), projection.get(),
                         viewport, &posX2, &posY2, &posZ2);
    Ray selectRay = Ray(Vector3(posX1, posY1, posZ1),
                        Vector3(posX2 - posX1, posY2 - posY1, posZ2 - posZ1));

    return selectRay;
}

Vector3 Camera::getDirection() {
    return Quaternion::toVector(rotate);
}

bool Camera::getPoint(int mx, int my, const std::vector<LineSegment>& lines,
                      Vector3& p, const Plane& plane) {
    float minDist = 1000.0f;
    bool findCurr = false;
    Ray ray = getRay(mx, my);

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < 2; ++j) {
            if (Ray::distRayPoint(ray, lines[i].points[j]) < 0.1f) {
                if ((ray.GetOrigin() - lines[i].points[j]).length() < minDist) {
                    minDist = (ray.GetOrigin() - lines[i].points[j]).length();
                    p = lines[i].points[j];
                    findCurr = true;
                }
            }
        }
    }
    if (!findCurr)
        p = intersect(ray, plane);
    // std::cout<<p<<std::endl;
    return findCurr;
}

int Camera::getLine(int mx, int my, const std::vector<LineSegment>& lines,
                    LineSegment& line) {
    Ray ray = getRay(mx, my);
    Vector3 v1 = ray.GetOrigin();
    Vector3 v2 = v1 + ray.GetDirection() * 100.0f;
    LineSegment l;
    l.points[0] = v1;
    l.points[1] = v2;
    float minDist = 1000.0f;
    int linePos = -1;
    for (int i = 0; i < lines.size(); ++i) {
        float dist = LineSegment::distSegmentSegment(lines[i], l);
        if (dist <= 0.1f) {
            minDist = dist;
            line = lines[i];
            linePos = i;
        }
    }
    return linePos;
}
