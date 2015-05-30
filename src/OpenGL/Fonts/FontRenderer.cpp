// Shipeng Xu
// billhsu.x@gmail.com
#include "FontRenderer.h"

FontRenderer::FontRenderer() {
    fontList.clear();
    stash = sth_create(512, 512);
    int font = sth_add_font(stash, "media/fonts/droid-sans/DroidSans.ttf");
    fontList["DroidSans"] = font;
    font = sth_add_font(stash, "media/fonts/droid-sans/DroidSans-Bold");
    fontList["DroidSans-Bold"] = font;
}

void FontRenderer::addText(int fontId, float fontSize, float x, float y, std::string content) {
    TextRenderInfo textRenderInfo;
    textRenderInfo.fontId = fontId;
    textRenderInfo.fontSize = fontSize;
    textRenderInfo.x = x;
    textRenderInfo.y = y;
    textRenderInfo.content = content;
    textRenderInfoList.push_back(textRenderInfo);
}

void FontRenderer::render(float timeDelta) {
    sth_begin_draw(stash);
    for(int i=0; i<textRenderInfoList.size(); ++i) {
        sth_draw_text(stash, textRenderInfoList[i].fontId,
                      textRenderInfoList[i].fontSize,
                      textRenderInfoList[i].x,
                      textRenderInfoList[i].y,
                      textRenderInfoList[i].content.c_str(),
                      &textRenderInfoList[i].x);
    }
    sth_end_draw(stash);
    textRenderInfoList.clear();
}