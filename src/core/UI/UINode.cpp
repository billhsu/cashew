/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UINode.h"

UINode::UINode(UINode* parent)
{
    mAlpha = 1.0f;
    mR = mG = mB = 1.0f;
    mIsVisible = true;
    
    mIsDisabled = false;
    mPosX = mPosY = 0;
    mParentNode = parent;

    mCallBackFunc = 0;
    
    if(parent != NULL)
    {
        parent->mChildNodes.push_back(this);
    }
}
UINode::~UINode()
{
    for(mChildIter Child = mChildNodes.begin(); 
            Child != mChildNodes.end(); Child++)
        delete *Child;
    
    if(mParentNode == NULL)
        return;
    
    for(mChildIter Index = mParentNode->mChildNodes.begin(); 
            Index != mParentNode->mChildNodes.end(); Index++)
    {
        if(*Index == this)
        {
            mParentNode->mChildNodes.erase(Index);
            break;
        }
    }
}

void UINode::_render(float timeDelta)
{
    render(timeDelta);
    for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
        (*Child)->_render(timeDelta);
}