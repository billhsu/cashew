// Shipeng Xu
// billhsu.x@gmail.com

#include "Core/UI/UIButton.h"
#include <OpenGL/gl3.h>
class UIButtonImpl : public UIButton
{
public:
    UIButtonImpl(UINode* parent) : UIButton(parent), indices{0,1,2, 0,2,3}{};
    ~UIButtonImpl();
    void render();
    void prepareRenderData();
    GLfloat verticesArray[8];
    GLfloat uvArray[8];
    GLfloat colorArray[16];
    GLubyte indices[6];
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint uvBuffer;
    GLuint indexBuffer;
    GLuint program;
};