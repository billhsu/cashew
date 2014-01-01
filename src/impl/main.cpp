/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include <stdio.h>
#include <GL/glut.h>
#include "Display.h"
#include "Ray.h"
#include "Plane.h"
#include "Scene.h"
#include "Utility.h"
#include "Controller.h"

#include <math.h>
#include <vector>
using namespace std;


Controller *ctrl;
long timeMsLast;

void MouseButton(int button, int state, int x, int y)
{
    ctrl->MouseButton(button, state, x, y);
}
void MouseMotion(int x, int y)
{
    ctrl->MouseMotion(x, y);
}
void PassiveMotion(int x, int y)
{
    ctrl->PassiveMotion(x, y);
}
void Keyboard(unsigned char key, int x, int y)
{
    ctrl->Keyboard(key, x, y);
}

void render()
{
    float timeDelta = getMilliSec() - timeMsLast;
    timeMsLast = getMilliSec();
    ctrl->render(timeDelta);

}
void reshape(GLint width, GLint height);

int main(int argc, char** argv)
{
    ctrl=&Controller::getInstance();
    ctrl->init();
    glutInit (&argc, argv);
    glutInitWindowSize (ctrl->width, ctrl->height);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("NeXTSketch");

    glutDisplayFunc (render);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (Keyboard);
    glutMouseFunc (MouseButton);
    glutMotionFunc (MouseMotion);
    glutPassiveMotionFunc(PassiveMotion);

    timeMsLast = getMilliSec();


    // Turn the flow of control over to GLUT

    glutMainLoop ();

    return 0;
}


void reshape(GLint w, GLint h)
{
    Controller::width = w;
    Controller::height = h;

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0*w/h, 1.0*w/h, -1.0, 1.0, 1.5, 200.0);
    glMatrixMode (GL_MODELVIEW);
}
