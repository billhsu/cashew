//  Thanks https://github.com/JulianAtGitHub/OpenGL-tutorial-for-Cocoa-master
//

#import <Foundation/Foundation.h>

@interface CashewOpenGLInfoHelper : NSObject

@property(nonatomic, readonly) float openglVersion;
@property(nonatomic, readonly) NSString* openglExtensions;

+ (CashewOpenGLInfoHelper*)sharedOpenGLInfoHelper;

- (BOOL)checkForGLExtension:(NSString*)searchName;

@end
