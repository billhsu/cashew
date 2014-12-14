//
//  CashewApp.m
//  cashew
//
//  Created by Xu, Shipeng on 23/11/14.
//  Copyright (c) 2014 Xu, Shipeng. All rights reserved.
//

#import <OpenGL/gl3.h>
#import "CashewOpenGLView.h"
#import "CashewShaderController.h"
#import "CashewTextureController.h"
#import "CashewInputController.h"
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include "Impl/Scene/Scene.h"

#include "Core/Camera/Camera.h"
#include "Impl/State/StateIdleImpl.h"
#include "Impl/State/StateSelectPlaneImpl.h"
#include "Core/Controller/Controller.h"
GLuint program;

Controller *mController = &Controller::getInstance();

@interface CashewApp : NSObject <CashewOpenGLViewDelegate, CashewInputDelegate>

@end

@implementation CashewApp

- (BOOL)prepareRenderData
{
    [[CashewInputController sharedInputController] addEventDelegate:self];
    NSLog(@"prepareRenderData");
    CashewShaderController *shaderController = [CashewShaderController sharedShaderController];
    program = [shaderController programWithVertexShaderFile:@"default.vs" FragmentShaderFile:@"default.fs"];
    glUseProgram(program);
    cashew::prepareSceneAxis(1.0f);
    cashew::prepareSceneGrid(20.0f,1.0f);
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
- (void)update:(NSTimeInterval)timeInterval
{
    mController->update(timeInterval * 1000.0f);
    GLint local_modelView = glGetUniformLocation(program, "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, mController->modelView.get());
}

- (void)render;
{
    mController->render();
}

-(void)reshapeWidth:(int)width height:(int)height
{
    mController->resize(width, height);
    NSLog(@"reshape - width: %d height: %d", width, height);
    
    GLint local_projection = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, mController->projection.get());
}
@end

@implementation CashewOpenGLView(CashewMain)

- (void)prepareOpenGL
{
    NSLog(@"prepareOpenGL");
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.8, 0.8, 0.8, 1.0);
    NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
    [[NSFileManager defaultManager] changeCurrentDirectoryPath:resourcePath];
    NSLog(@"%@", resourcePath);
    mController->init();
    mController->state_idle = new StateIdleImpl();
    mController->state_select_plane = new StateSelectPlaneImpl();
    State::enterState(mController->state_idle);
    GLint range[2];
    glGetIntegerv(GL_ALIASED_LINE_WIDTH_RANGE, range);
    glGetIntegerv(GL_SMOOTH_LINE_WIDTH_RANGE, range);
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext
{
    NSLog(@"clearGLContext");
    cashew::clearScene();
    glDeleteProgram(program);

    [super clearGLContext];
}

@end
