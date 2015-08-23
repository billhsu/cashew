/*
 Shipeng Xu
 billhsu.x@gmail.com

 Thanks to http://sol.gfxile.net/imgui
 */

#include "IMGUI.h"
namespace IMGUI {
    IMGUI::UIState state;
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
    int genID() {
        return 0;
    }
    void beginFrame() {
        state.hotItem = 0;
    }
    void endFrame() {
        if (state.mouseState == Mouse::MOUSE_ACTION_UP) {
            state.activeItem = 0;
        }
    }

    bool button(int ID, int x, int y, int w, int h) {
        if (regionHit(x, y, w, h)) {
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
            }
        } else {
            // button is not hot, but it may be active
        }

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

    UIState getState() {
        return state;
    }
}