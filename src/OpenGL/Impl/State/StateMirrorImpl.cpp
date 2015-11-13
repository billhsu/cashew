// Shipeng Xu
// billhsu.x@gmail.com

#include "StateMirrorImpl.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include "OpenGL/Impl/Scene/DrawLineSegment.h"
#include <OpenGL/gl3.h>

StateMirrorImpl::StateMirrorImpl() {
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}

StateMirrorImpl::~StateMirrorImpl() {
}

void StateMirrorImpl::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::renderLineSegments(NULL);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
}