// Shipeng Xu
// billhsu.x@gmail.com

#include "UIImpl.h"
#include "UIButtonImpl.h"
#include "OpenGL/TextureManager/TextureManager.h"
UIImpl::UIImpl()
{
    textureManager = &TextureManager::getInstance();
}
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
    button->prepareRenderData();
    button->program = shaderProgram;
    nodeList.push_back(button);
    return button;
}

UIButtonImpl* UIImpl::addButton(int id, const char* strID,
                                void (*callback)(UINode* Sender), UINode* parent)
{
    int x = luaGetNodePosX(strID);
    int y = luaGetNodePosY(strID);
    int width  = luaGetNodeWidth (strID);
    int height = luaGetNodeHeight(strID);
    
    int textureID_idle = textureManager->loadTexture(luaGetTextureName(strID, "idle"), 4);
    int textureID_hover = textureManager->loadTexture(luaGetTextureName(strID, "hover"), 4);
    int textureID_press = textureManager->loadTexture(luaGetTextureName(strID, "press"), 4);
    
    std::string text = luaGetNodeText(strID);
    UIButtonImpl* button = addButton(id, x, y, width, height,
                                     textureID_idle,textureID_hover,textureID_press,
                                     text.c_str(), callback, parent);
    
    strcpy(button->strID, strID);
    return button;
}

void UIImpl::prepareRenderData()
{
    mRootNode->prepareRenderData();
}

void UIImpl::render()
{
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    mRootNode->render();

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST) ;
}