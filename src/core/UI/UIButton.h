/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include "UINode.h"

class UIButton : public UINode
{
public:
    UIButton(UINode* parent);
    ~UIButton();
    
    void setText(const char* text);
    void render(float timeDelta);
private:

};