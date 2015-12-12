// Shipeng Xu
// billhsu.x@gmail.com

#ifndef __cashew__IMGUIImpl__
#define __cashew__IMGUIImpl__
#include "Core/UI/IMGUI.h"
class GLSLShader;

namespace IMGUIImpl {
    using namespace IMGUI;
    void init();
    void render();
    GLSLShader& getUIProgram();
};

#endif /* defined(__cashew__IMGUIImpl__) */
