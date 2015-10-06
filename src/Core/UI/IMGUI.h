/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */

#ifndef __cashew__IMGUI__
#define __cashew__IMGUI__
#include "Core/Controller/Mouse.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include <queue>
#include <string>

class lua_State;
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
            mouseX = -100;
            mouseY = -100;
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
        int preHotItem;
        int activeItem;
        int preActiveItem;
    };
    void init(lua_State* _luaState);
    void beginFrame();
    void endFrame();
    void resize(int w, int h);
    Matrix4 getProjection();
    Matrix4 getModelView();
    UIState& getState();

    bool isUIHot();
    enum { RENDER_ITEM_BUTTON = 1, RENDER_ITEM_CHECKBOX, RENDER_ITEM_LABEL };
    struct RenderItem {
        int type;
        std::string textureFile;
        std::string text;
        Vector2 vertices[4];
        Vector4 color;
        Vector2 pos;
        Vector2 size;
        bool showHintText;
    };
    std::queue<RenderItem> getRenderQueue();
    void update(float timeDelta);
    // functions for adding UI elements
    bool button(int x, int y, int w, int h, std::string text,
                std::string textureFile, Vector4 color = Vector4(1, 1, 1, 1));
    bool checkbox(int x, int y, int w, int h, std::string text, bool& checked,
                  std::string textureFile, Vector4 color = Vector4(1, 1, 1, 1));
    void label(int x, int y, int w, int h, std::string text,
               Vector4 color = Vector4(1, 1, 1, 0.8));
}
#endif /* defined(__cashew__IMGUI__) */