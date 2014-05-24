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

    void resize(int width, int height)
    {
        mWindowWidth = width;
        mWindowHeight = height;
    }
    UINode* getNodeByPos(int x, int y);

    UIButton* addButton(int id, int x, int y, int width, int height, 
            GLuint textureID_idle, GLuint textureID_hover, GLuint textureID_press,  
            const char* text, void (*callback)(UINode* Sender));

    UILabel* addLabel(int x, int y, int width, int height,const char* text);

    UINode* MouseButton(int button, int state, int x, int y);
    UINode* PassiveMotion(int x, int y);

    void render(float timeDelta);
private:
    UI();
    ~UI();
    int mWindowWidth, mWindowHeight;
    UINode* mRootNode;
    UINode* previousPressed;
    UINode* previousHover;
};