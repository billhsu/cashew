// Shipeng Xu
// billhsu.x@gmail.com
#pragma once
#include "fontstash.h"
class FontRenderer {
public:
    static FontRenderer& getInstance() {
        static FontRenderer instance;
        return instance;
    }
private:
    FontRenderer();
    struct sth_stash* stash;
};