//  Shipeng Xu
//  CashewOpenGLShaderController.m
//
//  Originally Created by wei.zhu on 1/28/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import "CashewShaderController.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

@implementation CashewShaderController

+ (CashewShaderController *)sharedShaderController
{
    static CashewShaderController *instance = nil;
    
    if (instance == nil) {
        instance = [[CashewShaderController alloc] init];
    }
    
    return instance;
}

- (GLuint)programWithVertexShaderFile:(NSString *)vsfilePath FragmentShaderFile:(NSString *)fsFilePath
{
    NSString *vsfileFullPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:vsfilePath];
    NSString *fsFileFullPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fsFilePath];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:vsfileFullPath] == NO) {
        NSLog(@"%@ not exist", vsfileFullPath);
        return 0;
    }
    if ([fileManager fileExistsAtPath:fsFileFullPath] == NO) {
        NSLog(@"%@ not exist", fsFileFullPath);
        return 0;
    }

    // read shader code from file
    NSString *vsContent = [NSString stringWithContentsOfFile:vsfileFullPath encoding:NSUTF8StringEncoding error:nil];
    NSString *fsContent = [NSString stringWithContentsOfFile:fsFileFullPath encoding:NSUTF8StringEncoding error:nil];
    
    return [self programWithVertexShader:vsContent FragmentShader:fsContent];
}

- (GLuint)programWithVertexShader:(NSString *)vsContent FragmentShader:(NSString *)fsContent
{
    // Create the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    GLint result = GL_FALSE;
    int infoLogLength;
    char *shaderInfoMessage = NULL;
    char *programInfoMessage = NULL;
    
    // Compile Vertex Shader
    const char *vsString = [vsContent UTF8String];
    glShaderSource(vertexShader, 1, &vsString , NULL);
    glCompileShader(vertexShader);
    
    // Check Vertex Shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        shaderInfoMessage = (char *)malloc(infoLogLength + 1);
        glGetShaderInfoLog(vertexShader, infoLogLength, NULL, shaderInfoMessage);
        NSLog(@"vertex shder info: %s", shaderInfoMessage);
        free(shaderInfoMessage);
    }
    
    // Compile Fragment Shader
    const char *fsString = [fsContent UTF8String];
    glShaderSource(fragmentShader, 1, &fsString , NULL);
    glCompileShader(fragmentShader);
    
    // Check Fragment Shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        shaderInfoMessage = (char *)malloc(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShader, infoLogLength, NULL, shaderInfoMessage);
        NSLog(@"fragment shder info: %s", shaderInfoMessage);
        free(shaderInfoMessage);
    }
    
    // Link the program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    // Check the program
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        programInfoMessage = (char *)malloc(infoLogLength + 1);
        glGetProgramInfoLog(program, infoLogLength, NULL, programInfoMessage);
        NSLog(@"program info: %s", programInfoMessage);
        free(programInfoMessage);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

@end
