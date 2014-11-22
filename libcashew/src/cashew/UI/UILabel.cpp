/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "cashew/UI/UILabel.h"

UILabel::UILabel(UINode* parent) : UINode(parent)
{

}
UILabel::~UILabel()
{
    
}

void UILabel::setText(const char* text)
{
    strcpy(mText, text);
}