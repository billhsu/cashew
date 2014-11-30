//  Shipeng Xu
//  CashewOpenGLShaderController.h
//
//  Originally Created by wei.zhu on 1/28/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGL/gltypes.h>
@interface CashewShaderController : NSObject

+ (CashewShaderController *)sharedShaderController;

- (GLuint)programWithVertexShader:(NSString *)vsContent FragmentShader:(NSString *)fsContent;
- (GLuint)programWithVertexShaderFile:(NSString *)vsfilePath FragmentShaderFile:(NSString *)fsFilePath;

@end
