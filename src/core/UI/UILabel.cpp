/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UILabel.h"

UILabel::UILabel(UINode* parent) : UINode(parent)
{

}
UILabel::~UILabel()
{
    
}

void UILabel::render(float timeDelta)
{
    glColor4f(mR, mG, mB, mAlpha);
    glRasterPos2f(mPosX, mPosY);
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)mText);
}

void UILabel::setText(const char* text)
{
    strcpy(mText, text);
}