/* 
Shipeng Xu
billhsu.x@gmail.com
*/
#include "UI.h"

UI::UI()
{
    rootNode = new UINode(NULL);
}

UI::~UI()
{
    delete rootNode;
}

UIButton* UI::addButton(int x, int y, int width, int height, 
            const char* text, void (*callback)(UINode* Sender))
{
    UIButton* button = new UIButton(rootNode);
    button->setPos(x, y);
    button->setText(text);
    button->setSize(width, height);
    button->SetCallback(callback);
    return button;
}

UILabel* UI:addLabel(int x, int y, int width, int height,const char* text)
{
    UILabel* label = new UILabel(rootNode);
    label->setPos(x, y);
    label->setText(text);
    label->setSize(width, height);
    return label;
}

void UI:render(float timeDelta)
{

}
