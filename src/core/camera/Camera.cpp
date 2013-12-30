#include "Camera.h"
#include <GL/glut.h>

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
        glRotatef(rotate.x,1.0f,0.0f,0.0f);
        glRotatef(rotate.y,0.0f,1.0f,0.0f);
        glRotatef(rotate.z,0.0f,0.0f,1.0f);
    }
    else
    {
        bool distOK = false;
        bool rotXOK = false;
        bool rotYOK = false;
        bool rotZOK = false;

        if(distanceDelta*(distanceTo - distance)>0) 
            distance = distance + (distanceDelta>0?1:-1)*timeDelta*5.0f;
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
