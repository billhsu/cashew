// Shipeng Xu
// billhsu.x@gmail.com

#include "StateSelectPlaneImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"

StateSelectPlaneImpl::StateSelectPlaneImpl()
{
    depthPeeling = &DepthPeeling::getInstance();
}
void StateSelectPlaneImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawGrid();
    cashew::drawAxis();
    Vector3 center(0,0,0);
    for(int i=0;i<selectedPoints.size();++i)
    {
        center += selectedPoints[i];
    }
    center /= selectedPoints.size();
    Vector4 color = Vector4(0.3,0.3,0.3,0.3);
    depthPeeling->addToRenderCallbackList([=](){PlaneRenderer::render(Controller::currPlane, center, 20, color);});
}
