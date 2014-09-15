/* 
Shipeng Xu
billhsu.x@gmail.com

Thanks to GLUI2
*/
#pragma once

#include <iostream>
#include "UINode.h"
#include "UIButton.h"
#include "UIRadioButton.h"
#include "UILabel.h"
#include <vector>

class UI
{
public:
    static UI& getInstance()
    {
        static UI instance;
        std::cout <<"UI getInstance()"<<std::endl;
        return instance;
    }

    void resize(int width, int height);
    UINode* getNodeByPos(int x, int y);

    UIButton* addButton(int id, int x, int y, int width, int height, 
            GLuint textureID_idle, GLuint textureID_hover, GLuint textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);

    UIButton* addButton(int id, const char* strID, 
            GLuint textureID_idle, GLuint textureID_hover, GLuint textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);

    UIRadioButton* addRadioButton(int id, int x, int y, int width, int height);

    UILabel* addLabel(int id, int x, int y, int width, int height,const char* text);

    UINode* MouseButton(int button, int state, int x, int y);
    UINode* PassiveMotion(int x, int y);

    static char uiHintText[128];
    static int hintTextPosX, hintTextPosY;

    void render(float timeDelta);
private:
    UI();
    ~UI();
    int mWindowWidth, mWindowHeight;
    std::vector <UINode*> nodeList;
    UINode* mRootNode;
};