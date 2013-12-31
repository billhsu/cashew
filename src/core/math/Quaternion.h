#pragma once
#include <math>

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
    void gl_matrix(double *m)
    {
        if(!m) return;
        m[ 0] = 1.0f - 2.0f * ( y * y + z * z ); 
        m[ 1] = 2.0f * (x * y + z * w);
        m[ 2] = 2.0f * (x * z - y * w);
        m[ 3] = 0.0f;  
        m[ 4] = 2.0f * ( x * y - z * w );  
        m[ 5] = 1.0f - 2.0f * ( x * x + z * z ); 
        m[ 6] = 2.0f * (z * y + x * w );  
        m[ 7] = 0.0f;  
        m[ 8] = 2.0f * ( x * z + y * w );
        m[ 9] = 2.0f * ( y * z - x * w );
        m[10] = 1.0f - 2.0f * ( x * x + y * y );  
        m[11] = 0.0f;  
        m[12] = 0;  
        m[13] = 0;  
        m[14] = 0;  
        m[15] = 1.0f;
    };
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
};