/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include <GL/freeglut.h>
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

void UI::render(float timeDelta)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, mWindowWidth, 0, mWindowHeight,-1,1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    mRootNode->_render(timeDelta);
    
    glEnable( GL_DEPTH_TEST ) ;
    glMatrixMode( GL_PROJECTION ) ;
    glPopMatrix(); // revert back to the matrix I had before.
    glMatrixMode( GL_MODELVIEW ) ;
    glPopMatrix();
}
