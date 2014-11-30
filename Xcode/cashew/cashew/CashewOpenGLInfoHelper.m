//  Shipeng Xu
//  GSOpenGLInfoHelper.m
//
//  CashewOpenGLInfoHelper.m
//
//  Originally Created by 朱 巍 on 17/2/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import "CashewOpenGLInfoHelper.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>

@implementation CashewOpenGLInfoHelper

+ (CashewOpenGLInfoHelper *)sharedOpenGLInfoHelper
{
    static CashewOpenGLInfoHelper *instance = nil;
    
    if (instance == nil) {
        instance = [[CashewOpenGLInfoHelper alloc] init];
    }
    
    return instance;
}

- (id)init
{
    self = [super init];
    
    if (self) {
        NSLog(@"GL_VENDOR:   %s", glGetString( GL_VENDOR ) );
		NSLog(@"GL_RENDERER: %s", glGetString( GL_RENDERER ) );
		NSLog(@"GL_VERSION:  %s", glGetString( GL_VERSION ) );

        NSString *versionAll = [NSString stringWithCString:(const char *)glGetString( GL_VERSION ) encoding: NSUTF8StringEncoding];
        NSString *versionMain = [versionAll substringToIndex:3];
        _openglVersion = [versionMain floatValue];
        
        NSMutableString *extensions = [NSMutableString string];
        GLint nExtension;
        glGetIntegerv(GL_NUM_EXTENSIONS, &nExtension);
        for (GLint i = 0; i < nExtension; ++i) {
            [extensions appendFormat:@"%s ", (const char *)glGetStringi(GL_EXTENSIONS, i)];
        }
        _openglExtensions = [NSString stringWithString:extensions];
    }
    
    return self;
}

- (BOOL) checkForGLExtension:(NSString *)searchName
{
	// For best results, extensionsNames should be stored in your renderer so that it does not
	// need to be recreated on each invocation.
    NSArray *extensionsNames = [_openglExtensions componentsSeparatedByString:@" "];
    return [extensionsNames containsObject: searchName];
}

@end
