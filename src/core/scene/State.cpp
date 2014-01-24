#include "State.h"
#include "Controller.h"
#include "../camera/Camera.h"
#include "Scene.h"
#include "Plane.h"
#include "../math/Quaternion.h"
#include "LineSegment.h"

State::State()
{
    ctrl = &Controller::getInstance();
    camera = &Camera::getInstance();
    std::cout<<"State State()"<<std::endl;
}

// State Idle

void StateIdle::MouseButton(int button, int state, int x, int y)
{    
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            stateSelectPlane->selectedPoints.clear();
            Vector3 v;
            camera->getPoint(v);
            std::cout<<v<<std::endl;
            stateSelectPlane->selectedPoints.push_back(v);
            Plane::buildPlane(
                stateSelectPlane->selectedPoints, Controller::currPlane);
            Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                Quaternion::Z_NEG_AXIS);
            camera->setCamCenterTo(v);
            camera->rotateCamTo(q);
            enterState(stateSelectPlane);
        }

        if(button==GLUT_RIGHT_BUTTON)
        {
            Controller::lastMouseX=x;
            Controller::lastMouseY=y;
        }
        if(button == 3)
        {
            float dist = camera->distance;
            camera->setCamDist(dist-2);
        }
        if(button == 4)
        {
            float dist = camera->distance;
            camera->setCamDist(dist+2);
        }
    }
}

void StateIdle::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateIdle::PassiveMotion(int x, int y)
{

}

void StateIdle::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'b')
    {
        Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
        camera->setCamCenter(Vector3(0,0,0));
        camera->rotateCamTo(q);
    }
    if(key == 'd')
    {
        enterState(stateDeleteLine);
    }
}

void StateIdle::render(float timeDelta)
{
    
}


// State Delete Line

void StateDeleteLine::MouseButton(int button, int state, int x, int y)
{    
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            bCurLine = camera->getLine(line);
            if(bCurLine!=-1)
            {
                Controller::sketchLines.erase(Controller::sketchLines.begin()+bCurLine);
                bCurLine = -1;
                enterState(stateIdle);
            }
        }
        if(button==GLUT_RIGHT_BUTTON)
        {
            Controller::lastMouseX=x;
            Controller::lastMouseY=y;
        }
        if(button == 3)
        {
            float dist = camera->distance;
            camera->setCamDist(dist-2);
        }
        if(button == 4)
        {
            float dist = camera->distance;
            camera->setCamDist(dist+2);
        }
    }
}

void StateDeleteLine::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateDeleteLine::PassiveMotion(int x, int y)
{
    bCurLine = camera->getLine(line);
}

void StateDeleteLine::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'b')
    {
        Quaternion q = Quaternion::fromEuler(Vector3(-90,0,0));
        camera->setCamCenter(Vector3(0,0,0));
        camera->rotateCamTo(q);
    }
    if(key == 'x')
    {
        enterState(stateIdle);
    }
}

void StateDeleteLine::render(float timeDelta)
{
    if(bCurLine!=-1)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        //line.points[0]*=2.0f;
        line.render(1,0,0);
        glLineWidth(1);
    }
}

// State Select Plane
void StateSelectPlane::MouseButton(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            Vector3 v;
            camera->getPoint(v);
            std::cout<<v<<std::endl;
            // three selected points should be different 
            for(int i=0; i<selectedPoints.size();++i) 
            {
                if(v==selectedPoints[i]) return;
            }
            selectedPoints.push_back(v);
            Plane::buildPlane(selectedPoints, Controller::currPlane);
            Controller::currPlane.printStatus();
            Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
                Quaternion::Z_NEG_AXIS);
            Vector3 center(0,0,0);
            for(int i=0;i<selectedPoints.size();++i)
                center += selectedPoints[i];
            center /= selectedPoints.size();

            camera->setCamCenterTo(center);
            camera->rotateCamTo(q);
            if(selectedPoints.size()==3) 
            {
                stateDraw->vCenter = center;
                //enterState(stateDraw);
            }
        }
        if(button == GLUT_RIGHT_BUTTON)
        {
            Controller::lastMouseX=x;
            Controller::lastMouseY=y;
        }
        if(button == 3)
        {
            float dist = camera->distance;
            camera->setCamDist(dist-2);
        }
        if(button == 4)
        {
            float dist = camera->distance;
            camera->setCamDist(dist+2);
        }
    }
}

void StateSelectPlane::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateSelectPlane::PassiveMotion(int x, int y)
{

}

void StateSelectPlane::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'x')
    {
        Vector3 center(0,0,0);
        for(int i=0;i<selectedPoints.size();++i)
            center += selectedPoints[i];
        center /= selectedPoints.size();
        
        stateDraw->vCenter = center;
        enterState(stateDraw);
    }
    if(key =='b')
    {
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
        Quaternion::Z_NEG_AXIS);
        camera->rotateCamTo(q);
    }
}

void StateSelectPlane::render(float timeDelta)
{
    Vector3 center(0,0,0);
    for(int i=0;i<selectedPoints.size();++i)
        center += selectedPoints[i];
    center /= selectedPoints.size();
    float color[4] = {0.3,0.3,0.3,0.3};
    Controller::currPlane.drawPlane(center, 20, color);
    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    for(int i = 0; i<selectedPoints.size(); ++i)
    {
        glVertex3fv(selectedPoints[i].cell);
    }
    glEnd();
    glPointSize(1);
}

// State Draw
void StateDraw::MouseButton(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if(internalState==IDLE)
            {
                camera->getPoint(startPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                camera->getPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                internalState = START_POINT_SELECTED;
            }
        }
        if(button == GLUT_RIGHT_BUTTON)
        {
            Controller::lastMouseX=x;
            Controller::lastMouseY=y;
        }
        if(button == 3)
        {
            float dist = camera->distance;
            camera->setCamDist(dist-2);
        }
        if(button == 4)
        {
            float dist = camera->distance;
            camera->setCamDist(dist+2);
        }
    }
    if(state==GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
            if(internalState==START_POINT_SELECTED)
            {
                camera->getPoint(endPoint, Controller::currPlane, Camera::GETPOINT_PLANE);
                LineSegment line = LineSegment(startPoint, endPoint);

                Vector3 startPointMirror = startPoint;
                Vector3 endPointMirror = endPoint;
                startPointMirror.x = -startPointMirror.x;
                endPointMirror.x   = -endPointMirror.x;
                LineSegment lineMirror = LineSegment(startPointMirror, endPointMirror);

                Controller::sketchLines.push_back(line);
                Controller::sketchLines.push_back(lineMirror);
                internalState = IDLE;
            }
        }
    }

}

void StateDraw::MouseMotion(int x, int y)
{
    int dx,dy;

    dx = x - Controller::lastMouseX;
    dy = y - Controller::lastMouseY;
    Controller::lastMouseX = x;
    Controller::lastMouseY = y;

    if(Controller::mouseState==GLUT_DOWN)
    {
        if(Controller::mouseButton==GLUT_LEFT_BUTTON)
        {
            if(internalState == START_POINT_SELECTED)
                camera->getPoint(endPoint, Controller::currPlane);
        }
        if(Controller::mouseButton==GLUT_RIGHT_BUTTON)
        {
            Controller::rotate.x -=dy;
            Controller::rotate.y +=dx;
            camera->rotateCam(Controller::rotate);
        }
    }
}

void StateDraw::PassiveMotion(int x, int y)
{

}

void StateDraw::Keyboard(unsigned char key, int x, int y)
{
    if(key == 'b')
    {
        Quaternion q = Quaternion::fromVector(Controller::currPlane.N, 
        Quaternion::Z_NEG_AXIS);
        camera->rotateCamTo(q);
    }
    if(key == 'x')
    {
        enterState(stateIdle);
    }
}

void StateDraw::render(float timeDelta)
{
    float color[4] = {0.4,0.4,0.4,0.7};
    Controller::currPlane.drawPlane(vCenter, 20, color);

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1,1,0);
        glVertex3fv(vCenter.cell);
    glEnd();

    if(internalState == START_POINT_SELECTED)
    {
        glPointSize(5);
        glBegin(GL_POINTS);
        glColor3f(1,0,1);
            glVertex3fv(startPoint.cell);
            glVertex3fv(endPoint.cell);
        glEnd();
        glLineWidth(3);
        glColor3f(1,1,0);
        glBegin(GL_LINES);
            glVertex3fv(startPoint.cell);
            glVertex3fv(endPoint.cell);
        glEnd();
    }
    

    glPointSize(1);
    glLineWidth(1);



}
