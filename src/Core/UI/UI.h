/*
 Shipeng Xu
 billhsu.x@gmail.com
 
 Thanks to GLUI2
 */
#pragma once

#include <iostream>
#include <vector>
#include <stdint.h>
#include "Core/Math/Matrices.h"

class LuaTable;
class UIButton;
class UINode;

class UI
{
public:
    void resize(int width, int height);
    UINode* getNodeByPos(int x, int y);
    
    UINode* MouseButton(int button, int state, int x, int y);
    UINode* PassiveMotion(int x, int y);
    
    void update(float timeDelta);
    virtual UIButton* addButton(int id, int x, int y, int width, int height,
                                    uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                                    const char* text, void (*callback)(void* data), void* userData = NULL, UINode* parent = NULL){return NULL;};
    
    virtual UIButton* addButton(int id, const char* strID,
                                    void (*callback)(void* data), void* userData = NULL, UINode* parent = NULL){return NULL;};


    static char uiHintText[128];
    static int hintTextPosX, hintTextPosY;
    virtual void render(){}
    static int getWindowWidth()
    {
        return mWindowWidth;
    }
    static int getWindowHeight()
    {
        return mWindowHeight;
    }
    static int getMouseX()
    {
        return mMouseX;
    }
    static int getMouseY()
    {
        return mMouseY;
    }
    static Matrix4 getProjection();
    static Matrix4 getModelView();
    typedef void (*UICallback)(void* data);
    struct UICallbackWithObject
    {
        UICallback callback;
        void* data;
    };
    static void addToUICallbackList(UICallback callback, void* data = NULL)
    {
        UICallbackWithObject callbackWithData;
        callbackWithData.callback = callback;
        callbackWithData.data = data;
        uiCallbackList.push_back(callbackWithData);
    }
protected:
    UI();
    virtual ~UI();
    static int mWindowWidth, mWindowHeight;
    static int mMouseX, mMouseY;
    std::vector <UINode*> nodeList;
    UINode* mRootNode;
    int luaGetNodePosX(const char *nodeName);
    int luaGetNodePosY(const char *nodeName);
    int luaGetNodeWidth(const char *nodeName);
    int luaGetNodeHeight(const char *nodeName);
    std::string luaGetTextureName(const char *nodeName, const char *nodeTexture);
    std::string luaGetNodeText(const char *nodeName);
    LuaTable *UILayout;

private:
    static std::vector<UICallbackWithObject> uiCallbackList;
    void clearUICallbackList()
    {
        uiCallbackList.clear();
    }
    void runUICallbackList()
    {
        for_each(uiCallbackList.begin(), uiCallbackList.end(),
                 [](UICallbackWithObject callbackWithObj){callbackWithObj.callback(callbackWithObj.data);});
    }
};