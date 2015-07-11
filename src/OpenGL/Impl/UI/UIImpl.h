// Shipeng Xu
// billhsu.x@gmail.com
#pragma once

#import <OpenGL/gl3.h>
#include "Core/UI/UI.h"

class UIButtonImpl;
class UILabelImpl;

class TextureManager;
class UIImpl : public UI {
public:
    static UIImpl& getInstance() {
        static UIImpl instance;
        std::cout <<"UIImpl getInstance()"<<std::endl;
        return instance;
    }
    void prepareRenderData();
    UIButton* addButton(int id, int x, int y, int width, int height,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(void* data), void* userData = NULL, UINode* parent = NULL);
    
    UIButton* addButton(int id, const char* strID,
                        void (*callback)(void* data), void* userData = NULL, UINode* parent = NULL);
    UILabel* addLabel(int id, int x, int y, int width, int height, const char* text, Vector4 color);
    void setShader(GLuint shader) {shaderProgram = shader;}
    void render();

private:
    UIImpl();
    GLuint shaderProgram;
    TextureManager* textureManager;
};