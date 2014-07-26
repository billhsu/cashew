/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UIButton.h"
#include <iostream>
#include <GL/freeglut.h>
#include "../math/Vectors.h"
#include "Utility.h"

UIButton::UIButton(UINode* parent) : UINode(parent)
{
    textureID_idle = textureID_hover = textureID_press = -1;
    std::cout<<"UIButton("<<parent<<")"<<std::endl;
}
UIButton::~UIButton()
{
    std::cout<<"~UIButton()"<<std::endl;
}
void UIButton::setText(const char* text)
{
    strcpy(mText, text);
}

void UIButton::MouseButton(int button, int state, int x, int y)
{
    if(state == 0)
    {
        nodeStatus = UINode::NODE_PRESS;
    }
    else if(state == 1)
    {
        if(mCallBackFunc!=NULL) mCallBackFunc(NULL);
        nodeStatus = UINode::NODE_IDLE;
        if(insideNode(x, y)) nodeStatus = UINode::NODE_HOVER;
    }
}

void UIButton::PassiveMotion(int x, int y)
{
    if(insideNode(x, y))
    {
        nodeStatus = UINode::NODE_HOVER;
    }
    else
    {
        nodeStatus=UINode::NODE_IDLE;
    }
}

void UIButton::render(float timeDelta)
{
    float alpha = mAlpha;
    if(isAnimation)
    {
        std::cout<<"isAnimation"<<std::endl;
        long curTimeMs = getMilliSec();
        if(aniStatus == UI_ANIM_IN)
        {
            alpha = mAlpha * (curTimeMs - timeMsAniStart) / timeMsTotalForAni;
            if(curTimeMs - timeMsAniStart >= timeMsTotalForAni)
            {
                isAnimation = false;
            }
        }
        if(aniStatus == UI_ANIM_OUT)
        {
            alpha = mAlpha * (1.0f - ((float)(curTimeMs - timeMsAniStart) / timeMsTotalForAni));
            if(curTimeMs - timeMsAniStart >= timeMsTotalForAni)
            {
                isAnimation = false;
                mIsVisible = false;
            }
        }
        std::cout<<"alpha: "<<alpha<<curTimeMs<<std::endl;
    }
    glColor4f(mR, mG, mB, alpha);
    GLuint textureID = -1;
    if(nodeStatus == UINode::NODE_IDLE) textureID = textureID_idle;
    else if(nodeStatus == UINode::NODE_HOVER) textureID = textureID_hover;
    else if(nodeStatus == UINode::NODE_PRESS) textureID = textureID_press;
    
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