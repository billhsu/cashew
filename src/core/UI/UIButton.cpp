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
    if(textureID!=-1)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f); glVertex2f(mPosX,mPosY);
        glTexCoord2f(1.0f,0.0f); glVertex2f(mPosX+mWidth,mPosY);
        glTexCoord2f(1.0f,1.0f); glVertex2f(mPosX+mWidth,mPosY+mHeight);
        glTexCoord2f(0.0f,1.0f); glVertex2f(mPosX,mPosY+mHeight);
    glEnd();

    if(textureID!=-1) glDisable(GL_TEXTURE_2D);
}