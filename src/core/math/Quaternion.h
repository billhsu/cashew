#pragma once
#include <cmath>
#include "Matrices.h"

class Quaternion
{
public:
    Quaternion(): w(1),x(0),y(0),z(0) {};
    Quaternion(float x1, float y1, float z1, float degrees)
    {
        float angle = float((degrees / 180.0f) * 3.1415926);
        float result = (float)sin( angle / 2.0f );
        w = (float)cos( angle / 2.0f );
        x = float(x1 * result);
        y = float(y1 * result);
        z = float(z1 * result);
    };

    Matrix4& getMatrix();
    float*   getFloat();
    
    Quaternion operator* (const Quaternion &b) {
        Quaternion r;
        r.w = w*b.w - x*b.x - y*b.y - z*b.z;
        r.x = w*b.x + x*b.w + y*b.z - z*b.y;
        r.y = w*b.y + y*b.w + z*b.x - x*b.z;
        r.z = w*b.z + z*b.w + x*b.y - y*b.x;
        return(r);
    };
private:
    float w,x,y,z;
    float m[16];
    Matrix4 mat;
};