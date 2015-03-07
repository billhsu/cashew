/* 
Shipeng Xu
billhsu.x@gmail.com

Thanks to:
http://willperone.net/Code/quaternion.php
http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors
*/

#pragma once
#include <cmath>
#include "Matrices.h"
#include "Vectors.h"
#include <iostream>
#include "Core/Util/Utility.h"

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
    
    bool operator==(const Quaternion& rhs)
    {
        return w==rhs.w && x==rhs.x && y==rhs.y && z==rhs.z;
    }
    
    bool operator!=(const Quaternion& rhs)
    {
        return w!=rhs.w || x!=rhs.x || y!=rhs.y || z!=rhs.z;
    }
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

    // build quaternion from euler angles(in degree)
    static Quaternion fromEuler(const Vector3& rot)
    {
        Quaternion quatX(1.0f,0.0f,0.0f,rot.x);
        Quaternion quatY(0.0f,1.0f,0.0f,rot.y);
        Quaternion quatZ(0.0f,0.0f,1.0f,rot.z);
        return quatX*quatY*quatZ;
    }

    // convert quaternion to Euler(in degree)
    static Vector3 toEuler(const Quaternion &q1)
    {
        Vector3 rot;
        float sqw = q1.w*q1.w;
        float sqx = q1.x*q1.x;
        float sqy = q1.y*q1.y;
        float sqz = q1.z*q1.z;
        float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
        float test = q1.x*q1.y + q1.z*q1.w;
        if (test > 0.499*unit) { // singularity at north pole
            rot.y = 2 * atan2(q1.x,q1.w)*180.0f/PI;
            rot.z = 180.0f/2;
            rot.x = 0;
            return rot;
        }
        if (test < -0.499*unit) { // singularity at south pole
            rot.y = -2 * atan2(q1.x,q1.w)*180.0f/PI;
            rot.z = -180.0f/2;
            rot.x = 0;
            return rot;
        }
        rot.y = atan2(2*q1.y*q1.w-2*q1.x*q1.z , sqx - sqy - sqz + sqw)*180.0f/PI;
        rot.z = asin(2*test/unit)*180.0f/PI;
        rot.x = atan2(2*q1.x*q1.w-2*q1.y*q1.z , -sqx + sqy - sqz + sqw)*180.0f/PI;
        return rot;
    }

    // convert quaternion to directional vector
    static Vector3 toVector(const Quaternion &q1)
    {
        Vector3 rotEular = toEuler(q1);
        float elevation = deg2rad(rotEular.x);
        float heading   = deg2rad(rotEular.y);
        return Vector3(cos(elevation) * sin(heading), sin(elevation), cos(elevation) * cos(heading));
    }

    // build a quaternion from two vectors
    // this can convert a directional vector to quaternion
    static Quaternion fromVector(Vector3& u, Vector3& v)
    {
        u.normalize();
        v.normalize();
        Vector3 w = u.cross(v);
        // in case if u and v are parallel
        if(w.length()<=0.0001) 
            return Quaternion(Vector3(0,0,1), 0);
        Quaternion q;
        q.w = 1.0f + u.dot(v);
        q.x = w.x;
        q.y = w.y;
        q.z = w.z;
        return q.normalized();
    }


    Matrix4& getMatrix();
    float*   getFloat();
    void printStatus()
    {
        std::cout<<"w: "<<w<<" x:"<<x<<" y:"<<y<<" z:"<<z<<std::endl;
    }

    static Vector3 X_AXIS, Y_AXIS, Z_AXIS;
    static Vector3 X_NEG_AXIS, Y_NEG_AXIS, Z_NEG_AXIS;
private:
    float w,x,y,z;
    float m[16];
    Matrix4 mat;
};