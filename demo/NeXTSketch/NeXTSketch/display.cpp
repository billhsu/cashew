#include "display.h"
#include "Draw/line.h"
#include "glut.h"
#include "scene.h"
extern int width,height;
float rotateX=-30.0f, rotateY=0.0f, rotateZ=0.0f;
void display(void)
{
    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotateX,1.0f,0.0f,0.0f);
    glRotatef(rotateY,0.0f,1.0f,0.0f);
    glRotatef(rotateZ,0.0f,0.0f,1.0f);
    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);
    glutPostRedisplay();
    glutSwapBuffers();
}