/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include <iostream>
#include "UI.h"
#include "Core/Controller/Mouse.h"
#include "Core/Graphics/Project.h"
#include "Core/Scripting/luaUtility.h"
#include "Core/Scripting/luatables.h"
#include "UINode.h"
#include "UIButton.h"
#include "UILabel.h"

char UI::uiHintText[128];
int UI::hintTextPosX, UI::hintTextPosY;
int UI::mWindowWidth, UI::mWindowHeight;
int UI::mMouseX, UI::mMouseY;

std::vector<UI::UICallbackWithObject> UI::uiCallbackList;

UI::UI() {
    mRootNode = new UINode(NULL);
    UILayout = LuaTable::fromFile("lua_scripts/UILayout.lua");
    std::cout << "UI()" << std::endl;
}

UI::~UI() {
    delete mRootNode;
    std::cout << "~UI()" << std::endl;
}
int UI::luaGetNodePosX(const char* nodeName) {
    std::string stringValue =
        (*UILayout)[nodeName]["pos"]["x"].get<std::string>();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodePosY(const char* nodeName) {
    std::string stringValue =
        (*UILayout)[nodeName]["pos"]["y"].get<std::string>();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodeWidth(const char* nodeName) {
    std::string stringValue =
        (*UILayout)[nodeName]["size"]["width"].get<std::string>();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

int UI::luaGetNodeHeight(const char* nodeName) {
    std::string stringValue =
        (*UILayout)[nodeName]["size"]["height"].get<std::string>();
    lua_evaluate_expression(UILayout->L, stringValue.c_str());
    int result = lua_tonumber(UILayout->L, -1);
    lua_pop(UILayout->L, 1);
    return result;
}

std::string UI::luaGetTextureName(const char* nodeName,
                                  const char* nodeTexture) {
    std::string stringValue =
        (*UILayout)[nodeName]["textures"][nodeTexture].get<std::string>();
    return stringValue;
}

std::string UI::luaGetNodeText(const char* nodeName) {
    std::string stringValue = (*UILayout)[nodeName]["text"].get<std::string>();
    return stringValue;
}

void UI::resize(int width, int height) {
    mWindowWidth = width;
    mWindowHeight = height;
    lua_pushnumber(UILayout->L, width);
    lua_setglobal(UILayout->L, "window_width");
    lua_pushnumber(UILayout->L, height);
    lua_setglobal(UILayout->L, "window_height");
    for (int i = 0; i < nodeList.size(); ++i) {
        if (strcmp(nodeList[i]->strID, "") == 0)
            continue;
        nodeList[i]->setPos(luaGetNodePosX(nodeList[i]->strID),
                            luaGetNodePosY(nodeList[i]->strID));
        nodeList[i]->setSize(luaGetNodeWidth(nodeList[i]->strID),
                             luaGetNodeHeight(nodeList[i]->strID));
    }
    update(0);
}

UINode* UI::getNodeByPos(int x, int y) {
    return mRootNode->getNodeByPos(x, y);
}

UINode* UI::getNodeById(int id) {
    for (int i = 0; i < nodeList.size(); ++i) {
        if (nodeList[i]->nodeID == id) {
            return nodeList[i];
        }
    }
    return NULL;
}
UINode* UI::MouseButton(int button, int state, int x, int y) {
    mMouseX = x;
    mMouseY = y;
    UINode* node = getNodeByPos(x, y);
    if (node != NULL && state == Mouse::MOUSE_ACTION_DOWN) {
        node->MouseButton(button, state, x, y);
        mRootNode->previousPressed = node;
    }

    if (state == Mouse::MOUSE_ACTION_UP && mRootNode->previousPressed != NULL) {
        mRootNode->previousPressed->MouseButton(button, state, x, y);
        mRootNode->previousPressed = NULL;
    }

    return node;
}

UINode* UI::PassiveMotion(int x, int y) {
    mMouseX = x;
    mMouseY = y;
    UINode* node = getNodeByPos(x, y);
    if (node != NULL) {
        if (mRootNode->previousHover == NULL) {
            node->PassiveMotion(x, y);
            mRootNode->previousHover = node;
            return node;
        } else if (mRootNode->previousHover != node) {
            mRootNode->previousHover->PassiveMotion(x, y);
            node->PassiveMotion(x, y);
            mRootNode->previousHover = node;
            return node;
        } else {
            node->PassiveMotion(x, y);
        }
    } else if (mRootNode->previousHover != NULL) {
        mRootNode->previousHover->PassiveMotion(x, y);
        mRootNode->previousHover = NULL;
    }
    return NULL;
}

void UI::update(float timeDelta) {
    mRootNode->update(timeDelta);
    runUICallbackList();
    clearUICallbackList();
}

Matrix4 UI::getProjection() {
    return cashew::glOrtho(0, mWindowWidth, 0, mWindowHeight, -1, 1);
}

Matrix4 UI::getModelView() {
    Matrix4 result;
    result.identity();
    result.scale(1, -1, 1);
    Matrix4 trans;
    trans.translate(0.0f, (float)-mWindowHeight, 0.0f);
    result = result * trans;
    return result;
}