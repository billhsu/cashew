// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDrawImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "Core/Controller/Controller.h"

void StateDrawImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::drawScene();
    Vector4 color = Vector4(0.3,0.3,0.3,0.3);
    PlaneRenderer::render(Controller::currPlane, vCenter, 20, color);
}