/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include "UINode.h"
class UILabel : public UINode
{
public:
    UILabel(UINode* parent);
    ~UILabel();
    void setText(const char* text);
    char* getText();

    void render(float timeDelta);

private:
};