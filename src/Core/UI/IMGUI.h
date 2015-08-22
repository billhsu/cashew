/*
 Shipeng Xu
 billhsu.x@gmail.com
 
 Thanks to http://sol.gfxile.net/imgui
 */

#ifndef __cashew__IMGUI__
#define __cashew__IMGUI__

namespace IMGUI {
    struct UIState
    {
        int mouseX;
        int mouseY;
        int mouseButton;
        
        int hotItem;
        int activeItem;
    };
    void init();
    UIState getState();
}
#endif /* defined(__cashew__IMGUI__) */
