#ifdef __APPLE__
#include <GLUT/glut.h>
#include <string.h>
void glutBitmapString(void* fontID, const unsigned char *str);
#else
#include <GL/freeglut.h>
#endif