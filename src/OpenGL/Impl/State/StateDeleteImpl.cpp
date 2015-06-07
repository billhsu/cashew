// Shipeng Xu
// billhsu.x@gmail.com

#include "StateDeleteImpl.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "OpenGL/Impl/Scene/Scene.h"
#include "OpenGL/Impl/Scene/LineSketches.h"
#include <OpenGL/gl3.h>
#include "OpenGL/DepthPeeling/DepthPeeling.h"

StateDeleteImpl::StateDeleteImpl()
{
    depthPeeling = &DepthPeeling::getInstance();
    textureManager = &TextureManager::getInstance();
}
StateDeleteImpl::~StateDeleteImpl()
{
}

void StateDeleteImpl::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    depthPeeling->addToRenderCallbackList(Scene::renderSketchLines);
    depthPeeling->addToRenderCallbackList(Scene::drawSceneWrapper);
    depthPeeling->addToRenderCallbackList(Scene::renderCurrentPoint);
}