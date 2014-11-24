#ifndef __GLU_PROJECT_CASHEW
#define __GLU_PROJECT_CASHEW

#include <stdint.h>
#include "Core/Math/Matrices.h"
namespace cashew
{
    
    Matrix4
    gluPerspective(float fovy, float aspect, float zNear, float zFar);
    
    Matrix4
    gluLookAt(float eyex, float eyey, float eyez, float centerx,
              float centery, float centerz, float upx, float upy,
              float upz);
    
    int32_t
    gluProject(float objx, float objy, float objz,
               const float modelMatrix[16],
               const float projMatrix[16],
               const int32_t viewport[4],
               float *winx, float *winy, float *winz);
    
    int32_t
    gluUnProject(float winx, float winy, float winz,
                 const float modelMatrix[16],
                 const float projMatrix[16],
                 const int32_t viewport[4],
                 double *objx, double *objy, double *objz);
    
    int32_t
    gluUnProject4(float winx, float winy, float winz, float clipw,
                  const float modelMatrix[16],
                  const float projMatrix[16],
                  const int32_t viewport[4],
                  float nearVal, float farVal,
                  float *objx, float *objy, float *objz,
                  float *objw);

};
#endif