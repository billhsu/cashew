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
class FontRenderer {
public:
    static FontRenderer& getInstance() {
        static FontRenderer instance;
        return instance;
    }
    struct TextRenderInfo {
        int fontId;
        int fontSize;
        int x;
        int y;
        std::string content;
    };
    void addText(int fontId, int fontSize, int x, int y, std::string content);
    void render(float timeDelta);
private:
    FontRenderer();
    struct sth_stash* stash;
    std::map <std::string, int> fontList;
    std::vector<TextRenderInfo> textRenderInfoList;
};