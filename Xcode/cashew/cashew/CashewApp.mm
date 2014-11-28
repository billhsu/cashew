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
#include "Core/Graphics/Project.h"
#include "Core/Camera/Camera.h"

GLuint vertexBuffer;
GLuint uvBuffer;
GLuint texture;
GLuint program;
GLuint vertexArrayObj;

int windowWidth, windowHeight;
Matrix4 projection, modelView;
Vector3 rotate = Vector3(-30, 0, 0);
Camera *mCamera = NULL;

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
    rotate.x -= y;
    rotate.y += x;
}

- (void)update:(NSTimeInterval)timeInterval
{
    mCamera->rotateCam(rotate);
    mCamera->update(timeInterval);
    modelView = mCamera->getMatrix();
    GLint local_modelView = glGetUniformLocation(program, "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, modelView.get());
}

- (void)render;
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawAxis();
    cashew::drawGrid();
}

-(void)reshapeWidth:(int)width height:(int)height
{
    windowWidth = width;
    windowHeight = height;
    NSLog(@"reshape - width: %d height: %d", windowWidth, windowHeight);
    projection = cashew::gluPerspective(45.0f, windowWidth / (float)windowHeight, 0.1f, 10000.f);
    GLint local_projection = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(local_projection, 1, GL_FALSE, projection.get());
}
@end

@implementation CashewOpenGLView(Tutorial)

- (void)prepareOpenGL
{
    NSLog(@"prepareOpenGL");
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    mCamera = &Camera::getInstance();
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext
{
    NSLog(@"clearGLContext");
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vertexArrayObj);
    cashew::clearScene();
    glDeleteProgram(program);

    [super clearGLContext];
}

@end
