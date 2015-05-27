// Shipeng Xu
// billhsu.x@gmail.com
#include "FontRenderer.h"

FontRenderer::FontRenderer() {
    fontList.clear();
    struct sth_stash* stash = sth_create(512, 512);
    int font = sth_add_font(stash, "/Library/Fonts/Arial Black.ttf");
    fontList["Arial Black"] = font;
}

void FontRenderer::addText(int fontId, int fontSize, int x, int y, std::string content) {
    TextRenderInfo textRenderInfo;
    textRenderInfo.fontId = fontId;
    textRenderInfo.fontSize = fontSize;
    textRenderInfo.x = x;
    textRenderInfo.y = y;
    textRenderInfo.content = content;
    textRenderInfoList.push_back(textRenderInfo);
}

void FontRenderer::render(float timeDelta) {
    // TODO RENDER
    
    textRenderInfoList.clear();
}