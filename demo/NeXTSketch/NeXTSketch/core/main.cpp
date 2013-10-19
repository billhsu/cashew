#include <stdio.h>
#include <GL/glut.h>
#include "display.h"
#include "ray.h"
#include "plane.h"
#include "scene.h"
#include "utility.h"
#include <math.h>
#include <vector>
using namespace std;
int width = 400, height = 300;
int mouseStatus =1;
int mouseButton = 0;
int mouseX=0,mouseY=0;
extern float rotateX, rotateY, rotateZ;
int lastX=0,lastY=0;
void reshape(GLint width, GLint height);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);


int main(int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitWindowSize (width, height);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("NeXTSketch");

    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (Keyboard);
    glutMouseFunc (MouseButton);
    glutMotionFunc (MouseMotion);
    glutPassiveMotionFunc(PassiveMotion);

    // Turn the flow of control over to GLUT

    glutMainLoop ();

    return 0;
}


void reshape(GLint w, GLint h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0*w/h, 1.0*w/h, -1.0, 1.0, 1.5, 200.0);
    glMatrixMode (GL_MODELVIEW);
}
void MouseButton(int button, int state, int x, int y)
{
    printf("button:%d state:%d x:%d y:%d\n",button, state, x, y);
    mouseButton = button;
    mouseStatus = state;
    if(mouseButton==GLUT_RIGHT_BUTTON && mouseStatus==GLUT_DOWN)
    {
        lastX=x;
        lastY=y;
    }
    if(mouseButton==GLUT_LEFT_BUTTON && mouseStatus==GLUT_DOWN && sysMode==IDLE)
    {
        planeMode = HOR_PLANE;
        pointList.clear();
        Ray selectRay = getMouseRay(x,y);
        if(!getRayPoint(selectRay,currPoint))
        {
            currPlane.N = Vector3(0,1,0);
            currPlane.D = 0;
            Vector3 pos = intersect(selectRay, currPlane);
            currPoint = pos;
            findCurr = true;
            currPlane.N = Vector3(0,1,0);
            currPlane.D = currPoint.y;
            sysMode = DRAW;
        }
        else
        {
            currPlane.N = Vector3(0,1,0);
            currPlane.D = currPoint.y;
            sysMode = DRAW;
        }
    }
    if(mouseButton==GLUT_LEFT_BUTTON && mouseStatus==GLUT_UP)
    {
        lineList.push_back(pointList);
        sysMode = IDLE;
    }
}
void MouseMotion(int x, int y)
{
    static unsigned long timeCurr = 0;
    Ray selectRay = getMouseRay(x,y);
    int dx,dy;

        dx = x - lastX;
        dy = y - lastY;
        lastX = x;
        lastY = y;

    if(mouseButton==GLUT_RIGHT_BUTTON&&mouseStatus==GLUT_DOWN)
    {
        rotateX-=dy;
        rotateY+=dx;   
        //printf("x: %f y: %f\n",rotateX,rotateY);
    }
    if(sysMode==DRAW && mouseButton==GLUT_LEFT_BUTTON && mouseStatus==GLUT_DOWN)
    {
        int mouseChange = dx*dx + dy*dy;
        float changeRate = exp(-mouseChange/10);
        if(getMilliSec()-timeCurr>changeRate*200)
        {
            Vector3 pos = intersect(selectRay, currPlane);
            cout<<pos<<endl;
            pointList.push_back(pos);
           
            timeCurr = getMilliSec();
        }
    }

}
void PassiveMotion(int x, int y)
{
    if(sysMode!=IDLE) return;
    Ray selectRay = getMouseRay(x,y);
    
    getRayPoint(selectRay,currPoint);
    mouseX = x;
    mouseY = y;
}
void Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(1);
    else if (key == 'C' || key == 'c')
    {
        lineList.clear();
        pointList.clear();
    }
    else if (key =='x' || key =='X')
    {
        if(planeMode == VER_PLANE) 
        {
            planeMode = HOR_PLANE;
            currPlane.N = Vector3(0,1,0);
        }
        else 
        {
            planeMode = VER_PLANE;
            currPlane.N = Vector3(1,0,0);
        }
    }
    printf("Key:%d x:%d y:%d\n",key,x,y);

}
