/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include <GL/freeglut.h>
#include <iostream>
#include "UI.h"

UI::UI()
{
    mRootNode = new UINode(NULL);
    previousPressed = NULL;
    previousHover = NULL;
    std::cout <<"UI()"<<std::endl;
}

UI::~UI()
{
    delete mRootNode;
    std::cout <<"~UI()"<<std::endl;
}

UINode* UI::getNodeByPos(int x, int y)
{
    return mRootNode->getNodeByPos(x, y);
}

UIButton* UI::addButton(int id, int x, int y, int width, int height, 
            GLuint textureID_idle, GLuint textureID_hover, GLuint textureID_press,  
            const char* text, void (*callback)(UINode* Sender))
{
    UIButton* button = new UIButton(mRootNode);
    button->nodeID = id;
    button->textureID_idle = textureID_idle;
    button->textureID_hover = textureID_hover;
    button->textureID_press = textureID_press;
    button->setPos(x, y);
    button->setText(text);
    button->setSize(width, height);
    button->setCallback(callback);
    return button;
}

UILabel* UI::addLabel(int x, int y, int width, int height, const char* text)
{
    UILabel* label = new UILabel(mRootNode);
    label->setPos(x, y);
    label->setText(text);
    label->setSize(width, height);
    return label;
}

UINode* UI::MouseButton(int button, int state, int x, int y)
{
    UINode* node = getNodeByPos(x, y);
    if(node!=NULL && state == 0)
    {
        if(previousPressed!=NULL) previousPressed->nodeStatus = UINode::NODE_IDLE;
        node->nodeStatus = UINode::NODE_PRESS;
        previousPressed = node;
        return node;
    }
    else
    {
        if(state == 1 && node!=NULL && node == previousPressed)
        {
            if(node->mCallBackFunc!=NULL) node->mCallBackFunc(NULL);
        }

        if(previousPressed!=NULL)
        {
            //if(previousHover!=NULL)
            //    previousPressed->nodeStatus = UINode::NODE_HOVER;
            //else
            //    previousPressed->nodeStatus = UINode::NODE_IDLE;

            //previousPressed = NULL;
        }
        return NULL;
    }
}

UINode* UI::PassiveMotion(int x, int y)
{
    UINode* node = getNodeByPos(x, y);
    if(node!=NULL)
    {
        if(previousHover!=NULL && previousHover!=node)
        {
            if(previousHover->nodeStatus==UINode::NODE_HOVER) 
            {
                previousHover->nodeStatus = UINode::NODE_IDLE;
            }
            previousHover = NULL;
        }
        if(node->nodeStatus==UINode::NODE_IDLE) 
        {
            node->nodeStatus = UINode::NODE_HOVER;
            previousHover = node;
        }
        return node;
    }
    else
    {
        if(previousHover!=NULL)
        {
            if(previousHover->nodeStatus==UINode::NODE_HOVER)
            {
                previousHover->nodeStatus = UINode::NODE_IDLE;
            }
            previousHover = NULL;
        }
        return NULL;
    }
}

void UI::render(float timeDelta)
{
    glMatrixMode( GL_PROJECTION ) ;
    glPushMatrix() ; // save
    glLoadIdentity();// and clear

    glOrtho(0, mWindowWidth, 0, mWindowHeight,-1,1);
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glLoadIdentity() ;

    glScalef(1, -1, 1);           // Invert Y axis so increasing Y goes down.
    glTranslatef(0.0f, (float)-mWindowHeight, 0.0f); 

    glDisable(GL_LIGHTING);
    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mRootNode->_render(timeDelta);

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix(); // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}
