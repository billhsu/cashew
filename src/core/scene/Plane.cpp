#include <GL/glut.h>
#include "Plane.h"

void Plane::drawPlane(Vector3 center, float size)
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
    glColor4f(0.4f,0.4f,0.4f,0.5f);
    glBegin(GL_QUADS);
        glVertex3fv(p1.cell);
        glVertex3fv(p2.cell);
        glVertex3fv(p3.cell);
        glVertex3fv(p4.cell);
    glEnd();

    glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

}