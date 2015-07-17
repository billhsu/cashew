// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include <map>
#include <string>
#include <vector>
#include <OpenGL/gl3.h>

extern "C" {
    #include "fontstash.h"
}
class GLSLShader;
class Vector3;

namespace FontRenderer {
    struct TextRenderInfo {
        int fontId;
        float fontSize;
        float x;
        float y;
        float color[3];
        std::string content;
    };
    void prepareRenderData();
    void addText(int fontId, float fontSize, float x, float y, Vector3 color, std::string content);
    void addText(std::string fontName, float fontSize, float x, float y, Vector3 color, std::string content);
    void getTextBoundingBox(std::string fontName, float fontSize, std::string content, float* width, float* height);
    void render();
    void flushDraw(sth_texture* texture);
    void release();
    GLSLShader* getFontShader();
};
