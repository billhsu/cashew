// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDeleteImpl.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include "OpenGL/Impl/Scene/LineSketches.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"

StateDeleteImpl::StateDeleteImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}

StateDeleteImpl::~StateDeleteImpl() {
}

void StateDeleteImpl::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::renderSketchLines(NULL);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
    depthPeeling->addToRenderCallbackList(renderCurrentLine, this);
}

void StateDeleteImpl::renderCurrentLine(void* data) {
    StateDeleteImpl* self = static_cast<StateDeleteImpl*>(data);
    if (!self->isCurrentLineSelected)
        return;

    LineSegmentRenderer::getLineSegmentShader()->bind();

    GLuint local_modelView = glGetUniformLocation(
        LineSegmentRenderer::getLineSegmentShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE,
                       Controller::modelView.get());
    GLuint local_projection = glGetUniformLocation(
        LineSegmentRenderer::getLineSegmentShader()->getProgram(),
        "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE,
                       Controller::projection.get());
    GLuint local_thickness = glGetUniformLocation(
        LineSegmentRenderer::getLineSegmentShader()->getProgram(), "thickness");
    glUniform1f(local_thickness, 0.15f);
    GLuint local_lineColor = glGetUniformLocation(
        LineSegmentRenderer::getLineSegmentShader()->getProgram(), "lineColor");
    glUniform4f(local_lineColor, 1, 0, 0, 1.0f);
    LineSegmentRenderer::getLineSegmentList().clear();
    LineSegmentRenderer::getLineSegmentList().push_back(self->currentLine);
    glDisable(GL_DEPTH_TEST);
    LineSegmentRenderer::render(0);
    glEnable(GL_DEPTH_TEST);
}