/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UINode.h"
#include <iostream>

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

void UINode::_render(float timeDelta)
{
    render(timeDelta);
    for(mChildIter Child = mChildNodes.begin(); Child != mChildNodes.end(); Child++)
        (*Child)->_render(timeDelta);
}