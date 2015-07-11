/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include <iostream>
#include <math.h>
#include "UI.h"
#include "UILabel.h"
#include "Core/Math/Vectors.h"
#include "Core/Util/Utility.h"

UILabel::UILabel(UINode* parent) : UINode(parent) {
    std::cout<<"UILabel("<<parent<<")"<<std::endl;
}
UILabel::~UILabel() {
    std::cout<<"~UILabel()"<<std::endl;
}
void UILabel::setText(const char* text) {
    strcpy(mText, text);
}

void UILabel::setColor(Vector4 color) {
    backgroundColor = color;
}

void UILabel::update(float timeDelta) {
    vertices[0].x = mPosX;           vertices[0].y = mPosY;
    vertices[1].x = mPosX + mWidth;  vertices[1].y = mPosY;
    vertices[2].x = mPosX + mWidth;  vertices[2].y = mPosY + mHeight;
    vertices[3].x = mPosX;           vertices[3].y = mPosY + mHeight;
}