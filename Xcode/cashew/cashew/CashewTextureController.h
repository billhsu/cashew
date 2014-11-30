//  Shipeng Xu
//  CashewTextureController.h
//
//  Originally Created by 朱 巍 on 17/2/13.
//  Copyright (c) 2013 Juicer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGL/gltypes.h>
@interface CashewTextureController : NSObject

@property (nonatomic, readonly) BOOL supportsNPOT;

+ (CashewTextureController *)sharedTextureController;

- (GLuint)textureWithFileName:(NSString *)fileName useMipmap:(BOOL)isMapmap;

@end
