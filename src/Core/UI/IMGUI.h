/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */

#ifndef __cashew__IMGUI__
#define __cashew__IMGUI__
#include "Core/Controller/Mouse.h"
#include "Core/Math/Vectors.h"
#include <queue>

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
    UIState getState();

    enum { RENDER_ITEM_BUTTON = 1, RENDER_ITEM_LABEL };
    struct RenderItem {
        int type;
        int texID;
        char* text;
        Vector2 vertices[4];
        Vector4 color;
    };
    std::queue<RenderItem> getRenderQueue();
    void update(float timeDelta);
    // functions for adding UI elements
    bool button(int ID, int x, int y, int w, int h, int texID,
                Vector4 color = Vector4(1, 1, 1, 1));
}
#endif /* defined(__cashew__IMGUI__) */