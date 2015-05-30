// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#import <OpenGL/gl3.h>

void checkGlErr(const char* file, int line);
#ifdef __cplusplus
extern "C" {
#endif
    void check_gl_err(const char* file, int line);
#ifdef __cplusplus
}
#endif