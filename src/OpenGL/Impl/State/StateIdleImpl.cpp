// Shipeng Xu
// billhsu.x@gmail.com

#include "StateIdleImpl.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/Impl/Scene/LineSketches.h"
#include "OpenGL/TextureManager/TextureManager.h"

StateIdleImpl::StateIdleImpl()
{
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}
void StateIdleImpl::render()
{
    depthPeeling->addToRenderCallbackList(Scene::renderSketchLines);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
}