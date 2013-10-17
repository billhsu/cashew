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
vector<Vector3> pointList;
vector< vector<Vector3> > lineList;
void display(void)
{
    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rotateX,1.0f,0.0f,0.0f);
    glRotatef(rotateY,0.0f,1.0f,0.0f);
    glRotatef(rotateZ,0.0f,0.0f,1.0f);

    glDisable(GL_LIGHTING);
    glLineWidth(3.0f);
    for(int i=0; i<lineList.size(); ++i)
    {
        glBegin(GL_LINES);
            for(int j=0; j<lineList[i].size(); ++j)
            {
                if(j==0) glVertex3fv(lineList[i][j].cell);
                else glVertex3fv(lineList[i][j-1].cell);
                glVertex3fv(lineList[i][j].cell);
            }
        glEnd();
    }

    glBegin(GL_LINES);
            for(int i=0; i<pointList.size(); ++i)
            {
                if(i==0) glVertex3fv(pointList[i].cell);
                else glVertex3fv(pointList[i-1].cell);

                glVertex3fv(pointList[i].cell);
            }
    glEnd();

    glLineWidth(1.0f);

    drawPlane(Vector3(0,0,0), plane(Vector3(0,1,0),0), 10);
    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);

    glutPostRedisplay();
    glutSwapBuffers();
}
