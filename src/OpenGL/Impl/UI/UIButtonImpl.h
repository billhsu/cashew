// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#include "Core/UI/UIButton.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include <iostream>
#include <OpenGL/gl3.h>

class UIButtonImpl : public UIButton {
   public:
    UIButtonImpl(UINode* parent) : UIButton(parent), indices{0, 1, 2, 0, 2, 3} {
        std::cout << "UIButtonImpl(" << this << ")" << std::endl;
    };
    ~UIButtonImpl();
    void render();
    void prepareRenderData();
    GLuint program;

   private:
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float verticesArray[8];
    float uvArray[8];
    float colorArray[16];
    int indices[6];
};