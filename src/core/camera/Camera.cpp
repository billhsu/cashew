#include "Camera.h"
#include <GL/freeglut.h>
#include "Quaternion.h"
#include "Controller.h"
#include "Utility.h"
Camera::Camera()
{
    anim = false;
    distance = 10.0f;
    distanceTo = distance;
    distanceDelta = 0.0f;
    rotate.x = -30.0f;
    rotate.y = 0.0f;
    rotate.z = 0.0f;
    rotateTo = rotate;
    rotateDelta.x = 0.0f;
    rotateDelta.y = 0.0f;
    rotateDelta.z = 0.0f;
    width = 400;
    height = 300;
    lastTimeMS = getMilliSec();
    FPS = 0;
    lastFPS = 0;
    std::cout <<"Camera Camera()"<<std::endl;
}

Camera::~Camera()
{
    std::cout <<"Camera ~Camera()"<<std::endl;
}
void Camera::update(float timeDelta)
{
    if(!anim)
    {
        gluLookAt (0.0, 0.0, -distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        //glRotatef(rotate.x,1.0f,0.0f,0.0f);
        //glRotatef(rotate.y,0.0f,1.0f,0.0f);
        //glRotatef(rotate.z,0.0f,0.0f,1.0f);
        Vector3 const xAxis(1.0f,0.0f,0.0f);
        Vector3 const yAxis(0.0f,1.0f,0.0f);
        Vector3 const zAxis(0.0f,0.0f,1.0f);

        Quaternion quatX(xAxis,rotate.x);
        Quaternion quatY(yAxis,rotate.y);
        Quaternion quatZ(zAxis,rotate.z);

        Quaternion quat = quatX*quatY*quatZ;
        glMultTransposeMatrixf(quat.getFloat());
    }
    else
    {
        bool distOK = false;
        bool rotXOK = false;
        bool rotYOK = false;
        bool rotZOK = false;

        if(distanceDelta*(distanceTo - distance)>0) 
            distance = distance + (distanceDelta>0?1:-1);
        else distOK = true;
        if(rotateDelta.x*(rotateTo.x - rotate.x)>0) 
            rotate.x = rotate.x + (rotateDelta.x>0?1:-1)*timeDelta*5.0f;
        else rotXOK = true;
        if(rotateDelta.y*(rotateTo.y - rotate.y)>0) 
            rotate.y = rotate.y + (rotateDelta.y>0?1:-1)*timeDelta*5.0f;
        else rotYOK = true;
        if(rotateDelta.z*(rotateTo.z - rotate.z)>0) 
            rotate.z = rotate.z + (rotateDelta.z>0?1:-1)*timeDelta*5.0f;
        else rotZOK = true;

        gluLookAt (0.0, 0.0, -distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glRotatef(rotate.x,1.0f,0.0f,0.0f);
        glRotatef(rotate.y,0.0f,1.0f,0.0f);
        glRotatef(rotate.z,0.0f,0.0f,1.0f);
        if(distOK && rotXOK && rotYOK && rotZOK) anim = false;
    }
    // draw FPS
    
    drawFPS();
}

void Camera::drawFPS()
{
    FPS++;
    if(getMilliSec() - lastTimeMS>=1000)
    {
        lastTimeMS = getMilliSec();
        lastFPS = FPS;
        FPS = 0;
    }
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix() ; // save
    glLoadIdentity();// and clear

    glOrtho(0, Controller::width, 0, Controller::height,-1,1);
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;

    glScalef(1, -1, 1);           // Invert Y axis so increasing Y goes down.
    glTranslatef(0.0f, (float)-Controller::height, 0.0f); 


    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

    glRasterPos2f(10, 20);
    snprintf(FPSchar, sizeof(FPSchar), "Width:%4d Height:%4d FPS:%3d", 
        Controller::width, Controller::height, lastFPS);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)FPSchar);
    //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'a');

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix(); // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}

Ray Camera::getRay(int mx, int my)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)mx;
    winY = (float)viewport[3] - (float)my;

    gluUnProject( winX, winY, 0.0f, modelview, projection, viewport, &posX1, &posY1, &posZ1);
    gluUnProject( winX, winY, 1.0f, modelview, projection, viewport, &posX2, &posY2, &posZ2);
    Ray selectRay = Ray(Vector3(posX1,posY1,posZ1), Vector3(posX1-posX2,posY1-posY2,posZ1-posZ2));
    
    return selectRay;
}
