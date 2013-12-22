/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#ifndef PLANE_H
#define PLANE_H
#include "Vectors.h"
class Plane
{
    public:
        Plane() : N( 0, 1, 0 ), D( 0 ) {};
        Plane( Vector3 a_Normal, float a_D ) : N( a_Normal ), D( a_D ) {};

        Vector3 N;
        float D;
};

#endif
