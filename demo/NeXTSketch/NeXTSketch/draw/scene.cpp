#include "scene.h"
#include <GL/glut.h>
Vector3 intersect(Ray r, plane p)
{
    float dist =  -(r.GetOrigin().dot(p.N)+p.D)/r.GetDirection().dot(p.N);
    Vector3 pos = r.GetOrigin() + r.GetDirection()*dist;
    return pos;
}
void drawGrid(float size, float step)
{
    // disable lighting
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);

    glColor3f(0.3f, 0.3f, 0.3f);
    for(float i=step; i <= size; i+= step)
    {
        glVertex3f(-size, 0,  i);   // lines parallel to X-axis
        glVertex3f( size, 0,  i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f( size, 0, -i);

        glVertex3f( i, 0, -size);   // lines parallel to Z-axis
        glVertex3f( i, 0,  size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0,  size);
    }

    // x-axis
    glColor3f(0.5f, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f( size, 0, 0);

    // z-axis
    glColor3f(0,0,0.5f);
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0,  size);

    glEnd();

    // enable lighting back
    glEnable(GL_LIGHTING);
}

void drawAxis(float size)
{
    glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
    glDisable(GL_LIGHTING);
    glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
    //      the light position when you draw GL_LINES
    //      and GL_POINTS. remember the matrix.

    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);
    glEnd();
    glLineWidth(1);

    // draw arrows(actually big square dots)
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(size, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, size, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, size);
    glEnd();
    glPointSize(1);

    // restore default settings
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
}
Ray getMouseRay(int mx, int my)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)mx;
    winY = (float)viewport[3] - (float)my;

    gluUnProject( winX, winY, 0.0f, modelview, projection, viewport, &posX1, &posY1, &posZ1);
    gluUnProject( winX, winY, 1.0f, modelview, projection, viewport, &posX2, &posY2, &posZ2);
    std::cout<<winX<<" "<<winY<<std::endl; 
    Ray selectRay = Ray(Vector3(posX1,posY1,posZ1), Vector3(posX1-posX2,posY1-posY2,posZ1-posZ2));
    
    return selectRay;
}

void drawPlane(Vector3 center, plane p, float size)
{
    size/=2.0f;
    center = center + p.D*p.N.normalize();
    Vector3 randVec = Vector3(0,0,1);
    if (randVec.cross(p.N).length()==0.0f) randVec = Vector3(1,0,0);
    Vector3 vx = p.N.cross(randVec);
    Vector3 vy = p.N.cross(vx);
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
