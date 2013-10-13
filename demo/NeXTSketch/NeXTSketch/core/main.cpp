#include <stdio.h>
#include <GL/glut.h>
#include "display.h"
#include "ray.h"
#include "plane.h"
#include "scene.h"
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
extern vector<Vector3> posList;
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
    if(mouseButton==GLUT_LEFT_BUTTON && mouseStatus==GLUT_DOWN)
    {
        lastX=x;
        lastY=y;
        Ray selectRay = getMouseRay(x,y);
        plane ground = plane(Vector3(0,1,0), 0);
        Vector3 pos = intersect(selectRay, ground);
        posList.push_back(pos);
    }
}
void MouseMotion(int x, int y)
{
    if(mouseButton==GLUT_LEFT_BUTTON&&mouseStatus==GLUT_DOWN)
    {
        int dx = x - lastX;
        int dy = y - lastY;
        rotateX-=dy;
        rotateY+=dx;
        lastX = x;
        lastY = y;
        //printf("x: %f y: %f\n",rotateX,rotateY);
    }
}
void PassiveMotion(int x, int y)
{
    mouseX = x;
    mouseY = y;
}
void Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(1);
    printf("Key:%d x:%d y:%d\n",key,x,y);
}
