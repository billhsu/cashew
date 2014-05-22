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
    
    GLuint textureID_idle, textureID_hover, textureID_press;
private:

};