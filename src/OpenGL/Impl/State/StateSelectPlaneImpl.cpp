// Shipeng Xu
// billhsu.x@gmail.com

#include "StateSelectPlaneImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/Impl/Basic/PlaneRenderer.h"

void StateSelectPlaneImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawGrid();
    cashew::drawAxis();
    PlaneRenderer::render(Plane(Vector3(0, 1, 0), 1), Vector3(0, 1, 0), 5.0f, Vector4(1,1,1,0.5));
    PlaneRenderer::render(Plane(Vector3(1, 0, 0), 1), Vector3(1, 0, 0), 1.0f, Vector4(1,0.5,1,0.5));
}