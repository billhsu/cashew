// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDrawImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>

void StateDrawImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawGrid();
    cashew::drawAxis();
}