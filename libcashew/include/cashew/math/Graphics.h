#pragma once
#include "cashew/math/Matrices.h"

namespace cashew {
    Matrix4 gluLookAt(float eyex, float eyey, float eyez,
                   float centerx, float centery, float centerz,
                   float upx, float upy, float upz);
    Matrix4 glMultTransposeMatrix(Matrix4 m1, Matrix4 m2);
};
