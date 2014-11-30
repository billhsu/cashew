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
#include "Core/State/State.h"
#include "Core/State/StateIdle.h"
#include "Core/Controller/Controller.h"
GLuint program;

int windowWidth, windowHeight;
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

- (void)mouseLeftDragWithX:(CGFloat)x andY:(CGFloat)y
{
    mController->MouseMotion(x, y);
}

- (void)update:(NSTimeInterval)timeInterval
{
    mController->update(timeInterval);
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
    NSLog(@"reshape - width: %d height: %d", windowWidth, windowHeight);
    
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
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
