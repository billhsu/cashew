// Shipeng Xu
// billhsu.x@gmail.com

#ifndef RAY_H
#define RAY_H
#include "Core/Math/Vectors.h"
class Ray
{
public:
    Ray() : m_Origin( Vector3( 0, 0, 0 ) ), m_Direction( Vector3( 0, 0, 0 ) ) {};
    Ray( Vector3 a_Origin, Vector3 a_Dir ):m_Origin(a_Origin),m_Direction(a_Dir.normalize()){};
    void SetOrigin( Vector3& a_Origin ) { m_Origin = a_Origin; }
    void SetDirection( Vector3& a_Direction ) { m_Direction = a_Direction.normalize();}
    Vector3& GetOrigin() { return m_Origin; }
    Vector3& GetDirection() { return m_Direction.normalize(); }
    static float distRayPoint(Ray r, Vector3 p)
    {
        return r.GetDirection().cross(p - r.GetOrigin()).length();
    }

private:
    Vector3 m_Origin;
    Vector3 m_Direction;
};
#endif
