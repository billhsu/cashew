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
namespace FontRenderer {
    struct TextRenderInfo {
        int fontId;
        float fontSize;
        float x;
        float y;
        std::string content;
    };
    void prepareRenderData();
    void addText(int fontId, float fontSize, float x, float y, std::string content);
    void render();
    void flushDraw(sth_texture* texture);
    void release();
};
