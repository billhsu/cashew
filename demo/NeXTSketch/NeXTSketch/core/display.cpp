#include "display.h"
#include "line.h"
#include<GL/glut.h>
#include "scene.h"
#include "ray.h"
#include "plane.h"
extern int width,height;
extern int mouseX, mouseY;
float rotateX=-30.0f, rotateY=0.0f, rotateZ=0.0f;
void display(void)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;

    


    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotateX,1.0f,0.0f,0.0f);
    glRotatef(rotateY,0.0f,1.0f,0.0f);
    glRotatef(rotateZ,0.0f,0.0f,1.0f);

    //TODO:
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)mouseX;
    winY = (float)viewport[3] - (float)mouseY;

    gluUnProject( winX, winY, 0.0f, modelview, projection, viewport, &posX1, &posY1, &posZ1);
    gluUnProject( winX, winY, 1.0f, modelview, projection, viewport, &posX2, &posY2, &posZ2);
    std::cout<<winX<<" "<<winY<<std::endl; 
    Ray selectRay = Ray(Vector3(posX1,posY1,posZ1), Vector3(posX1-posX2,posY1-posY2,posZ1-posZ2));
    plane ground = plane(Vector3(0,1,0), 0);
    Vector3 pos = intersect(selectRay, ground);
    //std::cout <<Vector3(posX1,posY1,posZ1)<<" "<<Vector3(posX2,posY2,posZ2)<<std::endl;
    std::cout<<pos<<std::endl;
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3f(posX1,posY1,posZ1);
    glVertex3f(posX2,posY2,posZ2);
    glEnd();

    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);
    glutPostRedisplay();
    glutSwapBuffers();
}
