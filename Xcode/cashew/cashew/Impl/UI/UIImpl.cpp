// Shipeng Xu
// billhsu.x@gmail.com

#include "UIImpl.h"
#include "UIButtonImpl.h"

UIButtonImpl* UIImpl::addButton(int id, int x, int y, int width, int height,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(UINode* Sender), UINode* parent)
{
    UIButtonImpl* button;
    if(parent==NULL) button = new UIButtonImpl(mRootNode);
    else button = new UIButtonImpl(parent);
    button->nodeID = id;
    button->textureID_idle = textureID_idle;
    button->textureID_hover = textureID_hover;
    button->textureID_press = textureID_press;
    button->setPos(x, y);
    button->setText(text);
    button->setSize(width, height);
    button->setCallback(callback);
    nodeList.push_back(button);
    return button;
}

UIButtonImpl* UIImpl::addButton(int id, const char* strID,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(UINode* Sender), UINode* parent)
{
    int x = luaGetNodePosX(strID);
    int y = luaGetNodePosY(strID);
    int width  = luaGetNodeWidth (strID);
    int height = luaGetNodeHeight(strID);
    UIButtonImpl* button = addButton(id, x, y, width, height,
                                 textureID_idle, textureID_hover, textureID_press,
                                 text, callback, parent);
    strcpy(button->strID, strID);
    return button;
}

void UIImpl::prepareRenderData()
{
    mRootNode->prepareRenderData();
}

void UIImpl::render()
{
    mRootNode->render();
}