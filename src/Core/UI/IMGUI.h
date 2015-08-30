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
    class UIState {
       public:
        UIState() {
            init();
        }
        void setMousePos(int x, int y) {
            mouseX = x;
            mouseY = y;
        }
        void setMouseButton(int button) {
            mouseButton = button;
        }
        void setMouseState(int state) {
            mouseState = state;
        }
        void setHotItem(int ID) {
            hotItem = ID;
        }
        void setActiveItem(int ID) {
            activeItem = ID;
        }
        void init() {
            mouseX = 0;
            mouseY = 0;
            mouseButton = Mouse::MOUSE_BUTTON_UNDEFINED;
            mouseState = Mouse::MOUSE_ACTION_UNDEFIINED;
            hotItem = 0;
            activeItem = 0;
        }
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
    UIState& getState();

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