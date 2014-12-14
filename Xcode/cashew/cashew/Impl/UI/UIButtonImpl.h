// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/UI/UIButton.h"

class UIButtonImpl : public UIButton
{
public:
    UIButtonImpl(UINode* parent) : UIButton(parent){};
    void render();
};