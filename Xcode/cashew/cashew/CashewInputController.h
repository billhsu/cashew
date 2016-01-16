//  Thanks https://github.com/JulianAtGitHub/OpenGL-tutorial-for-Cocoa-master
//

#import <Foundation/Foundation.h>

@protocol CashewInputDelegate<NSObject>

@optional
- (void)updateInput:(NSTimeInterval)timeInterval;
- (void)keyDown:(unichar)key;
- (void)keyUp:(unichar)key;
- (void)mouseLeftDown:(NSPoint)locationInWindow;
- (void)mouseLeftUp:(NSPoint)locationInWindow;
- (void)mouseRightDown:(NSPoint)locationInWindow;
- (void)mouseRightUp:(NSPoint)locationInWindow;
- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseLeftDragWithDX:(CGFloat)dx
                      andDY:(CGFloat)dy
                       andX:(CGFloat)x
                       andY:(CGFloat)y;
- (void)mouseRightDragWithDX:(CGFloat)dx
                       andDY:(CGFloat)dy
                        andX:(CGFloat)x
                        andY:(CGFloat)y;
- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseEnteredWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseExitedWithX:(CGFloat)x andY:(CGFloat)y;
@end

@interface CashewInputController : NSObject

+ (CashewInputController*)sharedInputController;

- (void)addEventDelegate:(id<CashewInputDelegate>)delegate;
- (void)removeEventDelegate:(id<CashewInputDelegate>)delegate;

- (void)updateDelegate:(NSTimeInterval)timeInterval;

- (void)keysDown:(NSString*)keys;
- (void)keysUp:(NSString*)keys;
- (BOOL)keyIsPressed:(unichar)key;

- (void)mouseLeftDown:(NSPoint)locationInWindow;
- (void)mouseLeftUp:(NSPoint)locationInWindow;
- (void)mouseRightDown:(NSPoint)locationInWindow;
- (void)mouseRightUp:(NSPoint)locationInWindow;
- (void)mouseMoveWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseLeftDragWithDX:(CGFloat)x
                      andDY:(CGFloat)y
                       andX:(CGFloat)x
                       andY:(CGFloat)y;
- (void)mouseRightDragWithDX:(CGFloat)dx
                       andDY:(CGFloat)dy
                        andX:(CGFloat)x
                        andY:(CGFloat)y;
- (void)mouseScrollWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseEnteredWithX:(CGFloat)x andY:(CGFloat)y;
- (void)mouseExitedWithX:(CGFloat)x andY:(CGFloat)y;
@end
