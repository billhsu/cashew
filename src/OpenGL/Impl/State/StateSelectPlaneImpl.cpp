// Shipeng Xu
// billhsu.x@gmail.com

#include "StateSelectPlaneImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"

Vector3 StateSelectPlaneImpl::renderCurrentPlaneCenter;
Vector4 StateSelectPlaneImpl::renderCurrentPlaneColor;
Plane StateSelectPlaneImpl::currentPlane;

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
    Vector4 color = Vector4(0.3,0.3,0.3,0.6);
    currentPlane = Controller::currPlane;
    renderCurrentPlaneColor = color;
    renderCurrentPlaneCenter = center;
    depthPeeling->addToRenderCallbackList(renderCurrentPlane);
}

void StateSelectPlaneImpl::renderCurrentPlane()
{
    PlaneRenderer::getPlaneShader()->bind();
    GLuint local_modelView = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, Controller::modelView.get());
    GLuint local_projection = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, Controller::projection.get());
    
    PlaneRenderer::render(currentPlane, renderCurrentPlaneCenter, 20, renderCurrentPlaneColor);
}