// Shipeng Xu
// billhsu.x@gmail.com
#include "FontRenderer.h"

FontRenderer::FontRenderer() {
    struct sth_stash* stash = sth_create(512, 512);
    int font = sth_add_font(stash, "/Library/Fonts/Arial Black.ttf");
}