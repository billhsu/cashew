/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UI.h"

UI::UI()
{
    mRootNode = new UINode(NULL);
}

UI::~UI()
{
    delete mRootNode;
}

UIButton* UI::addButton(int x, int y, int width, int height, 
            const char* text, void (*callback)(UINode* Sender))
{
    UIButton* button = new UIButton(mRootNode);
    button->setPos(x, y);
    button->setText(text);
    button->setSize(width, height);
    button->SetCallback(callback);
    return button;
}

UILabel* UI:addLabel(int x, int y, int width, int height,const char* text)
{
    UILabel* label = new UILabel(mRootNode);
    label->setPos(x, y);
    label->setText(text);
    label->setSize(width, height);
    return label;
}

void UI:render(float timeDelta)
{
    glPushMatrix();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0, mWindowWidth, mWindowHeight, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    // Make sure we are in fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Render all children (this controller is the root of all controllers)
    mRootNode->_render(timeDelta);
    
    // End 2D mode
    glPopMatrix();
}
