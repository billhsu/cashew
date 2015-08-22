/*
 Shipeng Xu
 billhsu.x@gmail.com
 */

#include "IMGUI.h"
namespace IMGUI {
    IMGUI::UIState state;
    
    void init() {
        state = {0, 0, 0, 0, 0};
        
    }
    
    UIState getState() {
        return state;
    }
    
    
}
