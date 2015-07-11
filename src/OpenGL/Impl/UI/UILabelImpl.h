// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#include "Core/UI/UILabel.h"
#include "OpenGL/HardwareBuffer/HardwareBuffer.h"
#include <iostream>
#include <OpenGL/gl3.h>

class UILabelImpl : public UILabel {
public:
    UILabelImpl(UINode* parent) : UILabel(parent), indices{0,1,2, 0,2,3} {
        std::cout<<"UILabelImpl("<<this<<")"<<std::endl;
    };
    ~UILabelImpl();
    void render();
    void prepareRenderData();
    GLuint program;
private:
    HardwareBuffer buffer;
    HardwareBuffer::VBOStruct VBOInfo;
    float verticesArray[8];
    float colorArray[16];
    int indices[6];
};