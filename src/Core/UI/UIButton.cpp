/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include <iostream>
#include <math.h>
#include "UI.h"
#include "UIButton.h"
#include "Core/Math/Vectors.h"
#include "Core/Util/Utility.h"

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
        mTimeAccu = 0.0f;
    }
    else if(state == 1)
    {
        if(mCallBackFunc!=NULL) mCallBackFunc(this);
        nodeStatus = UINode::NODE_IDLE;
        mTimeAccu = 0.0f;
        if(insideNode(x, y))
        {
            nodeStatus = UINode::NODE_HOVER;
            mTimeAccu = 0.0f;
        }
    }
}

void UIButton::PassiveMotion(int x, int y)
{
    if(insideNode(x, y))
    {
        if(UINode::NODE_HOVER != nodeStatus)
        {
            nodeStatus = UINode::NODE_HOVER;
            mTimeAccu = 0.0f;
        }
    }
    else
    {
        nodeStatus=UINode::NODE_IDLE;
        mTimeAccu = 0.0f;
    }
}

void UIButton::update(float timeDelta)
{
    float _alpha = mAlpha;
    float _height = mHeight;
    float _width = mWidth;
    
    mTimeAccu += timeDelta;
    
    if(isAnimation)
    {
        long curTimeMs = getMilliSec();
        float factor = (float)(curTimeMs - timeMsAniStart) / timeMsTotalForAni;
        if(aniStatus == UI_ANIM_IN)
        {
            _alpha  = mAlpha  * factor;
            _height = mHeight * sin(factor * 90 * PI / 180);
            _width  = mWidth  * sin(factor * 90 * PI / 180);
            if(curTimeMs - timeMsAniStart >= timeMsTotalForAni)
            {
                isAnimation = false;
            }
        }
        if(aniStatus == UI_ANIM_OUT)
        {
            factor  = 1.0f    - factor;
            _alpha  = mAlpha  * factor;
            _height = mHeight * sin(factor*90*PI/180);
            _width  = mWidth  * sin(factor*90*PI/180);
            if(curTimeMs - timeMsAniStart >= timeMsTotalForAni)
            {
                isAnimation = false;
                mIsVisible = false;
            }
        }
    }
    else if(nodeStatus == NODE_HOVER)
    {
        _height = mHeight * (0.96f + 0.04f * cos(mTimeAccu/90.0f));
        _width  = mWidth  * (0.96f + 0.04f * cos(mTimeAccu/90.0f));
    }
    
    uint32_t textureID = -1;
    if(nodeStatus == UINode::NODE_IDLE) textureID = textureID_idle;
    else if(nodeStatus == UINode::NODE_HOVER) textureID = textureID_hover;
    else if(nodeStatus == UINode::NODE_PRESS) textureID = textureID_press;
    
    
    float offset_x = (mWidth  - _width ) / 2.0f;
    float offset_y = (mHeight - _height) / 2.0f;
    
    
    if(nodeStatus == NODE_HOVER && mTimeAccu >= 600)
    {
        offset_x = 0.0f;
        offset_y = 0.0f;
        if(UI::getMouseX()>=UI::getWindowWidth() - mWidth - 100) offset_x = - (strlen(mText) * 9);
        if(UI::getMouseY()>=UI::getWindowHeight() - mHeight - 100) offset_y = - 15;
        strcpy(UI::uiHintText, mText);
        UI::hintTextPosX = UI::getMouseX() + offset_x;
        UI::hintTextPosY = UI::getMouseY() + offset_y;
    }
}