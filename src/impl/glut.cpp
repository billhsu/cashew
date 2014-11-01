#include "glut.h"
#ifdef __APPLE__
void glutBitmapString(void* fontID, const unsigned char *str)
{
    for(int i = 0; i < strlen((char*)str); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
    }
}
#else
#endif