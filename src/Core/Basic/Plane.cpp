// Shipeng Xu
// billhsu.x@gmail.com

#include "Plane.h"

void Plane::buildPlane(Vector3 v1, Plane& plane, Vector3 normal)
{
    plane.N = normal;
    plane.D = v1.dot(normal.normalize());
}

void Plane::buildPlane(Vector3 v1, Vector3 v2, Plane& plane, Vector3 direction)
{
    Vector3 v12 = v1 - v2;
    Vector3 _normal = v12.cross(direction).normalize();
    float dist = v1.dot(_normal);
    plane.N = _normal;
    plane.D = dist;
}

void Plane::buildPlane(Vector3 v1, Vector3 v2, Vector3 v3, Plane& plane)
{
    Vector3 v12 = v1 - v2;
    Vector3 v23 = v2 - v3;
    Vector3 normal = v12.cross(v23).normalize();
    float dist = normal.dot(v3);
    plane.N = normal;
    plane.D = dist;
}

void Plane::buildPlane(std::vector<Vector3> &v, Plane& plane, Vector3 normal)
{
    if(v.size()==1) buildPlane(v[0], plane, normal);
    else if(v.size()==2) buildPlane(v[0], v[1], plane, normal);
    else if(v.size()==3) buildPlane(v[0], v[1], v[2], plane);
}