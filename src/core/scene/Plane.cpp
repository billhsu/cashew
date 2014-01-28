#include "GL/freeglut.h"
#include "Plane.h"

void Plane::buildPlane(Vector3 v1, Plane& plane)
{
    plane.N = Vector3(0,1,0);
    plane.D = v1.y;
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
    else if(v.size()==3) buildPlane(v[0], v[1], v[2], plane);
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
    
    /*
        y
        ^
    p4  |  p1 
        |
    --------> x
        |
    p3  |  p2
    */
    Vector3 p1,p2,p3,p4;
    p1 = center + vx + vy;
    p2 = center + vx - vy;
    p3 = center - vx - vy;
    p4 = center - vx + vy;

    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(!color)glColor4f(0.4f,0.4f,0.4f,0.5f);
    else glColor4fv(color);
    glBegin(GL_QUADS);
        glVertex3fv(p1.cell);
        glVertex3fv(p2.cell);
        glVertex3fv(p3.cell);
        glVertex3fv(p4.cell);
    glEnd();

    glColor4f(1.0f,1.0f,1.0f,0.9f);
    glBegin(GL_LINES);
    int osize = size*2;
    for(int i=0; i<=size*2; ++i)
    {
        Vector3 vXinter1 = p1*((float)i/(float)osize) + p2*((float)(osize - i)/(float)osize);
        Vector3 vXinter2 = p4*((float)i/(float)osize) + p3*((float)(osize - i)/(float)osize);

        Vector3 vYinter1 = p1*((float)i/(float)osize) + p4*((float)(osize - i)/(float)osize);
        Vector3 vYinter2 = p2*((float)i/(float)osize) + p3*((float)(osize - i)/(float)osize);

        if(i==size) glColor4f(1.0f,0.0f,0.0f,1.0f);
        glVertex3fv(vXinter1.cell);
        glVertex3fv(vXinter2.cell);

        if(i==size) glColor4f(0.0f,0.0f,1.0f,1.0f);
        glVertex3fv(vYinter1.cell);
        glVertex3fv(vYinter2.cell);

        if(i==size) glColor4f(1.0f,1.0f,1.0f,0.9f);

    }
    glEnd();

    //glEnable(GL_LIGHTING);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

}