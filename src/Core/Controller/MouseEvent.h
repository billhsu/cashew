/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#ifndef __cashew__MouseEvent__
#define __cashew__MouseEvent__
class MouseEvent {
   public:
    float mousePosX;
    float mousePosY;
    float mouseDragX;
    float mouseDragY;
    float mouseScroll;
    int mouseButton;
    int mouseButtonAction;
    int mouseScrollDirection;
    MouseEvent() {
        mousePosX = 0;
        mousePosY = 0;
        mouseDragX = 0;
        mouseDragY = 0;
        mouseScroll = 0;
        mouseButton = Mouse::MOUSE_BUTTON_UNDEFINED;
        mouseButtonAction = Mouse::MOUSE_ACTION_UNDEFIINED;
        mouseScrollDirection = Mouse::MOUSE_SCROLL_UNDEFINED;
    }
};

#endif /* defined(__cashew__MouseEvent__) */
