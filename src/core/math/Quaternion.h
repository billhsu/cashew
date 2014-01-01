#pragma once
#include <cmath>
#include "Matrices.h"
#include "Vectors.h"

class Quaternion
{
public:
    Quaternion(): w(1),x(0),y(0),z(0) {};
    Quaternion(float x1, float y1, float z1, float degrees)
    {
        buildQuaternion(x1, y1, z1, degrees);
    };

    Quaternion(Vector3 axis, float degrees)
    {
        buildQuaternion(axis.x, axis.y, axis.z, degrees);
    }

    void buildQuaternion(float x1, float y1, float z1, float degrees)
    {
        float angle = float((degrees / 180.0f) * 3.1415926);
        float result = (float)sin( angle / 2.0f );
        w = (float)cos( angle / 2.0f );
        x = float(x1 * result);
        y = float(y1 * result);
        z = float(z1 * result);
    }
    // length of the quaternion
    float length() const 
    { 
        return (float)sqrt(w*w + x*x + y*y + z*z); 
    }

    // normalizes this quaternion
    void normalize() { *this/=length(); }

    // returns the normalized version of this quaternion
    Quaternion normalized() const { return *this/length(); }

    Quaternion operator +(const Quaternion &q) const  
    {
        Quaternion quat;
        quat.w = q.w+w;
        quat.x = q.x+x;
        quat.y = q.y+y;
        quat.z = q.z+z;
        return quat;
    }

    Quaternion operator -() const
    {
        Quaternion quat;
        quat.w = -w;
        quat.x = -x;
        quat.y = -y;
        quat.z = -z;
        return quat;
    }

    Quaternion operator *(float scale) const
    {
        Quaternion quat;
        quat.w=w*scale; 
        quat.x=x*scale;
        quat.y=y*scale;
        quat.z=z*scale;
        return quat;
    }

    Quaternion operator /(float scale) const
    {
        Quaternion quat;
        quat.w=w/scale; 
        quat.x=x/scale;
        quat.y=y/scale;
        quat.z=z/scale;
        return quat;
    }

    Quaternion &operator /= (float scale) 
    {
        w/=scale; 
        x/=scale;
        y/=scale;
        z/=scale;
        return *this; 
    }
    
    Quaternion operator* (const Quaternion &b) {
        Quaternion r;
        r.w = w*b.w - x*b.x - y*b.y - z*b.z;
        r.x = w*b.x + x*b.w + y*b.z - z*b.y;
        r.y = w*b.y + y*b.w + z*b.x - x*b.z;
        r.z = w*b.z + z*b.w + x*b.y - y*b.x;
        return(r);
    };

    // dot product of 2 quaternions
    static inline float dot(const Quaternion &q1, const Quaternion &q2) 
    {
        return q1.w*q2.w + q1.x*q2.x + q1.y*q2.y + q1.z*q2.z;
    }



    // linear quaternion interpolation
    static Quaternion lerp(const Quaternion &q1, const Quaternion &q2, float t) 
    {
        return (q1*(1-t) + q2*t).normalized();
    }

    // spherical linear interpolation
    static Quaternion slerp(const Quaternion &q1, const Quaternion &q2, float t) 
    {
        Quaternion q3;
        float dot = Quaternion::dot(q1, q2);

        /*  dot = cos(theta)
            if (dot < 0), q1 and q2 are more than 90 degrees apart,
            so we can invert one to reduce spinning */
        if (dot < 0)
        {
            dot = -dot;
            q3 = -q2;
        }
        else q3 = q2;
        
        if (dot < 0.95f)
        {
            float angle = acosf(dot);
            return (q1*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
        } 
        else // if the angle is small, use linear interpolation                               
            return lerp(q1,q3,t);       
    }

    // get quaternion from rotation(in degree)
    static Quaternion fromEuler(float rotX, float rotY, float rotZ)
    {
        Quaternion quatX(1.0f,0.0f,0.0f,rotX);
        Quaternion quatY(0.0f,1.0f,0.0f,rotY);
        Quaternion quatZ(0.0f,0.0f,1.0f,rotZ);
        return quatX*quatY*quatZ;
    }

    static Quaternion fromEuler(const Vector3& rot)
    {
        Quaternion quatX(1.0f,0.0f,0.0f,rot.x);
        Quaternion quatY(0.0f,1.0f,0.0f,rot.y);
        Quaternion quatZ(0.0f,0.0f,1.0f,rot.z);
        return quatX*quatY*quatZ;
    }


    Matrix4& getMatrix();
    float*   getFloat();
private:
    float w,x,y,z;
    float m[16];
    Matrix4 mat;
};