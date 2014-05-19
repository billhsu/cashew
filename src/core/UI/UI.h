/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#pragma once
#include "UINode.h"
class UI
{
public:
    static UI& getInstance()
    {
        static UI instance;
        std::cout <<"UI getInstance()"<<std::endl;
        return instance;
    }

    void addButton(int x, int y, int width, int height, 
            void (*callback)(UINode* Sender));
    void addLabel();

    void render(float timeDelta);
private:
    UI();
    ~UI();
}