/*
 Shipeng Xu
 billhsu.x@gmail.com
 */
#pragma once

#include "UINode.h"
#include "Core/Math/Vectors.h"

class UIButton : public UINode {
   public:
    UIButton(UINode* parent);
    virtual ~UIButton();

    void MouseButton(int button, int state, int x, int y);
    void PassiveMotion(int x, int y);

    void setText(const char* text);
    void update(float timeDelta);

    uint32_t textureID_idle, textureID_hover, textureID_press;
    Vector2 vertices[4];

   private:
};