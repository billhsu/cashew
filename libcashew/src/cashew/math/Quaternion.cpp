#include "cashew/math/Quaternion.h"

Vector3 Quaternion::X_AXIS = Vector3(1,0,0);
Vector3 Quaternion::Y_AXIS = Vector3(0,1,0);
Vector3 Quaternion::Z_AXIS = Vector3(0,0,1);

Vector3 Quaternion::X_NEG_AXIS = Vector3(-1,0,0);
Vector3 Quaternion::Y_NEG_AXIS = Vector3(0,-1,0);
Vector3 Quaternion::Z_NEG_AXIS = Vector3(0,0,-1);

float* Quaternion::getFloat()
{
    m[ 0] = 1.0f - 2.0f * ( y * y + z * z ); 
    m[ 1] = 2.0f * ( x * y - z * w );
    m[ 2] = 2.0f * ( x * z + y * w );
    m[ 3] = 0;

    m[ 4] = 2.0f * (x * y + z * w);
    m[ 5] = 1.0f - 2.0f * ( x * x + z * z );
    m[ 6] = 2.0f * ( y * z - x * w );
    m[ 7] = 0;

    m[ 8] = 2.0f * (x * z - y * w);
    m[ 9] = 2.0f * (z * y + x * w );
    m[10] = 1.0f - 2.0f * ( x * x + y * y );
    m[11] = 0;

    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;

    return m;
}

Matrix4& Quaternion::getMatrix()
{
    mat.set(getFloat());
    return mat;
};