/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UIRadioButton.h"

UIRadioButton::UIRadioButton(UINode* parent) : UINode(parent)
{
    previousPressed = NULL;
    previousHover = NULL;
}
UIRadioButton::~UIRadioButton()
{
    
}

void UIRadioButton::MouseButton(int button, int state, int x, int y)
{
    UINode* node = getNodeByPos(x, y);
    if(state == 0)
    {
        if(previousPressed!=NULL) previousPressed->nodeStatus = UINode::NODE_IDLE;
        node->nodeStatus = UINode::NODE_PRESS;
        previousPressed = node;
    }
    if(state == 1 && node!=NULL && node == previousPressed)
    {
        if(node->mCallBackFunc!=NULL) node->mCallBackFunc(NULL);
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
            previousHover->nodeStatus = UINode::NODE_IDLE;
            node->nodeStatus = UINode::NODE_HOVER;
            previousHover = node;
        }
    }
    else
    {
        if(previousHover != NULL)
        {
            previousHover->nodeStatus = UINode::NODE_IDLE;
            previousHover = NULL;
        }
    }
    

}
void UIRadioButton::render(float timeDelta)
{
    
}
