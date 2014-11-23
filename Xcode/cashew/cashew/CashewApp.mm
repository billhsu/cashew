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
#import "Scene.h"

GLuint vertexBuffer;
GLuint uvBuffer;
GLuint texture;
GLuint program;
GLuint vertexArrayObj;

@interface CashewApp : NSObject <CashewOpenGLViewDelegate>

@end

@implementation CashewApp

- (BOOL)prepareRenderData
{
    CashewShaderController *shaderController = [CashewShaderController sharedShaderController];
    program = [shaderController programWithVertexShaderFile:@"default.vs" FragmentShaderFile:@"default.fs"];
    glUseProgram(program);
    cashew::prepareScene();
    return YES;
}

- (void)update:(NSTimeInterval)timeInterval
{
    
}

- (void)render;
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cashew::drawAxis(1.0f);
}

@end

@implementation CashewOpenGLView(Tutorial)

- (void)prepareOpenGL
{
    [super prepareOpenGL];
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    Set_OpenGLViewDelegate(CashewApp);
}

- (void)clearGLContext
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vertexArrayObj);
    cashew::clearScene();
    glDeleteProgram(program);

    [super clearGLContext];
}

@end
