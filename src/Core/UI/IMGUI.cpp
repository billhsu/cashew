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
#include "Core/Scripting/luaUtility.h"
#include "Core/Graphics/Project.h"

#define TEXTURE_FILE_PATH "media/textures/"
namespace IMGUI {
    IMGUI::UIState state;
    std::queue<RenderItem> renderQueue;
    lua_State* luaState;
    float timeAnimationAcc;

    static int luaButton(lua_State* L);
    static int luaCheckbox(lua_State* L);
    static int luaLabel(lua_State* L);

    int mWindowWidth, mWindowHeight;
    float backingRatioX = 1.0f, backingRatioY = 1.0f;

    void setBackingRatio(float x, float y) {
        backingRatioX = x;
        backingRatioY = y;
        if (luaState != nullptr) {
            lua_pushnumber(luaState, backingRatioX);
            lua_setglobal(luaState, "backingRatioX");
            lua_pushnumber(luaState, backingRatioY);
            lua_setglobal(luaState, "backingRatioY");
        }
    }
    float getBackingRatioX() {
        return backingRatioX;
    }
    float getBackingRatioY() {
        return backingRatioY;
    }

    int currentMaxID = 0;
    int generateID() {
        return ++currentMaxID;
    }

    void init(lua_State* _luaState) {
        state.init();
        luaState = _luaState;
        lua_register(luaState, "button", luaButton);
        lua_register(luaState, "checkbox", luaCheckbox);
        lua_register(luaState, "label", luaLabel);
        lua_pushnumber(luaState, backingRatioX);
        lua_setglobal(luaState, "backingRatioX");
        lua_pushnumber(luaState, backingRatioY);
        lua_setglobal(luaState, "backingRatioY");
    }

    bool regionHit(int x, int y, int w, int h) {
        if (state.mouseX < x || state.mouseY < y || state.mouseX >= x + w ||
            state.mouseY >= y + h) {
            return false;
        }
        return true;
    }

    bool isUIHot() {
        return state.hotItem != 0;
    }

    void beginFrame() {
        state.preHotItem = state.hotItem;
        state.hotItem = 0;
        renderQueue = std::queue<RenderItem>();
        currentMaxID = 0;
    }

    void endFrame() {
        state.preActiveItem = state.activeItem;
        if (state.mouseState == Mouse::MOUSE_ACTION_UP) {
            state.activeItem = 0;
        }
    }

    void resize(int w, int h) {
        mWindowWidth = w;
        mWindowHeight = h;
        lua_pushnumber(luaState, w);
        lua_setglobal(luaState, "window_width");
        lua_pushnumber(luaState, h);
        lua_setglobal(luaState, "window_height");
    }

    Matrix4 getProjection() {
        return cashew::glOrtho(0, mWindowWidth, 0, mWindowHeight, -1, 1);
    }

    Matrix4 getModelView() {
        Matrix4 result;
        result.identity();
        result.scale(1, -1, 1);
        Matrix4 trans;
        trans.translate(0.0f, (float)-mWindowHeight, 0.0f);
        result = result * trans;
        return result;
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
                                  std::string text, float x, float y,
                                  float width, float height, float offset_x,
                                  float offset_y, Vector4 color,
                                  Vector3 textColor, bool showHintText) {
        RenderItem item;
        item.type = itemType;
        if (textureFile.find(TEXTURE_FILE_PATH) == 0) {
            item.textureFile = textureFile;
        } else {
            item.textureFile = TEXTURE_FILE_PATH + textureFile;
        }
        item.vertices[0].x = x + offset_x;
        item.vertices[0].y = y + offset_y;
        item.vertices[1].x = x + offset_x + width;
        item.vertices[1].y = y + offset_y;
        item.vertices[2].x = x + offset_x + width;
        item.vertices[2].y = y + offset_y + height;
        item.vertices[3].x = x + offset_x;
        item.vertices[3].y = y + offset_y + height;
        item.color = color;
        item.textColor = textColor;
        item.text = text;
        item.showHintText = showHintText;
        item.pos = Vector2(x, y);
        item.size = Vector2(width, height);
        return item;
    }

    RenderItem generateRenderItem(int itemType, std::string textureFile,
                                  std::string text, float x, float y,
                                  float width, float height, float offset_x,
                                  float offset_y, Vector4 color,
                                  bool showHintText) {
        return generateRenderItem(itemType, textureFile, text, x, y, width,
                                  height, offset_x, offset_y, color,
                                  Vector3(0, 0, 0), showHintText);
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

    bool button(int x, int y, int w, int h, std::string text,
                std::string textureFile, Vector4 color) {
        float height = h;
        float width = w;
        int ID = generateID();
        bool showHintText = false;
        checkUIRegion(ID, x, y, w, h);
        if (state.hotItem == ID) {
            if (state.activeItem == ID) {
            } else {
                showHintText = true;
                height = h * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
                width = w * (0.96f + 0.04f * cos(timeAnimationAcc / 90.0f));
            }
        }

        float offset_x = (w - width) / 2.0f;
        float offset_y = (h - height) / 2.0f;

        RenderItem item = generateRenderItem(
            RENDER_ITEM_BUTTON, textureFile, text, x, y, width, height,
            offset_x, offset_y, color, showHintText);

        addToRenderQueue(item);
        return checkUIHit(ID);
    }

    bool checkbox(int x, int y, int w, int h, std::string text, bool& checked,
                  std::string textureFile, Vector4 color) {
        float height = h;
        float width = w;
        int ID = generateID();
        bool showHintText = false;
        checkUIRegion(ID, x, y, w, h);
        if (state.hotItem == ID) {
            if (state.activeItem == ID) {
            } else {
                showHintText = true;
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
        RenderItem item = generateRenderItem(
            RENDER_ITEM_CHECKBOX, textureFile, text, x, y, width, height,
            offset_x, offset_y, color, showHintText);

        addToRenderQueue(item);
        if (checkUIHit(ID)) {
            checked = !checked;
            return true;
        }
        return false;
    }

    void label(int x, int y, int w, int h, std::string text, Vector4 color,
               Vector3 textColor) {
        RenderItem item =
            generateRenderItem(RENDER_ITEM_LABEL, "media/textures/FFFFFF-1.png",
                               text, x, y, w, h, 0, 0, color, textColor, false);

        addToRenderQueue(item);
    }
    int luaButton(lua_State* L) {
        int x = lua_tonumber(L, 1);
        int y = lua_tonumber(L, 2);
        int w = lua_tonumber(L, 3);
        int h = lua_tonumber(L, 4);
        const char* text = lua_tostring(L, 5);
        const char* textureFile = lua_tostring(L, 6);
        bool hit = button(x, y, w, h, text, textureFile);
        lua_pushboolean(L, hit);
        return 1;
    }
    int luaCheckbox(lua_State* L) {
        int x = lua_tonumber(L, 1);
        int y = lua_tonumber(L, 2);
        int w = lua_tonumber(L, 3);
        int h = lua_tonumber(L, 4);
        lua_pushstring(L, "checked");
        lua_gettable(L, 6);
        bool checked = lua_toboolean(L, 8);
        lua_pop(L, 1);
        const char* text = lua_tostring(L, 5);
        const char* textureFile = lua_tostring(L, 7);
        bool hit = checkbox(x, y, w, h, text, checked, textureFile);
        lua_pushstring(L, "checked");
        lua_pushboolean(L, checked);
        lua_settable(L, 6);
        lua_pushboolean(L, hit);
        return 1;
    }
    int luaLabel(lua_State* L) {
        int x = lua_tonumber(L, 1);
        int y = lua_tonumber(L, 2);
        int w = lua_tonumber(L, 3);
        int h = lua_tonumber(L, 4);
        const char* text = lua_tostring(L, 5);
        float r, g, b, a;
        r = get_table_field(L, 6, "r");
        g = get_table_field(L, 6, "g");
        b = get_table_field(L, 6, "b");
        a = get_table_field(L, 6, "a");
        Vector4 color = Vector4(r, g, b, a);
        r = get_table_field(L, 7, "r");
        g = get_table_field(L, 7, "g");
        b = get_table_field(L, 7, "b");
        Vector3 textColor = Vector3(r, g, b);
        label(x, y, w, h, text, color, textColor);
        return 1;
    }
}