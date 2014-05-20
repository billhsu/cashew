/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UIButton.h"
#include <iostream>
UIButton::UIButton(UINode* parent) : UINode(parent)
{
    std::cout<<"UIButton("<<parent<<")"<<std::endl;
}
UIButton::~UIButton()
{
    std::cout<<"~UIButton()"<<std::endl;
}
void UIButton::setText(const char* text)
{
    
}

void UIButton::render(float timeDelta)
{
    
}