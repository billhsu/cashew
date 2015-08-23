/*
 Shipeng Xu
 billhsu.x@gmail.com
 */
#pragma once
class Mouse {
   public:
    enum {
        MOUSE_BUTTON_LEFT = 10,
        MOUSE_BUTTON_RIGHT,
        MOUSE_BUTTON_SCROLL,
        MOUSE_BUTTON_UNDEFINED
    };
    enum {
        MOUSE_ACTION_UP = 20,
        MOUSE_ACTION_DOWN,
        MOUSE_ACTION_DRAG,
        MOUSE_ACTION_MOTION,
        MOUSE_ACTION_UNDEFIINED
    };
    enum { MOUSE_SCROLL_UP = 30, MOUSE_SCROLL_DOWN, MOUSE_SCROLL_UNDEFINED };
};