/*
 Shipeng Xu
 billhsu.x@gmail.com
 */
#pragma once

#include "UINode.h"
#include "Core/Math/Vectors.h"

class UILabel : public UINode
{
public:
    UILabel(UINode* parent);
    virtual ~UILabel();

    void setText(const char* text);
    void setColor(Vector4 color);
    void update(float timeDelta);
    
    Vector2 vertices[4];
private:
};