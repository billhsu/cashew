#ifndef PLANE_H
#define PLANE_H
#include "vectors.h"
class plane
{
    public:
        plane() : N( 0, 0, 0 ), D( 0 ) {};
        plane( Vector3 a_Normal, float a_D ) : N( a_Normal ), D( a_D ) {};

        Vector3 N;
        float D;
};

#endif
