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
    UINode* getNodeByPos(int x, int y);
    UIButton* addButton(int x, int y, int width, int height, GLuint textureID, 
            const char* text, void (*callback)(UINode* Sender));

    UILabel* addLabel(int x, int y, int width, int height,const char* text);

    bool MouseButton(int button, int state, int x, int y);
    bool PassiveMotion(int x, int y);

    void render(float timeDelta);
private:
    UI();
    ~UI();
    int mWindowWidth, mWindowHeight;
    UINode* mRootNode;
};