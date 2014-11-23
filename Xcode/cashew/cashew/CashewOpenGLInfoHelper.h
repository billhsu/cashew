//
//  CashewOpenGLInfoHelper.h
//
//  Originally Created by 朱 巍 on 17/2/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CashewOpenGLInfoHelper : NSObject

@property (nonatomic, readonly) float openglVersion;
@property (nonatomic, readonly) NSString *openglExtensions;

+ (CashewOpenGLInfoHelper *)sharedOpenGLInfoHelper;

- (BOOL) checkForGLExtension:(NSString *)searchName;

@end
