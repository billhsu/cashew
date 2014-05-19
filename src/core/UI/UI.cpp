/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UI.h"

UI::UI()
{
    //rootNode
}

UI::~UI()
{
    delete rootNode;
}

UIButton* UI::addButton(int x, int y, int width, int height, 
            const char* text, void (*callback)(UINode* Sender))
{

}

UILabel* UI:addLabel(int x, int y, int width, int height,const char* text)
{

}

void UI:render(float timeDelta)
{

}
