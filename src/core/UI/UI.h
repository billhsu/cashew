/* 
Shipeng Xu
billhsu.x@gmail.com

Thanks to GLUI2
*/
#pragma once

#include <iostream>
#include "UINode.h"
#include "UIButton.h"
#include "UILabel.h"

class UI
{
public:
    static UI& getInstance()
    {
        static UI instance;
        std::cout <<"UI getInstance()"<<std::endl;
        return instance;
    }

    void setWindowSize(int width, int height)
    {
        mWindowWidth = width;
        mWindowHeight = height;
    }

    UIButton* addButton(int x, int y, int width, int height, 
            const char* text, void (*callback)(UINode* Sender));

    UILabel* addLabel(int x, int y, int width, int height,const char* text);

    void render(float timeDelta);
private:
    UI();
    ~UI();
    int mWindowWidth, mWindowHeight;
    UINode* mRootNode;
};