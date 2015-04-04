//
//  CashewApp.m
//  cashew
//
//  Created by Xu, Shipeng on 23/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "CashewOpenGLView.h"
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
#include "OpenGL/Impl/Basic/LineSegmentRenderer.h"

#include "OpenGL/DepthPeeling/DepthPeeling.h"
#include "OpenGL/TextureManager/TextureManager.h"
#include "Core/Controller/Mouse.h"
#include "FileOperations.h"
#include "FileOperationsCppWrapper.h"
#include <fstream>

GLSLShader UIProgram;
DepthPeeling *depthPeeling;
TextureManager* textureManager;

Controller *mController = &Controller::getInstance();
FileOperations *fileOperations = [FileOperations alloc];

@interface CashewApp : NSObject <CashewOpenGLViewDelegate, CashewInputDelegate>

@end

@implementation CashewApp

- (BOOL)prepareRenderData
{
    [[CashewInputController sharedInputController] addEventDelegate:self];
    NSLog(@"prepareRenderData");
    
    textureManager = &TextureManager::getInstance();
    textureManager->loadTexture("media/textures/point_selected.png", 4);
    textureManager->loadTexture("media/textures/point_current.png", 4);
    textureManager->loadTexture("media/textures/button_cancel.png", 4);
    textureManager->loadTexture("media/textures/button_confirm.png", 4);
    textureManager->loadTexture("media/textures/button_horizontal.png", 4);
    textureManager->loadTexture("media/textures/button_vertical.png", 4);
    textureManager->loadTexture("media/textures/social-icon.png", 4);
    textureManager->loadTexture("media/textures/point_3.png", 4);
    textureManager->loadTexture("media/textures/point_4.png", 4);
    
    UIProgram.loadFromFile(GL_VERTEX_SHADER,   "Shader/UI.vs");
    UIProgram.loadFromFile(GL_FRAGMENT_SHADER, "Shader/UI.fs");
    UIProgram.createProgram();

    Scene::prepareSceneAxis(1.0f);
    Scene::prepareSceneGrid(20.0f,1.0f);

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
    Controller::btnDocNew = mController->GUI->addButton(0, "BTN_ID_DOC_NEW",
                                                        newFile, NULL);
    Controller::btnDocOpen = mController->GUI->addButton(0, "BTN_ID_DOC_OPEN",
                                                        openFile, NULL);
    Controller::btnDocSave = mController->GUI->addButton(0, "BTN_ID_DOC_SAVE",
                                                        saveFile, NULL);
    PlaneRenderer::prepareRenderData();
    PointRenderer::prepareRenderData();
    LineSegmentRenderer::prepareRenderData();

    depthPeeling = &DepthPeeling::getInstance();
    depthPeeling->setPassCount(2);
    depthPeeling->setWindowSize(mController->windowWidth, mController->windowHeight);
    depthPeeling->init();
    
    return YES;
}
void newFile(void* data)
{
    std::string option = showNewFileDialogWrapper((__bridge void*)fileOperations);
    if(option=="OK")
    {
        Controller::sketchLines.clear();
        Controller::lineOperations.clear();
    }
}

void saveFile(void* data)
{
    std::string filename = showSaveFileDialogWrapper((__bridge void*)fileOperations);
    if(filename=="") return;
    std::cout<<"Saving to "<<filename<<std::endl;
    std::ofstream fileStream;
    fileStream.open(filename);
    fileStream<<"cashew v1"<<std::endl;
    fileStream<<Controller::sketchLines.size()<<std::endl;
    for(int i=0; i<Controller::sketchLines.size(); ++i)
    {
        fileStream<<Controller::sketchLines[i].points[0]<<" "<<Controller::sketchLines[i].points[1]<<std::endl;
    }
    fileStream.close();
}

void openFile(void* data)
{
    std::string filename = showOpenFileDialogWrapper((__bridge void*)fileOperations);
    if(filename=="") return;
    std::cout<<"Opening "<<filename<<std::endl;
    Controller::sketchLines.clear();
    std::ifstream fileStream;
    fileStream.open(filename);
    std::string versionStr;
    fileStream>>versionStr;
    std::cout<<"Cashew version: "<<versionStr<<std::endl;
    int sketchSize;
    fileStream>>sketchSize;
    std::cout<<"Sketches: "<<sketchSize<<std::endl;
    for(int i=0; i<sketchSize; ++i)
    {
        Vector3 point1, point2;
        fileStream>>point1>>point2;
        LineSegment line = LineSegment(point1, point2);
        Controller::addLine(line);
    }
    Controller::lineOperations.clear();
    fileStream.close();
}

- (void)mouseLeftUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Mouse::MOUSE_LEFT, Mouse::MOUSE_UP, x, y);
}

- (void)mouseLeftDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Mouse::MOUSE_LEFT, Mouse::MOUSE_DOWN, x, y);
}

- (void)mouseRightUp:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Mouse::MOUSE_RIGHT, Mouse::MOUSE_UP, x, y);
}

- (void)mouseRightDown:(NSPoint)locationInWindow;
{
    int x = (int)locationInWindow.x;
    int y = mController->windowHeight - (int)locationInWindow.y;
    mController->MouseButton(Mouse::MOUSE_RIGHT, Mouse::MOUSE_DOWN, x, y);
}

- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y
{
    y = mController->windowHeight - y;
    mController->PassiveMotion(x, y);
}
- (void)mouseRightDragWithDX:(CGFloat)dx andDY:(CGFloat)dy andX:(CGFloat)x andY:(CGFloat)y
{
    y = mController->windowHeight - y;
    mController->MouseRightDrag(x, y, dx, dy);
}

- (void)mouseLeftDragWithDX:(CGFloat)dx andDY:(CGFloat)dy andX:(CGFloat)x andY:(CGFloat)y
{
    y = mController->windowHeight - y;
    mController->MouseLeftDrag(x, y, dx, dy);
}

- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseButton(Mouse::MOUSE_SCROLL, (int)y,
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLuint local_modelView;
    GLuint local_projection;
    mController->render();
    depthPeeling->render();
    glClearColor(0.8, 0.8, 0.8, 1.0);
    
    UIProgram.bind();
    local_modelView = glGetUniformLocation(UIProgram.getProgram(), "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->GUI->getModelView().get());
    local_projection = glGetUniformLocation(UIProgram.getProgram(), "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->GUI->getProjection().get());
    glUniform1i(glGetUniformLocation(UIProgram.getProgram(), "image0"), 0);
    mController->GUI->render();
    
#ifdef DEBUG
    checkGlErr(__FILE__, __LINE__);
#endif
}

-(void)reshapeWidth:(int)width height:(int)height
{
    mController->resize(width, height);
    depthPeeling->setWindowSize(width, height);
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
    Scene::clearScene();
    PointRenderer::release();
    LineSegmentRenderer::release();
    [super clearGLContext];
}

@end
