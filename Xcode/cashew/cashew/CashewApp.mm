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
#include "Core/Math/Vectors.h"
#include "Core/Math/Matrices.h"
#include "Impl/Scene/Scene.h"
#include "Core/Graphics/Project.h"

GLuint vertexBuffer;
GLuint uvBuffer;
GLuint texture;
GLuint program;
GLuint vertexArrayObj;

int windowWidth, windowHeight;
Matrix4 projection, modelView;

@interface CashewApp : NSObject <CashewOpenGLViewDelegate>

@end

@implementation CashewApp

- (BOOL)prepareRenderData
{
    NSLog(@"prepareRenderData");
    CashewShaderController *shaderController = [CashewShaderController sharedShaderController];
    program = [shaderController programWithVertexShaderFile:@"default.vs" FragmentShaderFile:@"default.fs"];
    glUseProgram(program);
    
    modelView = cashew::gluLookAt(4.0, 3.0, 3.0, 0, 0, 0, 0, 1.0, 0);
    GLint local_modelView = glGetUniformLocation(program, "modelView");
    glUniformMatrix4fv(local_modelView, 1, GL_FALSE, modelView.get());
    
    cashew::prepareSceneAxis(1.0f);
    return YES;
}

- (void)update:(NSTimeInterval)timeInterval
{
    
}

- (void)render;
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawAxis();
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
