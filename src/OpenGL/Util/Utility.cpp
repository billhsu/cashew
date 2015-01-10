#include "Utility.h"
#include <iostream>
#include <string>
void checkGlErr(const std::string& file, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err <<" "<<file<< " "<<line<<std::endl;
    }
}