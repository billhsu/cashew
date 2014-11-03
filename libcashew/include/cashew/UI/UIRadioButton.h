/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once

#include "UINode.h"

class UIRadioButton : public UINode
{
public:
    UIRadioButton(UINode* parent);
    ~UIRadioButton();

    void render(float timeDelta);
    void MouseButton(int button, int state, int x, int y);
    void PassiveMotion(int x, int y);

private:
    
};