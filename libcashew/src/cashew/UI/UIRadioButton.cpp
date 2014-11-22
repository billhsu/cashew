/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "cashew/UI/UIRadioButton.h"
#include <iostream>

UIRadioButton::UIRadioButton(UINode* parent) : UINode(parent)
{
    std::cout<<"UIRadioButton("<<parent<<")"<<std::endl;
}
UIRadioButton::~UIRadioButton()
{
    
}

void UIRadioButton::MouseButton(int button, int state, int x, int y)
{
    UINode* node = this->getNodeByPos(x, y);
    if(node != NULL)
    {
        if(state == 0)
        {
            if(previousPressed==NULL)
            {
                node->nodeStatus = UINode::NODE_PRESS;
                previousPressed = node;
                if(node->mCallBackFunc!=NULL) node->mCallBackFunc(NULL);
            }
            else
            {
                previousPressed->nodeStatus = UINode::NODE_IDLE;
                node->nodeStatus = UINode::NODE_PRESS;
                previousPressed = node;
                if(node->mCallBackFunc!=NULL) node->mCallBackFunc(NULL);
            }
        }
    }
}

void UIRadioButton::PassiveMotion(int x, int y)
{
    UINode* node = getNodeByPos(x, y);
    if(node!=NULL)
    {
        if(previousHover == NULL)
        {
            if(node->nodeStatus == UINode::NODE_IDLE)
            {
                node->nodeStatus = UINode::NODE_HOVER;
                previousHover = node;
            }
        }
        else if(previousHover != node)
        {
            if(previousHover->nodeStatus == UINode::NODE_HOVER)
                previousHover->nodeStatus = UINode::NODE_IDLE;
            if(node->nodeStatus==UINode::NODE_IDLE)
                node->nodeStatus = UINode::NODE_HOVER;
            previousHover = node;
        }
    }
    else
    {
        if(previousHover != NULL)
        {
            if(previousHover->nodeStatus == UINode::NODE_HOVER)
                previousHover->nodeStatus = UINode::NODE_IDLE;
            previousHover = NULL;
        }
    }
}
void UIRadioButton::render(float timeDelta)
{
    
}
