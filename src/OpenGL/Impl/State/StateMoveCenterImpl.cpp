// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMoveCenterImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/Impl/Scene/DrawLineSegment.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "Core/Controller/Controller.h"
#include "Core/Basic/SketchLine.h"

StateMoveCenterImpl::StateMoveCenterImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}
void StateMoveCenterImpl::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::renderLineSegments(NULL);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
}