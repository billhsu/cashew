//
//  CashewApp.m
//  cashew
//
//  Created by Xu, Shipeng on 23/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "CashewOpenGLView.h"
#import "CashewTextureController.h"
#import "CashewInputController.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include "OpenGL/Impl/Scene/Scene.h"

#include "Core/Camera/Camera.h"
#include "OpenGL/Impl/State/StateIdleImpl.h"
#include "OpenGL/Impl/State/StateSelectPlaneImpl.h"
#include "OpenGL/Impl/State/StateDrawImpl.h"
#include "Core/Controller/Controller.h"
#include "OpenGL/Impl/UI/UIImpl.h"
#include "OpenGL/Impl/UI/UIButtonImpl.h"
#include "OpenGL/Util/Utility.h"
#include "OpenGL/Shader/GLSLShader.h"
#include "OpenGL/Impl/Basic/PlaneRenderer.h"
#include "OpenGL/Impl/Basic/PointRenderer.h"
#include "OpenGL/DepthPeeling/DepthPeeling.h"

GLSLShader defaultProgram;
GLSLShader UIProgram;
DepthPeeling depthPeeling;
GLuint texture;

Controller *mController = &Controller::getInstance();

@interface CashewApp : NSObject <CashewOpenGLViewDelegate, CashewInputDelegate>

@end

@implementation CashewApp

UIButtonImpl* button;

- (BOOL)prepareRenderData
{
    [[CashewInputController sharedInputController] addEventDelegate:self];
    NSLog(@"prepareRenderData");
    
    CashewTextureController *textureController = [CashewTextureController sharedTextureController];
    texture = [textureController textureWithFileName:@"media/textures/point_4.png" useMipmap:NO];
    
    
    defaultProgram.loadFromFile(GL_VERTEX_SHADER,   "Shader/default.vs");
    defaultProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/default.fs");
    defaultProgram.createProgram();
    
    UIProgram.loadFromFile(GL_VERTEX_SHADER,   "Shader/UI.vs");
    UIProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/UI.fs");
    UIProgram.createProgram();

    defaultProgram.bind();
    cashew::prepareSceneAxis(1.0f);
    cashew::prepareSceneGrid(20.0f,1.0f);

    UIProgram.bind();
    GLint local_image0 = glGetUniformLocation(UIProgram.getProgram(), "image0");
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(local_image0, 0);
    glDisable(GL_TEXTURE_2D);
    UIProgram.unbind();
    mController->GUI = &UIImpl::getInstance();
    static_cast<UIImpl*>(mController->GUI)->setShader(UIProgram.getProgram());

    for(int i=0; i < State::STATE_ID_MAX; ++i)
    {
        State::statePool[i] = NULL;
    }
    mController->state_idle = new StateIdleImpl();
    mController->state_select_plane = new StateSelectPlaneImpl();
    mController->state_draw = new StateDrawImpl();
    State::enterState(mController->state_idle);
    
    mController->init();
    button = mController->GUI->addButton(0, "BTN_ID_DOC_NEW",
                                                       0, 0, 0, "New Sketch", NULL, NULL);
    button->textureID_idle = texture;
    PlaneRenderer::prepareRenderData();
    PointRenderer::prepareRenderData();
    PointRenderer::getPointList().push_back(Vector3(1,0,0));
    PointRenderer::getPointList().push_back(Vector3(0,1,0));
    PointRenderer::getPointList().push_back(Vector3(0,0,1));
    
    PointRenderer::getPointList().push_back(Vector3(-1,0,0));
    PointRenderer::getPointList().push_back(Vector3(0,-1,0));
    PointRenderer::getPointList().push_back(Vector3(0,0,-1));
    
    depthPeeling.setPassCount(2);
    depthPeeling.setWindowSize(mController->windowWidth, mController->windowHeight);
    depthPeeling.init(renderTransparent);
    
    
    return YES;
}

- (void)mouseLeftUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_LEFT, Controller::MOUSE_UP, x, y);
}

- (void)mouseLeftDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_LEFT, Controller::MOUSE_DOWN, x, y);
}

- (void)mouseRightUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_RIGHT, Controller::MOUSE_UP, x, y);
}

- (void)mouseRightDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Controller::MOUSE_RIGHT, Controller::MOUSE_DOWN, x, y);
}

- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y
{
    y = mController->windowHeight - y;
    mController->PassiveMotion(x, y);
}
- (void)mouseRightDragWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseRightDrag(x, y);
}

- (void)mouseLeftDragWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseLeftDrag(x, y);
}

- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseButton(Controller::MOUSE_SCROLL, (int)y,
                             mController->mouseX, mController->mouseY);
    
}
- (void)keyDown:(unichar)key
{
    mController->Keyboard(key, Controller::KEY_DOWN);
}
- (void)keyUp:(unichar)key
{
    mController->Keyboard(key, Controller::KEY_UP);
}
- (void)update:(NSTimeInterval)timeInterval
{
    mController->update(timeInterval * 1000.0f);
}

- (void)render;
{
    defaultProgram.bind();
    GLint local_modelView = glGetUniformLocation(defaultProgram.getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    GLint local_projection = glGetUniformLocation(defaultProgram.getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
    mController->render();
    
    PlaneRenderer::getPlaneShader()->bind();
    local_modelView = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    local_projection = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
//    PlaneRenderer::render(Plane(Vector3(0, 1, 0),1), Vector3(0,1,0), 4, Vector4(0,0,1,0.8));
//    PlaneRenderer::render(Plane(Vector3(0, 0, 1),1), Vector3(0,0,1), 4, Vector4(1,0,0,0.8));
    
    PointRenderer::getPointShader()->bind();
    local_modelView = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    local_projection = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
    int local_pointSize = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "pointSize");
    glUniform1f(local_pointSize, 5.f);
//    PointRenderer::render(texture);
    depthPeeling.render();
    button->textureID_idle = depthPeeling.colorTexture1;
    button->setPos(0, 0);
    button->setSize(80*8, 60*8);
//    glClearColor(0.8, 0.8, 0.8, 1.0);
    
    UIProgram.bind();
    local_modelView = glGetUniformLocation(UIProgram.getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->GUI->getModelView().get());
    local_projection = glGetUniformLocation(UIProgram.getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->GUI->getProjection().get());
    
    mController->GUI->render();
    
#ifdef DEBUG
    checkGlErr(__FILE__, __LINE__);
#endif
}

void renderTransparent()
{
    GLuint local_modelView, local_projection;
    
    PlaneRenderer::getPlaneShader()->bind();
    local_modelView = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    local_projection = glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
    glUniform1i(glGetUniformLocation(PlaneRenderer::getPlaneShader()->getProgram(), "PeelLayerDepthMap"), 0);
    
    PlaneRenderer::render(Plane(Vector3(0, 1, 0),1), Vector3(0,1,0), 4, Vector4(1,0,0,0.8));
    PlaneRenderer::render(Plane(Vector3(0, 0, 1),1), Vector3(0,0,1), 4, Vector4(0,1,0,0.8));
    PlaneRenderer::render(Plane(Vector3(1, 0, 0),1), Vector3(1,0,0), 4, Vector4(0,0,1,0.8));
    
    PointRenderer::getPointShader()->bind();
    local_modelView = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
    local_projection = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
    int local_pointSize = glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "pointSize");
    glUniform1f(local_pointSize, 5.f);
    glUniform1i(glGetUniformLocation(PointRenderer::getPointShader()->getProgram(), "PeelLayerDepthMap"), 0);
    PointRenderer::render(texture);
}

-(void)reshapeWidth:(int)width height:(int)height
{
    mController->resize(width, height);
    depthPeeling.setWindowSize(width, height);
    NSLog(@"reshape - width: %d height: %d", width, height);
}
@end

@implementation CashewOpenGLView(CashewMain)

- (void)prepareOpenGL
{
    NSLog(@"prepareOpenGL");
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
    NSLog(@"%@", resourcePath);
    
    GLint range[2];
    glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, range);
    glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext
{
    NSLog(@"clearGLContext");
    cashew::clearScene();
    PointRenderer::release();
    [super clearGLContext];
}

@end
