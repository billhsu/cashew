// Shipeng Xu
// billhsu.x@gmail.com

#include "Utility.h"
#include <stdio.h>

void checkGlErr(const char* file, int line)
{
#ifdef DEBUG
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %d - %s %d\n", err, file, line);
    }
#endif
}

void check_gl_err(const char* file, int line) {
    checkGlErr(file, line);
}