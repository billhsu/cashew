#include "State.h"
#include "Controller.h"
#include "Camera.h"
#include "Scene.h"
State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}

// State Idle

void StateIdle::MouseButton(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        enterState(stateSelectPlane);
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        ctrl->lastMouseX=x;
        ctrl->lastMouseY=y;
    }
}

void StateIdle::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - ctrl->lastMouseX;
    dy = y - ctrl->lastMouseY;
    ctrl->lastMouseX = x;
    ctrl->lastMouseY = y;

    if(ctrl->mouseButton==GLUT_RIGHT_BUTTON && ctrl->mouseState==GLUT_DOWN)
    {
        Vector3 rot = camera->rotate;
        rot.x-=dy;
        rot.y+=dx;
        camera->rotateCam(rot);
    }
}

void StateIdle::PassiveMotion(int x, int y)
{

}

void StateIdle::Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(1);
    if(key == 'x') camera->rotateCamTo(-90.0f,camera->rotate.y, camera->rotate.z);
}

void StateIdle::render(float timeDelta)
{
    glClearColor (0.9f, 0.9f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera->update(timeDelta);

    drawGrid(20.0f,2.0f);
    drawAxis(2.0f);

    glutPostRedisplay();
    glutSwapBuffers();
}

// State Select Plane
void StateSelectPlane::MouseButton(int button, int state, int x, int y)
{

}

void StateSelectPlane::MouseMotion(int x, int y)
{

}

void StateSelectPlane::PassiveMotion(int x, int y)
{

}

void StateSelectPlane::Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(1);
}

void StateSelectPlane::render(float timeDelta)
{
    
}

// State Draw
void StateDraw::MouseButton(int button, int state, int x, int y)
{

}

void StateDraw::MouseMotion(int x, int y)
{

}

void StateDraw::PassiveMotion(int x, int y)
{

}

void StateDraw::Keyboard(unsigned char key, int x, int y)
{
    if(key == 27) exit(1);
}

void StateDraw::render(float timeDelta)
{
    
}
