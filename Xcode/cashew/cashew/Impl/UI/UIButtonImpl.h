// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/UI/UIButton.h"
#include <OpenGL/gl3.h>
class UIButtonImpl : public UIButton
{
public:
    UIButtonImpl(UINode* parent) : UIButton(parent), indices{0,1,2, 0,2,3}{};
    void render();
    void prepareRenderData();
    GLfloat verticesArray[8];
    GLubyte indices[6];
};