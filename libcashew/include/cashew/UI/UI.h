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

class LuaTable;

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
            uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);

    UIButton* addButton(int id, const char* strID, 
            uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,  
            const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);

    UIRadioButton* addRadioButton(int id, int x, int y, int width, int height);

    UILabel* addLabel(int id, int x, int y, int width, int height,const char* text);

    UINode* MouseButton(int button, int state, int x, int y);
    UINode* PassiveMotion(int x, int y);

    static char uiHintText[128];
    static int hintTextPosX, hintTextPosY;
    enum{CASHEW_MOUSE_DOWN, CASHEW_MOUSE_UP, CASHEW_RIGHT_BUTTON, CASHEW_LEFT_BUTTON};
    void render(float timeDelta);
private:
    UI();
    ~UI();
    int mWindowWidth, mWindowHeight;
    std::vector <UINode*> nodeList;
    UINode* mRootNode;
    int luaGetNodePosX(const char *nodeName);
    int luaGetNodePosY(const char *nodeName);
    int luaGetNodeWidth(const char *nodeName);
    int luaGetNodeHeight(const char *nodeName);
    LuaTable *UILayout;

};