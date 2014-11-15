#pragma once
#include <stdint.h>
#include "cashew/math/Matrices.h"

namespace cashew
{
Matrix4 gluLookAt(float eyex, float eyey, float eyez,
                  float centerx, float centery, float centerz,
                  float upx, float upy, float upz);

int32 gluUnProject(float winx, float winy, float winz,
                   const float modelMatrix[16],
                   const float projMatrix[16],
                   const int32 viewport[4],
                   float *objx, float *objy, float *objz);
};
