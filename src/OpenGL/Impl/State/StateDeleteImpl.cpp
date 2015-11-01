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
    if (!Controller::bCurrLine) {
        return;
    }

    glDisable(GL_DEPTH_TEST);
    Scene::renderSingleSketchLine(Controller::currLine, Vector4(1, 0, 0, 1.0f),
                                  0.15f);
    glEnable(GL_DEPTH_TEST);
}