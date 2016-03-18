// Shipeng Xu
// billhsu.x@gmail.com

#pragma once
#include <stdint.h>
#include <iostream>
#include "Core/Math/Vectors.h"
#include "Core/Basic/Ray.h"
#include "Core/Basic/Plane.h"
#include "Core/Basic/LineSegment.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Matrices.h"

class Camera {
   public:
    static Camera& getInstance() {
        static Camera instance;
        std::cout << "Camera getInstance()" << std::endl;
        return instance;
    }

    Matrix4 getMatrix() {
        return cameraMatrix;
    }
    Matrix4 getInvertMatrix() {
        Matrix4 invert = cameraMatrix;
        invert.invert();
        return invert;
    }
    Matrix4 getModelView() {
        return modelView;
    }
    Matrix4 getProjection() {
        return projection;
    }
    void rotateCam(float rotX, float rotY, float rotZ) {
        rotate = Quaternion::fromEuler(rotX, rotY, rotZ);
        rotateTo = rotate;
    }
    void rotateCam(Vector3 rot) {
        rotateCam(rot.x, rot.y, rot.z);
    }
    void rotateCam(Quaternion rot) {
        rotate = rot;
        rotateTo = rotate;
    }
    void rotateCamDelta(Quaternion rotDelta) {
        rotate = rotate * rotDelta;
        rotateTo = rotate;
    }
    void setCamDist(float dist) {
        if (dist <= 0)
            dist = 0.0f;
        ;
        if (anim)
            return;
        distance = dist;
        distanceTo = dist;
    }

    // rotate with animation
    void rotateCamTo(float rotX, float rotY, float rotZ) {
        rotateTo = Quaternion::fromEuler(rotX, rotY, rotZ);
        rotChange = true;
        anim = true;
    }
    void rotateCamTo(Vector3 rot) {
        rotateCamTo(rot.x, rot.y, rot.z);
    }
    void rotateCamTo(Quaternion rot) {
        rotateTo = rot;
        anim = true;
        rotChange = true;
    }

    void setCamDistTo(float dist) {
        if (dist <= 0)
            return;
        distanceTo = dist;
        distanceDelta = distanceTo - distance;
        anim = true;
        distChange = true;
    }

    Vector3 getCamCenter() {
        return camCenter;
    }
    void setCamCenter(Vector3 center) {
        camCenter = center;
    }
    void setCamCenterTo(Vector3 center) {
        camCenterTo = center;
        anim = true;
        centerChange = true;
    }

    void setModelView(Matrix4 _modelView) {
        modelView = _modelView;
    }

    void setProjection(Matrix4 _projection) {
        projection = _projection;
    }

    void setWindowHeight(int _height) {
        windowHeight = _height;
    }

    void setWindowWidth(int _width) {
        windowWidth = _width;
    }

    int update(float timeDelta);
    Ray getRay(int mx, int my);
    Vector3 getDirection();
    bool getPoint(int mx, int my, const std::vector<LineSegment>& lines,
                  Vector3& p, const Plane& plane = Plane(Vector3(0, 1, 0), 0));
    int getLine(int mx, int my, const std::vector<LineSegment>& lines,
                LineSegment& line);
    Quaternion getRotateQuaternion() {
        if (!anim)
            return rotate;
        else
            return rotate_slerp;
    }

    float distance, distanceTo, distanceDelta;
    bool anim;
    enum { UPDATE_OK, UPDATE_ANIM_DONE };

   private:
    Camera();
    ~Camera();
    Camera(Camera const&);
    void operator=(Camera const&);
    Matrix4 cameraMatrix;
    float ANIM_TIME_MS;
    float animTime;
    Quaternion rotate, rotateTo, rotate_slerp;
    Vector3 camCenter, camCenterTo;
    bool rotChange, centerChange, distChange;
    Matrix4 modelView;
    Matrix4 projection;
    int windowWidth, windowHeight;

    void updateFPS(float timeDelta);
    long lastTimeMS;
    int FPS;
    int lastFPS;
    char FPSchar[64];
};
