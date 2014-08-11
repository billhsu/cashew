/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include "../math/Vectors.h"
#include <vector>
class Plane
{
public:
    Plane() : N( 0, 1, 0 ), D( 0 ) {};
    Plane( Vector3 a_Normal, float a_D ) : N( a_Normal ), D( a_D ) {};

    void drawPlane(Vector3 center, float size, float* color = NULL);
    void printStatus()
    {
        std::cout<<"Plane "<<N<<" "<<D<<std::endl;
    }
    static void buildPlane(Vector3 v1, Plane& plane, Vector3 normal = Vector3(0, 1, 0));
    static void buildPlane(Vector3 v1, Vector3 v2, Plane& plane, Vector3 direction = Vector3(0, 1, 0));
    static void buildPlane(Vector3 v1, Vector3 v2, Vector3 v3, Plane& plane);
    static void buildPlane(std::vector<Vector3> &v, Plane& plane, Vector3 normal = Vector3(0, 1, 0));

    Vector3 N;
    float D;
};

#endif
