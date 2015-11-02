// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdleImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/Impl/Scene/LineSketches.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "Core/Controller/Controller.h"

StateIdleImpl::StateIdleImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}
void StateIdleImpl::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::renderSketchLines(NULL);
    if (Controller::bCurrLine && !Controller::bCurrPoint) {
        Scene::renderSingleSketchLine(Controller::currLine,
                                      Vector4(0, 1, 0, 1.0f), 0.15f);
    }
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
}