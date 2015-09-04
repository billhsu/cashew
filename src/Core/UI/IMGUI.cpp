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
    void init() {
        state.init();
    }

    bool regionHit(int x, int y, int w, int h) {
        if (state.mouseX < x || state.mouseY < y || state.mouseX >= x + w ||
            state.mouseY >= y + h) {
            return false;
        }
        return true;
    }

    void beginFrame() {
        state.preHotItem = state.hotItem;
        state.hotItem = 0;
        renderQueue = std::queue<RenderItem>();
    }

    void endFrame() {
        state.preActiveItem = state.activeItem;
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
        timeAnimationAcc += timeDelta;
    }

    RenderItem generateRenderItem(int itemType, int texID, float x, float y,
                                  float width, float height, float offset_x,
                                  float offset_y, Vector4 color) {
        RenderItem item;
        item.type = itemType;
        item.texID = texID;
        item.vertices[0].x = x + offset_x;
        item.vertices[0].y = y + offset_y;
        item.vertices[1].x = x + offset_x + width;
        item.vertices[1].y = y + offset_y;
        item.vertices[2].x = x + offset_x + width;
        item.vertices[2].y = y + offset_y + height;
        item.vertices[3].x = x + offset_x;
        item.vertices[3].y = y + offset_y + height;
        item.color = color;
        return item;
    }

    void checkUIRegion(int ID, int x, int y, int w, int h) {
        if (regionHit(x, y, w, h)) {
            state.hotItem = ID;
            if (state.hotItem != state.preHotItem) {
                timeAnimationAcc = 0;
            }
            if (state.activeItem == 0 &&
                state.mouseButton == Mouse::MOUSE_BUTTON_LEFT &&
                state.mouseState == Mouse::MOUSE_ACTION_DOWN) {
                state.activeItem = ID;
            }
        }
    }

    bool checkUIHit(int ID) {
        if (state.mouseButton == Mouse::MOUSE_BUTTON_LEFT &&
            state.mouseState == Mouse::MOUSE_ACTION_UP && state.hotItem == ID &&
            state.activeItem == ID) {
            return true;
        }
        return false;
    }

    bool button(int ID, int x, int y, int w, int h, int texID, Vector4 color) {
        float height = h;
        float width = w;
        checkUIRegion(ID, x, y, w, h);
        if (state.hotItem == ID) {
            if (state.activeItem == ID) {
            } else {
                height = h * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
                width = w * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
            }
        }

        float offset_x = (w - width) / 2.0f;
        float offset_y = (h - height) / 2.0f;

        RenderItem item =
            generateRenderItem(RENDER_ITEM_BUTTON, texID, x, y, width, height,
                               offset_x, offset_y, color);

        addToRenderQueue(item);
        return checkUIHit(ID);
    }

    bool checkbox(int ID, int x, int y, int w, int h, bool& checked, int texID,
                  Vector4 color) {
        float height = h;
        float width = w;
        checkUIRegion(ID, x, y, w, h);
        if (state.hotItem == ID) {
            if (state.activeItem == ID) {
            } else {
                height = h * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
                width = w * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
            }
        }
        float offset_x = (w - width) / 2.0f;
        float offset_y = (h - height) / 2.0f;
        if (!checked) {
            float oldAplha = color.a;
            color *= 0.5f;
            color.a = oldAplha;
        }
        RenderItem item =
            generateRenderItem(RENDER_ITEM_BUTTON, texID, x, y, width, height,
                               offset_x, offset_y, color);

        addToRenderQueue(item);
        if (checkUIHit(ID)) {
            checked = !checked;
            return true;
        }
        return false;
    }
}