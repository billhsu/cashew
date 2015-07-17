// Shipeng Xu
// billhsu.x@gmail.com

#include "UIImpl.h"
#include "UIButtonImpl.h"
#include "UILabelImpl.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Fonts/FontRenderer.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "Core/Controller/Controller.h"

#define UI_HINT_LABEL_ID 321

UIImpl::UIImpl() {
    textureManager = &TextureManager::getInstance();
    UIHintLabel = addLabel(UI_HINT_LABEL_ID, 0, 0, 0, 0, "UIHint", Vector4(1,1,1,0.5));
}
UIButton* UIImpl::addButton(int id, int x, int y, int width, int height,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(void* data), void* userData, UINode* parent) {
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
    button->setUserDataObject(userData);
    nodeList.push_back(button);
    return button;
}

UIButton* UIImpl::addButton(int id, const char* strID,
                                void (*callback)(void* data), void* userData, UINode* parent) {
    int x = luaGetNodePosX(strID);
    int y = luaGetNodePosY(strID);
    int width  = luaGetNodeWidth (strID);
    int height = luaGetNodeHeight(strID);
    
    int textureID_idle = textureManager->loadTexture(luaGetTextureName(strID, "idle"), 4);
    int textureID_hover = textureManager->loadTexture(luaGetTextureName(strID, "hover"), 4);
    int textureID_press = textureManager->loadTexture(luaGetTextureName(strID, "press"), 4);
    
    std::string text = luaGetNodeText(strID);
    UIButtonImpl* button = dynamic_cast<UIButtonImpl*>(addButton(id, x, y, width, height,
                                     textureID_idle,textureID_hover,textureID_press,
                                     text.c_str(), callback, userData, parent));
    
    strcpy(button->strID, strID);
    return button;
}

UILabel* UIImpl::addLabel(int id, int x, int y, int width, int height, const char* text, Vector4 color, UINode* parent) {
    UILabelImpl* label;
    if(parent==NULL) label = new UILabelImpl(mRootNode);
    else label = new UILabelImpl(parent);
    
    label->setText(text);
    label->setSize(width, height);
    label->setPos(x, y);
    label->setColor(color);
    label->prepareRenderData();
    nodeList.push_back(label);
    return label;
}

void UIImpl::prepareRenderData() {
    mRootNode->prepareRenderData();
}

void UIImpl::render() {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    if(strcmp(uiHintText,"") != 0) {
        UIHintLabel->setText(uiHintText);
        UIHintLabel->setPos(hintTextPosX, hintTextPosY + 20);
        UIHintLabel->setSize(100, 100);
    } else {
        UIHintLabel->setText("");
        UIHintLabel->setPos(0, 0);
        UIHintLabel->setSize(0, 0);
    }

    mRootNode->render();
    
    // Render Font
    FontRenderer::getFontShader()->bind();
    GLuint local_modelView = glGetUniformLocation(FontRenderer::getFontShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, Controller::GUI->getModelView().get());
    GLuint local_projection = glGetUniformLocation(FontRenderer::getFontShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, Controller::GUI->getProjection().get());
    glUniform1i(glGetUniformLocation(FontRenderer::getFontShader()->getProgram(), "image0"), 0);
    FontRenderer::render();
        
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    // Clear the UI hint text
    strcpy(uiHintText, "");
}