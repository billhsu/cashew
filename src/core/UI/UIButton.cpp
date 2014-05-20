/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UIButton.h"
#include <iostream>
#include <GL/freeglut.h>
#include "../math/Vectors.h"

UIButton::UIButton(UINode* parent) : UINode(parent)
{
    std::cout<<"UIButton("<<parent<<")"<<std::endl;
}
UIButton::~UIButton()
{
    std::cout<<"~UIButton()"<<std::endl;
}
void UIButton::setText(const char* text)
{
    
}

void UIButton::render(float timeDelta)
{
    glColor4f(mR, mG, mB, mAlpha);
    glBegin(GL_QUADS);
        glVertex3fv(Vector3(mPosX,mPosY,0).cell);
        glVertex3fv(Vector3(mPosX+mWidth,mPosY,0).cell);
        glVertex3fv(Vector3(mPosX+mWidth,mPosY+mHeight,0).cell);
        glVertex3fv(Vector3(mPosX,mPosY+mHeight,0).cell);
    glEnd();
}