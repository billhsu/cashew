/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */

#include "IMGUI.h"
namespace IMGUI {
    IMGUI::UIState state;
    std::queue<RenderItem> renderQueue;
    float timeAnimationAcc;
    float timeElapsed;
    void init() {
        state = {0, 0, 0, 0, 0};
    }

    bool regionHit(int x, int y, int w, int h) {
        if (state.mouseX < x || state.mouseY < y || state.mouseX >= x + w ||
            state.mouseY >= y + h) {
            return false;
        }
        return true;
    }

    void beginFrame() {
        state.hotItem = 0;
        renderQueue = std::queue<RenderItem>();
    }

    void endFrame() {
        if (state.mouseState == Mouse::MOUSE_ACTION_UP) {
            state.activeItem = 0;
        }
    }

    std::queue<RenderItem> getRenderQueue() {
        return renderQueue;
    }

    void addToRenderQueue(RenderItem item) {
        renderQueue.push(item);
    }

    UIState& getState() {
        return state;
    }
    void update(float timeDelta) {
        timeElapsed = timeDelta;
    }

    bool button(int ID, int x, int y, int w, int h, int texID, Vector4 color) {
        float _height = h;
        float _width = w;
        if (regionHit(x, y, w, h)) {
            if (state.hotItem != ID) {
                timeAnimationAcc = 0;
            }
            state.hotItem = ID;
            if (state.activeItem == 0 &&
                state.mouseButton == Mouse::MOUSE_BUTTON_LEFT &&
                state.mouseState == Mouse::MOUSE_ACTION_DOWN)
                state.activeItem = ID;
        }
        if (state.hotItem == ID) {
            if (state.activeItem == ID) {
                // Button is both 'hot' and 'active'
            } else {
                // Button is merely 'hot'
                _height = h * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
                _width = w * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
            }
        } else {
            // button is not hot, but it may be active
        }

        float offset_x = (w - _width) / 2.0f;
        float offset_y = (h - _height) / 2.0f;

        RenderItem item;
        item.type = RENDER_ITEM_BUTTON;
        item.texID = texID;
        item.vertices[0].x = x + offset_x;
        item.vertices[0].y = y + offset_y;
        item.vertices[1].x = x + offset_x + _width;
        item.vertices[1].y = y + offset_y;
        item.vertices[2].x = x + offset_x + _width;
        item.vertices[2].y = y + offset_y + _height;
        item.vertices[3].x = x + offset_x;
        item.vertices[3].y = y + offset_y + _height;
        item.color = color;
        addToRenderQueue(item);

        // If button is hot and active, but mouse button is not
        // down, the user must have clicked the button.
        if (state.mouseButton == Mouse::MOUSE_BUTTON_LEFT &&
            state.mouseState == Mouse::MOUSE_ACTION_UP && state.hotItem == ID &&
            state.activeItem == ID) {
            return true;
        }
        // Otherwise, no clicky.
        return false;
    }
}