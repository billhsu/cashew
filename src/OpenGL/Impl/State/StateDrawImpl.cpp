// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDrawImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Impl/Scene/DrawLineSegment.h"
StateDrawImpl::StateDrawImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}
StateDrawImpl::~StateDrawImpl() {
}

void StateDrawImpl::render() {
    Vector4 color = Vector4(0.3, 0.3, 0.3, 0.1);
    Vector3 center(0, 0, 0);
    for (int i = 0; i < selectedPoints.size(); ++i) {
        center += selectedPoints[i];
    }
    center /= selectedPoints.size();
    currentPlane = Controller::currPlane;
    renderCurrentPlaneColor = color;
    renderCurrentPlaneCenter = center;

    Scene::renderSketchLines(NULL);
    renderCurrentLine();

    depthPeeling->addToRenderCallbackList(renderCurrentPlane, this);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper, this);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
    depthPeeling->addToRenderCallbackList(renderCurrentPoints, this);
}

void StateDrawImpl::renderCurrentPlane(void* data) {
    StateDrawImpl* self = static_cast<StateDrawImpl*>(data);
    PlaneRenderer::getPlaneShader()->bind();

    GLuint local_modelView = glGetUniformLocation(
        PlaneRenderer::getPlaneShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                       Controller::modelView.get());
    GLuint local_projection = glGetUniformLocation(
        PlaneRenderer::getPlaneShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                       Controller::projection.get());

    PlaneRenderer::render(self->currentPlane, self->renderCurrentPlaneCenter,
                          20, self->renderCurrentPlaneColor);
}

void StateDrawImpl::renderCurrentPoints(void* data) {
    StateDrawImpl* self = static_cast<StateDrawImpl*>(data);
    PointRenderer::getPointShader()->bind();
    GLuint local_modelView = glGetUniformLocation(
        PointRenderer::getPointShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                       Controller::modelView.get());
    GLuint local_projection = glGetUniformLocation(
        PointRenderer::getPointShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                       Controller::projection.get());
    GLuint local_pointSize = glGetUniformLocation(
        PointRenderer::getPointShader()->getProgram(), "pointSize");
    glUniform1f(local_pointSize, 0.3f);
    glUniform1i(
        glGetUniformLocation(PointRenderer::getPointShader()->getProgram(),
                             "pointTexture"),
        1);
    PointRenderer::getPointList().clear();
    for_each(self->selectedPoints.begin(), self->selectedPoints.end(),
             [](Vector3 v) { PointRenderer::getPointList().push_back(v); });
    PointRenderer::render(
        self->textureManager->getTexture("media/textures/point_3.png")
            .glTextureID);
    if (self->internalState == STATE_DRAW_START_POINT_SELECTED) {
        PointRenderer::getPointList().clear();
        PointRenderer::getPointList().push_back(self->startPoint);
        PointRenderer::getPointList().push_back(self->endPoint);
        PointRenderer::render(
            self->textureManager->getTexture("media/textures/point_4.png")
                .glTextureID);
    }
}

void StateDrawImpl::renderCurrentLine() {
    if (internalState != STATE_DRAW_START_POINT_SELECTED) {
        return;
    }
    Scene::renderSingleSketchLine(currentLine, Vector3(0.545, 0.2, 1), 0.1f);
    if (Controller::mirrorMode & Controller::MIRROR_MODE_X) {
        Scene::renderSingleSketchLine(currentLineMirrorX, Vector3(0.5, 1, 0),
                                      0.1f);
    }
    if (Controller::mirrorMode & Controller::MIRROR_MODE_Y) {
        Scene::renderSingleSketchLine(currentLineMirrorY, Vector3(0.5, 1, 0),
                                      0.1f);
    }
    if (Controller::mirrorMode & Controller::MIRROR_MODE_Z) {
        Scene::renderSingleSketchLine(currentLineMirrorZ, Vector3(0.5, 1, 0),
                                      0.1f);
    }
}
