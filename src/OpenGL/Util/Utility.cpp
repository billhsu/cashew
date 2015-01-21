// Shipeng Xu
// billhsu.x@gmail.com

#include "Utility.h"
#include <iostream>
#include <string>
void checkGlErr(const std::string& file, int line)
{
#ifdef DEBUG
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err <<" "<<file<< " "<<line<<std::endl;
    }
#endif
}