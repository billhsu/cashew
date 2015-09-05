/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "IMGUI.h"
namespace IMGUI {
    IMGUI::UIState state;
    std::queue<RenderItem> renderQueue;
    bool UIClicked;
    lua_State* luaState;

    bool isUIClicked() {
        return UIClicked;
    }
    float timeAnimationAcc;

    static int luaButton(lua_State* L);
    static int luaCheckbox(lua_State* L);

    void init(lua_State* _luaState) {
        state.init();
        luaState = _luaState;
        lua_register(luaState, "button", luaButton);
        lua_register(luaState, "checkbox", luaCheckbox);
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
        UIClicked = false;
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

    RenderItem generateRenderItem(int itemType, std::string textureFile,
                                  float x, float y, float width, float height,
                                  float offset_x, float offset_y,
                                  Vector4 color) {
        RenderItem item;
        item.type = itemType;
        item.textureFile = textureFile;
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

    bool button(int ID, int x, int y, int w, int h, std::string textureFile,
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

        RenderItem item =
            generateRenderItem(RENDER_ITEM_BUTTON, textureFile, x, y, width,
                               height, offset_x, offset_y, color);

        addToRenderQueue(item);
        return checkUIHit(ID);
    }

    bool checkbox(int ID, int x, int y, int w, int h, bool& checked,
                  std::string textureFile, Vector4 color) {
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
            generateRenderItem(RENDER_ITEM_BUTTON, textureFile, x, y, width,
                               height, offset_x, offset_y, color);

        addToRenderQueue(item);
        if (checkUIHit(ID)) {
            checked = !checked;
            return true;
        }
        return false;
    }
    int luaButton(lua_State* L) {
        int ID = lua_tonumber(L, 1);
        int x = lua_tonumber(L, 2);
        int y = lua_tonumber(L, 3);
        int w = lua_tonumber(L, 4);
        int h = lua_tonumber(L, 5);
        const char* textureFile = lua_tostring(L, 6);
        bool hit = button(ID, x, y, w, h, textureFile);
        lua_pushboolean(L, hit);
        return 1;
    }
    int luaCheckbox(lua_State* L) {
        int ID = lua_tonumber(L, 1);
        int x = lua_tonumber(L, 2);
        int y = lua_tonumber(L, 3);
        int w = lua_tonumber(L, 4);
        int h = lua_tonumber(L, 5);
        lua_pushstring(L, "checked");
        lua_gettable(L, 6);
        bool checked = lua_toboolean(L, 8);
        lua_pop(L, 1);
        const char* textureFile = lua_tostring(L, 7);
        bool hit = checkbox(ID, x, y, w, h, checked, textureFile);
        lua_pushboolean(L, hit);
        return 1;
    }
}