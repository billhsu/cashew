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
    ANIM_TIME_MS = 300.0;
    animTime = 0.0f;
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
        Quaternion quat = Quaternion::fromEuler(rotate);
        glMultTransposeMatrixf(quat.getFloat());
        animTime = 0;
    }
    else
    {
        animTime += timeDelta;
        float alpha = animTime/ANIM_TIME_MS;
        if(animTime>=ANIM_TIME_MS)
        {
            animTime = 0;
            anim = false;
            rotate = rotateTo;
            distance = distanceTo;
            Quaternion quat0 = Quaternion::fromEuler(rotate);
            gluLookAt (0.0, 0.0, -distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            glMultTransposeMatrixf(quat0.getFloat());
        }
        else
        {
            float distanceTmp = distance*(1-alpha) + distanceTo*alpha;
            gluLookAt (0.0, 0.0, -distanceTmp, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            Quaternion quat0 = Quaternion::fromEuler(rotate);
            Quaternion quat1 = Quaternion::fromEuler(rotateTo);
            Quaternion quat2 = Quaternion::slerp(quat0, quat1, alpha);
            glMultTransposeMatrixf(quat2.getFloat());
        }
        
    }
    
    drawFPS(timeDelta);
}

void Camera::drawFPS(float timeDelta)
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
    snprintf(FPSchar, sizeof(FPSchar), "Width:%4d Height:%4d FPS:%3d tDelta:%.1f", 
        Controller::width, Controller::height, lastFPS, timeDelta);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)FPSchar);

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
