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
#include "Core/Controller/Mouse.h"

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
    if(state == Mouse::MOUSE_DOWN)
    {
        nodeStatus = UINode::NODE_PRESS;
        mTimeAccu = 0.0f;
    }
    else if(state == Mouse::MOUSE_UP)
    {
        if(mCallBackFunc!=NULL && insideNode(x, y))
        {
            UI::addToUICallbackList(mCallBackFunc, userDataObject);
        }
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
    
    vertices[0].x = mPosX + offset_x;         vertices[0].y = mPosY + offset_y;
    vertices[1].x = mPosX + offset_x +_width; vertices[1].y = mPosY + offset_y;
    vertices[2].x = mPosX + offset_x +_width; vertices[2].y = mPosY + offset_y +_height;
    vertices[3].x = mPosX + offset_x;         vertices[3].y = mPosY + offset_y +_height;

    if(nodeStatus == NODE_HOVER && mTimeAccu >= 600)
    {
        strcpy(UI::uiHintText, mText);
        UI::hintTextPosX = UI::getMouseX();
        UI::hintTextPosY = UI::getMouseY();
    }
}