#include "display.h"
#include "line.h"
#include<GL/glut.h>
#include "scene.h"
#include "ray.h"
#include "plane.h"
#include <vector>
using namespace std;
extern int width,height;
extern int mouseX, mouseY;
float rotateX=-30.0f, rotateY=0.0f, rotateZ=0.0f;
vector<Vector3> posList;
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

    glBegin(GL_POINTS);
        for(int i=0; i<posList.size(); ++i)
        {
            glVertex3fv(posList[i].cell);
        }
    glEnd();

    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);
    glutPostRedisplay();
    glutSwapBuffers();
}
