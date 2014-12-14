// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/UI/UI.h"

class UIButtonImpl;

class UIImpl : public UI
{
    UIButtonImpl* addButton(int id, int x, int y, int width, int height,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);
    
    UIButtonImpl* addButton(int id, const char* strID,
                        uint32_t textureID_idle, uint32_t textureID_hover, uint32_t textureID_press,
                        const char* text, void (*callback)(UINode* Sender), UINode* parent = NULL);
};