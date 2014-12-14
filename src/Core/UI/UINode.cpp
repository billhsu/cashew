/*
 Shipeng Xu
 billhsu.x@gmail.com
 */
#include "UINode.h"
#include <iostream>
#include "Core/Util/Utility.h"

UINode::UINode(UINode* parent)
{
    strcpy(strID,"");
    mAlpha = 1.0f;
    mR = mG = mB = 1.0f;
    mIsVisible = true;
    
    mIsDisabled = false;
    mPosX = mPosY = 0;
    mParentNode = parent;
    
    mTimeAccu = 0.0f;
    
    isAnimation = false;
    
    nodeStatus = NODE_IDLE;
    
    previousPressed = NULL;
    previousHover = NULL;
    
    mCallBackFunc = 0;
    
    if(parent != NULL)
    {
        parent->mChildNodes.push_back(this);
    }
    std::cout<<"UINode("<<parent<<")"<<std::endl;
}

UINode::~UINode()
{
    std::cout<<"~UINode()"<<std::endl;
    for(mChildIter Child = mChildNodes.begin();
        Child != mChildNodes.end(); Child++)
    {
        delete *Child;
    }
    
}
void UINode::appearIn(float timeMs)
{
    isAnimation = true;
    timeMsAniStart = getMilliSec();
    timeMsTotalForAni = timeMs;
    aniStatus = UI_ANIM_IN;
    mIsVisible = true;
    if(mChildNodes.size()>0)
    {
        for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
        {
            (*Child)->isAnimation = isAnimation;
            (*Child)->timeMsAniStart = timeMsAniStart;
            (*Child)->timeMsTotalForAni = timeMsTotalForAni;
            (*Child)->aniStatus = aniStatus;
            (*Child)->mIsVisible = mIsVisible;
        }
    }
}
void UINode::appearOut(float timeMs)
{
    isAnimation = true;
    timeMsAniStart = getMilliSec();
    timeMsTotalForAni = timeMs;
    aniStatus = UI_ANIM_OUT;
    nodeStatus = NODE_IDLE;
    std::cout<<"UINode::appearOut "<<mChildNodes.size()<<std::endl;
    if(mChildNodes.size()>0)
    {
        for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
        {
            (*Child)->isAnimation = isAnimation;
            (*Child)->timeMsAniStart = timeMsAniStart;
            (*Child)->timeMsTotalForAni = timeMsTotalForAni;
            (*Child)->aniStatus = aniStatus;
            (*Child)->nodeStatus = NODE_IDLE;
        }
    }
}
void UINode::update(float timeDelta)
{
    for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
    {
        if((*Child)->mIsVisible) (*Child)->update(timeDelta);
    }
}

UINode* UINode::getNodeByPos(int x, int y)
{
    UINode* findNode = NULL;
    if(mChildNodes.size()>0)
    {
        for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
        {
            if((*Child)->insideNode(x, y) && (*Child)->getVisibility() == true)
            {
                findNode = (*Child);
                break;
            }
        }
    }
    
    return findNode;
}