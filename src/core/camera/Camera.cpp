#include "Camera.h"
#include <GL/freeglut.h>
#include "../scene/Controller.h"
#include "../../impl/Utility.h"
#include "../scene/Scene.h"


Camera::Camera()
{
    anim = false;
    distance = 10.0f;
    distanceTo = distance;
    distanceDelta = 0.0f;
    rotate = Quaternion::fromEuler(-30,0,0);
    camCenter = Vector3(0,0,0);
    lastTimeMS = getMilliSec();
    FPS = 0;
    lastFPS = 0;
    ANIM_TIME_MS = 300.0;
    animTime = 0.0f;
    rotChange = false;
    centerChange = false;
    distChange = false;
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
        gluLookAt (0.0f, 0.0f, 0.0f -distance,
            0.0f, 0.0f, 0.0f, 0.0, 1.0, 0.0);
        glMultTransposeMatrixf(rotate.getFloat());
        animTime = 0;
        glTranslatef(-camCenter.x, -camCenter.y, -camCenter.z);
    }
    else
    {
        animTime += timeDelta;
        float alpha = animTime/ANIM_TIME_MS;
        if(animTime>=ANIM_TIME_MS)
        {
            animTime = 0;
            anim = false;
            if(rotChange) rotate = rotateTo;
            if(distChange) distance = distanceTo;
            if(centerChange) camCenter = camCenterTo;
            
            rotChange = false;
            centerChange = false;
            distChange = false;

            Controller::rotate = Quaternion::toEuler(rotate);
            std::cout<<"Quaternion::toEuler "<<Controller::rotate<<std::endl;
            gluLookAt (0.0f, 0.0f, 0.0f -distance,
                0.0f, 0.0f, 0.0f, 0.0, 1.0, 0.0);
            glMultTransposeMatrixf(rotate.getFloat());
            glTranslatef(-camCenter.x, -camCenter.y, -camCenter.z);
        }
        else
        {
            float distanceTmp = distance*(1-alpha) + distanceTo*alpha;
            Quaternion quat = Quaternion::slerp(rotate, rotateTo, alpha);
            gluLookAt (0.0f, 0.0f, 0.0f -distanceTmp,
                0.0f, 0.0f, 0.0f, 0.0, 1.0, 0.0);
            glMultTransposeMatrixf(quat.getFloat());
            Vector3 camCenterTmp = camCenter*(1-alpha) + camCenterTo*alpha;
            glTranslatef(-camCenterTmp.x, -camCenterTmp.y, -camCenterTmp.z);
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

    glDisable(GL_LIGHTING);
    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top
    glColor3f(0.3f, 0.3f, 0.3f);
    glRasterPos2f(10, 20);
    snprintf(FPSchar, sizeof(FPSchar), "Width:%4d Height:%4d FPS:%3d", 
        Controller::width, Controller::height, lastFPS);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)FPSchar);

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix(); // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}

Ray Camera::getRay()
{
    int mx = Controller::mouseX;
    int my = Controller::mouseY;
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY;
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

bool Camera::getPoint(Vector3& p, const Plane& plane)
{
    float minDist = 1000.0f;
    bool findCurr = false;
    Ray ray = getRay();

    for(int i=0; i<Controller::sketchLines.size(); ++i)
    {
        for(int j=0; j<2; ++j)
        {
            if(distRayPoint(ray,Controller::sketchLines[i].points[j])<0.1f)
            {
                if((ray.GetOrigin() - Controller::sketchLines[i].points[j]).length()<minDist)
                {
                    minDist = (ray.GetOrigin() - Controller::sketchLines[i].points[j]).length();
                    p = Controller::sketchLines[i].points[j];
                    findCurr = true;
                }
            }
        }
    }
    if(!findCurr) p = intersect(ray, plane);

    return findCurr;
}