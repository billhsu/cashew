#include "cashew/camera/Camera.h"
#include "cashew/scene/Controller.h"
#include "cashew/util/Utility.h"
#include "cashew/scene/Scene.h"
#include "cashew/math/Vectors.h"
#include "cashew/scene/Plane.h"
#include "cashew/scene/Controller.h"
#include "cashew/UI/UI.h"


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
    
    snprintf(FPSchar, sizeof(FPSchar), "Width:%4d Height:%4d FPS:%3d", 
        Controller::width, Controller::height, lastFPS);
    Controller::lbFPS->setText(FPSchar);
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
    Ray selectRay = Ray(Vector3(posX1,posY1,posZ1), Vector3(posX2-posX1,posY2-posY1,posZ2-posZ1));
    
    return selectRay;
}

Vector3 Camera::getDirection()
{
    return Quaternion::toVector(rotate);
}

bool Camera::getPoint(Vector3& p, const Plane& plane, bool mode)
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
    if(!findCurr||mode==GETPOINT_PLANE) p = intersect(ray, plane);

    return findCurr;
}

int Camera::getLine(LineSegment& line)
{
    Ray ray = getRay();
    Vector3 v1 = ray.GetOrigin();
    Vector3 v2 = v1 + ray.GetDirection()*100.0f;
    LineSegment l;
    l.points[0] = v1;
    l.points[1] = v2;
    float minDist = 1000.0f;
    int linePos=-1;
    for(int i=0; i<Controller::sketchLines.size(); ++i)
    {
        float dist = distSegmentSegment(Controller::sketchLines[i],l);
        if(dist<=0.1f)
        {
            minDist = dist;
            line = Controller::sketchLines[i];
            linePos = i;
        }
    }
    return linePos;

}
