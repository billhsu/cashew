#include <GL/glut.h>
#include "Plane.h"

void Plane::buildPlane(Vector3 v1, Plane& plane)
{
    plane.N = Vector3(0,1,0);
    plane.D = 0;
}

void Plane::buildPlane(Vector3 v1, Vector3 v2, Plane& plane)
{
    Vector3 v12 = v1 - v2;
    Vector3 normal = v12.cross(Vector3(0,1,0)).normalize();
    float dist = v1.dot(normal);
    plane.N = normal;
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

void Plane::buildPlane(std::vector<Vector3> &v, Plane& plane)
{
    if(v.size()==1) buildPlane(v[0], plane);
    else if(v.size()==2) buildPlane(v[0], v[1], plane);
    else if(v.size()==3) buildPlane(v[0], v[1], v[3], plane);
}
void Plane::drawPlane(Vector3 center, float size, float* color)
{
    size/=2.0f;
    Vector3 randVec = Vector3(0,0,1);
    if (randVec.cross(N).length()<0.001f) randVec = Vector3(1,0,0);
    Vector3 vx = N.cross(randVec);
    Vector3 vy = N.cross(vx);
    vx.normalize();
    vy.normalize();
    vx*=size;
    vy*=size;

    Vector3 p1,p2,p3,p4;
    p1 = center + vx + vy;
    p2 = center + vx - vy;
    p3 = center - vx - vy;
    p4 = center - vx + vy;

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glDisable(GL_LIGHTING);
    if(!color)glColor4f(0.4f,0.4f,0.4f,0.5f);
    else glColor4fv(color);
    glBegin(GL_QUADS);
        glVertex3fv(p1.cell);
        glVertex3fv(p2.cell);
        glVertex3fv(p3.cell);
        glVertex3fv(p4.cell);
    glEnd();

    //glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

}