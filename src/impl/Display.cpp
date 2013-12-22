#include "Display.h"

using namespace std;
extern int width,height;
extern int mouseX, mouseY;
float rotateX=-30.0f, rotateY=0.0f, rotateZ=0.0f;

vector<Vector3> pointList;
vector< vector<Vector3> > lineList;

Plane currPlane;
Vector3 currPoint;

void display(void)
{
    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Vector3 planeN = currPlane.N;

    if(sysMode==DRAW && findCurr && planeMode == VER_PLANE) 
        gluLookAt (currPoint.x + planeN.x*20,currPoint.y,currPoint.z + planeN.z*20,
            currPoint.x,currPoint.y,currPoint.z, 
            0.0, 1.0, 0.0);
    else 
    {
        gluLookAt (0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(rotateX,1.0f,0.0f,0.0f);
        glRotatef(rotateY,0.0f,1.0f,0.0f);
        glRotatef(rotateZ,0.0f,0.0f,1.0f);
    }
    if(sysMode==DRAW && findCurr) drawPlane(currPoint, currPlane, 20);



    glDisable(GL_LIGHTING);
    glLineWidth(2.0f);
    glColor3f(0.1,0,1);
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

    glPointSize(5.0f);
    glColor3f(1,1,0);
    for(int i=0; i<lineList.size(); ++i)
    {
        glBegin(GL_POINTS);
            for(int j=0; j<lineList[i].size(); ++j)
            {
                glVertex3fv(lineList[i][j].cell);
            }
        glEnd();
    }

    glBegin(GL_POINTS);
            for(int i=0; i<pointList.size(); ++i)
            {
                glVertex3fv(pointList[i].cell);
            }
    glEnd();

    if(findCurr)
    {
        glColor3f(1,0,0);
        glPointSize(8.0f);
        glBegin(GL_POINTS);
            glVertex3fv(currPoint.cell);
        glEnd();
    }
    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);

    glutPostRedisplay();
    glutSwapBuffers();
}
