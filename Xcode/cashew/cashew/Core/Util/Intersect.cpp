// Shipeng Xu
// billhsu.x@gmail.com

#include "Intersect.h"

Vector3 intersect(Ray r, Plane p)
{
    p.N = - p.N;
    float dist =  -(r.GetOrigin().dot(p.N)+p.D)/r.GetDirection().dot(p.N);
    Vector3 pos = r.GetOrigin() + r.GetDirection()*dist;
    return pos;
}
