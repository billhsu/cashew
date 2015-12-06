// Shipeng Xu
// billhsu.x@gmail.com

#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include "Core/Math/Vectors.h"
#include <vector>
class Plane {
   public:
    Plane() : N(0, 1, 0), D(0){};
    Plane(Vector3 a_Normal, float a_D) : N(a_Normal), D(a_D){};

    Plane operator-() const {
        Plane p;
        p.N = -N;
        p.D = -D;
        return p;
    }

    void printStatus() {
        std::cout << "Plane " << N << " " << D << std::endl;
    }
    // Build plane from one point and a normal
    static void buildPlane(Vector3 v1, Plane& plane,
                           Vector3 normal = Vector3(0, 1, 0));

    // Build plane from two points and a normal
    static void buildPlane(Vector3 v1, Vector3 v2, Plane& plane,
                           Vector3 normal = Vector3(0, 1, 0));

    // Build plane from three points
    static void buildPlane(Vector3 v1, Vector3 v2, Vector3 v3, Plane& plane);

    // Build plane from a list of points
    static void buildPlane(std::vector<Vector3>& v, Plane& plane,
                           Vector3 normal = Vector3(0, 1, 0));

    Vector3 N;
    float D;
};

#endif
