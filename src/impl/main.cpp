/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include <stdio.h>
#include <GL/glut.h>
#include "../core/scene/Ray.h"
#include "../core/scene/Plane.h"
#include "../core/scene/Scene.h"
#include "Utility.h"
#include "../core/scene/Controller.h"
#include "../core/UI/UI.h"
#include "../core/UI/UINode.h"
#include "../core/UI/UIButton.h"
#include "../core/texture/g2Images.h"
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
void testCallback(UINode* sender)
{
    std::cout<<"testCallback"<<std::endl;
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
    UIButton* btn, *btn2;
    
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

    int _w, _h, _ch;
    GLuint TextureID_idle = g2LoadImage("media/textures/button.png", &_w, &_h, &_ch, false, false);
    GLuint TextureID_hover = g2LoadImage("media/textures/button_hover.png", &_w, &_h, &_ch, false, false);
    GLuint TextureID_press = g2LoadImage("media/textures/button_press.png", &_w, &_h, &_ch, false, false);

    btn = Controller::GUI->addButton(200, 200, 100, 100, 
                                    TextureID_idle, TextureID_hover, TextureID_press,
                                    "test", testCallback);
    btn->setColor(1.0f,1.0f,1.0f,0.9f);

    btn2 = Controller::GUI->addButton(400, 200, 100, 100, 
                                    TextureID_idle, TextureID_hover, TextureID_press,
                                    "test", testCallback);
    btn2->setColor(1.0f,1.0f,1.0f,0.9f);

    // Turn the flow of control over to GLUT

    glutMainLoop ();

    return 0;
}


void reshape(GLint w, GLint h)
{
    Controller::resize(w, h);

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0*w/h, 1.0*w/h, -1.0, 1.0, 1.5, 200.0);
    glMatrixMode (GL_MODELVIEW);
}
