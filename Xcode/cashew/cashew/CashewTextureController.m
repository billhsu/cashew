//
//  CashewTextureController.m
//
//  Originally Created by 朱 巍 on 17/2/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import "CashewTextureController.h"
#import "CashewOpenGLInfoHelper.h"
#import <OpenGL/gl3.h>
#import <OpenGL/gl3ext.h>
@import AppKit;

unsigned long getNextPOT(unsigned long x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

@implementation CashewTextureController

+ (CashewTextureController *)sharedTextureController
{
    static CashewTextureController *instance = nil;
    
    if (instance == nil) {
        instance = [[CashewTextureController alloc] init];
    }
    
    return instance;
}

- (id)init
{
    self = [super init];
    if (self) {
        CashewOpenGLInfoHelper *openGLInfoHelp = [CashewOpenGLInfoHelper sharedOpenGLInfoHelper];
        
        if (openGLInfoHelp.openglVersion < 2.0) {
            _supportsNPOT = [openGLInfoHelp checkForGLExtension:@"GL_ARB_texture_non_power_of_two"];
        } else {
            _supportsNPOT = YES;
        }
    }
    
    return self;
}

- (GLuint)textureWithFileName:(NSString *)fileName useMipmap:(BOOL)isMapmap
{
    NSString *fullPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileName];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if ([fileManager fileExistsAtPath:fullPath] == NO) {
        NSLog(@"%@ not exist", fullPath);
        return 0;
    }
    
    NSData *fileData = [[NSData alloc] initWithContentsOfFile:fullPath];
    NSBitmapImageRep *image = [[NSBitmapImageRep alloc] initWithData:fileData];
    CGImageRef cgImage = [image CGImage];
    
    CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
    //support NPOT
    NSUInteger textureWidth, textureHeight;
    if( self.supportsNPOT == NO )
	{
		textureWidth = getNextPOT(CGImageGetWidth(cgImage));
		textureHeight = getNextPOT(CGImageGetHeight(cgImage));
	}
	else
	{
		textureWidth = CGImageGetWidth(cgImage);
		textureHeight = CGImageGetHeight(cgImage);
	}
    CGSize imageSize = CGSizeMake(CGImageGetWidth(cgImage), CGImageGetHeight(cgImage));
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
    BOOL hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
    
    if(colorSpace) {
		if( hasAlpha ) {
			info = kCGImageAlphaPremultipliedLast;
		} else {
			info = kCGImageAlphaNoneSkipLast;
		}
	} else {
		return 0;
	}
    
    //glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    GLuint texObj;
    glGenTextures(1, &texObj);
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texObj);
    
    GLint level = 0;
    NSUInteger width = textureWidth;
    NSUInteger height = textureHeight;
    NSUInteger widthImage = imageSize.width;
    NSUInteger heightImage = imageSize.height;
    do {
        if (level > 0) {
            width /= 2;
            height /= 2;
            
            widthImage /= 2;
            if (widthImage == 0) {
                widthImage = 1;
            }
            
            heightImage /= 2;
            if (heightImage == 0) {
                heightImage = 1;
            }
        }
        
        void *data = malloc(height * width * 4);
        colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef context = CGBitmapContextCreate(data, width, height, 8, 4 * width, colorSpace, info | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        CGContextClearRect(context, CGRectMake(0, 0, width, height));
        CGContextTranslateCTM(context, 0, height - heightImage);
        CGContextDrawImage(context, CGRectMake(0, 0, widthImage, heightImage), cgImage);
        
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        CGContextRelease(context);
        free(data);
        
        if (width == 1 && height == 1) {
            break;
        }
        level++;
        
    } while (isMapmap);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (isMapmap == NO) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    glDisable(GL_TEXTURE_2D);
    
    
    
    return texObj;
}

@end
