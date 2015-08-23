/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */

#ifndef __cashew__IMGUI__
#define __cashew__IMGUI__
#include "Core/Controller/Mouse.h"

namespace IMGUI {
    struct UIState {
        int mouseX;
        int mouseY;
        int mouseButton;
        int mouseState;

        int hotItem;
        int activeItem;
    };
    void init();
    void beginFrame();
    void endFrame();

    bool button(int x, int y, int w, int h);
    UIState getState();
}
#endif /* defined(__cashew__IMGUI__) */